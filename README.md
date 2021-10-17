# MBRNet

## What is MBRNet 

MBRNet: the Mesh Blaze Response Network is a mesh network of sensors that aims to help firefighters and civilians respond to fires quicker so that they can do less damage. It is pronounced like "ember net". It is low-cost and easily reproducible because all parts are readily available online for cheap. The mesh network is useful in an environment, such as forests, where there is not an available internet connection. Only one node, the root node, needs to be connected to the internet so that it can communicate to FireBase. Another benefit of the mesh network is that it is self-healing. This means that if a fire is detected and destroys a node, the network will funnel the data to other nodes so that they still get to the people who need to act quickly. All of the sensor data for each location is pushed up to FireBase, which is then displayed on a live map on a webpage so California can see it.


## Inspiration

MbrNet was inspired by the response times to wildfires. Normally, wildfires are detected by air patrols, infrared technology, computer technology, or lookout stations. However, we feel that these tools were not enough as it takes most CAL fire staff to reach most forests within 20 minutes or less. Every minute is important as suppression costs can total up to $9.5 million per and the value of the lost home be estimated at $300,000 to $450,000 per wildfire. As such, we wanted to deploy thousands of microcomputers across remote areas so if temperatures or carbon dioxide levels were to rise, and there would be instant notice for firefighters to be deployed and civilians evacuated.


## How we built it
**Hardware**
We used 5 Adafruit ESP32 Feather microcontrollers. One for the internet bridge and the rest for the mesh network.
 
**Firmware**
We used the Arduino ide along with C++ to code the firmware for the mesh network. We used the ArduinoJson, IXOHop_Firebase, and the PainlessMesh Arduino libraries.

**Database**
We used the FireBase realtime database to store all of our data in a JSON format.

**Webpage**
We used Leaflet.js for the interactive data map. The Bootstrap framework was used for the styling. All of the webpage was written in HTML and JavaScript.
  

## Challenges we ran into

**Connecting the Mesh Network to the Internet**
One challenge that we ran into was how to make a bridge between the mesh network and an internet access point. At first, we were under the assumption that we would be able to connect by simultaneously connecting the root node to the mesh and the ap. However, the esp32 could only be connected to one network at once. One of the possibilities was to create a device that can understand the node network and communicate to firebase at the same time. What we ended up doing, because it was simpler in our eyes was to have a separate device connected to the root node in the mesh network. This device, called the bridge, communicates with the root node over serial and connects to a wireless AP to communicate with firebase.

  
**Conflicting Library Dependencies**
The two Arduino libraries that we used for Firebase and the Mesh Network both relied on the same library, ArduinoJson. The problem is that the much older Firebase library used version 5.xx of the ArduinoJson lib, and the Mesh lib used 6.xx. This ended up being okay because the code was separated on the bridge and root node, so the two libraries never needed to be used on the same device. Unfortunately, though, it made it so you would have to reconfigure the Arduino project libraries again to switch the arduinojson version every time you wanted to compile new code.

  
**Limited Hardware**
Because our idea involves a lot of hardware, we were limited to what hardware was already at my house (which, to be fair, is probably considerably more than most people). While there were enough microcontrollers, I did not have enough sensors for each one. I thought that I had more Adafruit BME680 gas and temperature sensors, but I could not find them. We ended up simulating the sensors in code by transmitting random values within a reasonable range.


## What's next for MbrNet


While we were certainly able to accomplish a lot in just two days, the path ahead is clear.

-   Add real sensors such as the Adafruit BME680 to communicate with the ESP32s over I2C.
    
-   Add weatherproof casings, batteries, and solar panels to each node so that they can last out in the wilderness.
    
-   Work with government agencies to create more meshes around California.
    
-   Set up better alert systems for civilians and firefighters when values in the database indicate a possible fire.
    
-   Create an easier way to provision new networks (set up location data for nodes, configure roots) that requires little technical knowledge.
    
-   Switch to a longer range wireless communication protocol such as LoRa so nodes can be further apart.