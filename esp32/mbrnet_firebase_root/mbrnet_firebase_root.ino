#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>

#define FIREBASE_HOST "https://sce-hacks-2021-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "" //"AIzaSyAUvpTKzl5KJs4icdyIQPFEEmcvbUqz2Fo"
#define WIFI_SSID "[SSID]"
#define WIFI_PASSWORD "[PASSWORD]"

const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;


void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  Serial2.setRxBufferSize(2048);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void postData(String id, float temp, float gas) {
  Firebase.setFloat("/data/" + id + "/t", temp);
  if (Firebase.failed()) {
    Serial.print("temp failed:");
    Serial.println(Firebase.error());
    return;
  }
  Firebase.setFloat("/data/" + id + "/g", gas);
  if (Firebase.failed()) {
    Serial.print("gas failed:");
    Serial.println(Firebase.error());
    return;
  }
}

void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial2.available() > 0 && newData == false) {
    rc = Serial2.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0';
      ndx = 0;
      newData = true;
    }
  }
}

void showNewData() {
  if (newData == true) {
    String s = String(receivedChars);
    int firstComma = s.indexOf(',');
    int lastComma = s.lastIndexOf(',');
    String id = s.substring(0, firstComma);
    float temp = s.substring(firstComma + 1, lastComma).toFloat();
    float gas = s.substring(lastComma + 1).toFloat();
    postData(id, temp, gas);
    newData = false;
  }
}

void loop() {
  recvWithEndMarker();
  showNewData();
}
