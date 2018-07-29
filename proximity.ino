/* 
sensor box to monitor and report:
LDR light-level detection
SPL avg. audio level from freetronics mic module
PIR proximity sensor
 
sending OSC messages over ethernet.

REQUIRES 12V power to drive the PIR sensor adequately.
 */

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>    
#include <OSCMessage.h>

EthernetUDP Udp;
IPAddress ip(x,x,x,x);
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress targetIp(x,x,x,x);    

//Arduino sensor pins
int pirPin = 2;
int LDR_Pin = A0;
int SPL_Pin = A5;

//init
int act = 0;
int spl = 0;
int ldr = 0;

int SPLthresh= 1;
int LDRthresh= 1;

void setup() {
  //enet
  Ethernet.begin(mac,ip);
  Udp.begin(57121); //target port
  //serial
  Serial.println("inited"); 
  Serial.begin(9600); 
  act = 0;
  LDRthresh = 1;
  SPLthresh = 1;
}

//PIR output goes LOW when motion detected
void loop() {
  if(digitalRead(pirPin) == LOW) {
    act = 1;   
  } else {
    act = 0;
  }
  OSCMessage msg("/activity");
  msg.add(act);
  Udp.beginPacket(targetIp, targetPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();  
    // debugging:
    //Serial.print(" activity: "); 
    //Serial.print(act); 
    // Serial.println("");
  
  //LDR - low light = higher value
  ldr = analogRead(LDR_Pin); 
  if(ldr > LDRthresh) {
    OSCMessage msg("/light");
    msg.add(ldr);
    Udp.beginPacket(targetIp, targetPort);
    msg.send(Udp); 
    Udp.endPacket();
    msg.empty();
    // debugging:
    //Serial.print("LDR: ");
    //Serial.print(spl);
  } 
  //SPL redings
  spl = analogRead(SPL_Pin);
  if(spl > SPLthresh) {
    OSCMessage msg("/sound");
    msg.add(spl);
    Udp.beginPacket(targetIp, targetPort);
    msg.send(Udp); 
    Udp.endPacket(); 
    msg.empty();  
    // debugging:
    //Serial.print(" SPL: ");
    //Serial.print(spl);
    //Serial.print("");
  }  
  delay(4000);  
}
