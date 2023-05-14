  
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLwnOKpbgp"
#define BLYNK_DEVICE_NAME "IOT ENERGY METER"

#include "EmonLib.h"   
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
 
EnergyMonitor emon;
#define vCalibration 106.8
#define currCalibration 0.52
BlynkTimer timer;
#define BLYNK_AUTH_TOKEN "oAqI1clecEoT9tkzj1d8oUrkP3tj0L9x" 

char auth[] =BLYNK_AUTH_TOKEN;
 
char ssid[] = "gokul";
char pass[] = "";
 
float kWh = 0;
unsigned long lastmillis = millis();

   

 
void myTimerEvent() {
    emon.calcVI(20, 2000);
  
    Serial.print("Vrms: ");
    Serial.print(emon.Vrms, 2);
    Serial.print("V");
    Blynk.virtualWrite(V0, emon.Vrms);
    Serial.print("\tIrms: ");
    Serial.print(emon.Irms, 4);
    Serial.print("A");
    Blynk.virtualWrite(V1, emon.Irms);
    Serial.print("\tPower: ");
    Serial.print(emon.apparentPower, 4);
    Serial.print("W");
    Blynk.virtualWrite(V2, emon.apparentPower);
    Serial.print("\tkWh: ");
    kWh = kWh + emon.apparentPower*(millis()-lastmillis)/3600000000.0;
    Serial.print(kWh, 4);
    Serial.print("kWh");
    Serial.print("\tAmount:");
    Serial.println(kWh*0);
    lastmillis = millis();
    Blynk.virtualWrite(V3, kWh);
    Blynk.virtualWrite(V4, kWh*0);

}
 
void setup() {
  Serial.begin(9600);
  emon.voltage(35, vCalibration, 1.9); 
  emon.current(34, currCalibration); 
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(5000L, myTimerEvent);
}
 
void loop() {
  Blynk.run();
  timer.run();
}
