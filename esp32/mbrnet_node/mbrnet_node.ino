#include "painlessMesh.h"

#define   MESH_PREFIX     "mbrnet1"
#define   MESH_PASSWORD   "123456789"
#define   MESH_PORT       5555

Scheduler userScheduler;
painlessMesh  mesh;

void sendMessage() ;

Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );

void sendMessage() {
  char msg[100];
  sprintf(msg, "%u,%.2f,%.2f", (unsigned long)mesh.getNodeId(), (random(0, 2999) + 6000) / 100.0, random(0, 99) / 100.0);
  mesh.sendBroadcast(msg);
  Serial2.println(msg);
  taskSendMessage.setInterval( random( TASK_SECOND * 20, TASK_SECOND * 40 ));
}

void receivedCallback( uint32_t from, String &msg ) {
  Serial2.println(msg);
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  Serial2.setRxBufferSize(2048);

  mesh.setDebugMsgTypes( ERROR | STARTUP );

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
}

void loop() {
  mesh.update();
}
