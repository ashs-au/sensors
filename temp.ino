#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>    
#include <OSCMessage.h>

EthernetUDP Udp;
IPAddress ip(x,x,x,x);
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress targetIp(x,x,x,x);

#include "DHT.h"  

//Arduino sensor pins
#define DHT1PIN 3 
#define DHT2PIN 5 
#define DHT1TYPE DHT22 
#define DHT2TYPE DHT22 

DHT dht1(DHT1PIN, DHT1TYPE); 
DHT dht2(DHT2PIN, DHT2TYPE);

void setup() { 
  //enet
  Ethernet.begin(mac,ip);
  Udp.begin(57121); //target OSC port
    //serial
  Serial.begin(9600); 
  Serial.println("DHTxx init!");   
  dht1.begin(); 
  dht2.begin(); 
}   

void loop() { 
  // Reading temperature or humidity takes about 250 milliseconds 
  // Sensor readings may also be up to 2 seconds 'old' 
  float t1 = dht1.readTemperature();
  float t2 = dht2.readTemperature();  
  // check if returns are valid, else - sensor error
  if (isnan(t1)) { 
    Serial.println("Failed to read from DHT #1"); 
  } else { 
    OSCMessage msg("/cold");
    msg.add(t1);
    Udp.beginPacket(targetIp, targetPort);
    msg.send(Udp); 
    Udp.endPacket(); 
    msg.empty();  
    Serial.print("Temp 1: "); 
    Serial.print(t1); 
    //Serial.println(" *C"); //testing
  } 
  if (isnan(t2)) { 
    Serial.println("Failed to read from DHT #2"); 
  } else {  
    OSCMessage msg("/heat");
    msg.add(t2);
    Udp.beginPacket(targetIp, targetPort);
    msg.send(Udp);
    Udp.endPacket(); //close the packet
    msg.empty(); 
    Serial.print("Temp 2: "); 
    Serial.print(t2);
    //Serial.println(" *C"); //testing
  } 
   Serial.println(); 
   delay(2000);
}