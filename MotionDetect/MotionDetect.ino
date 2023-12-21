#include "secrets.h"
#include "WiFi.h"
#include "AdafruitIO_WiFi.h"

const int SensorSignal = 33; //Signal output.  
int sensorValue = 0; 

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASSWORD);

//Connect to Wifi.
void connectWifi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!!");
}

//Connect to Adafruit IO.
void connectIo(){
  io.connect();
  Serial.print("Connecting to Adafruit IO");
  while(io.status() < AIO_CONNECTED){
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConnected to Adafruit IO!!");
}

void setup() { 
  Serial.begin(115200);
  connectWifi();
  connectIo();

  pinMode(SensorSignal, INPUT); // declare digital pin 33 as input.
} 

void loop(){ 
  io.run();

  sensorValue = digitalRead(SensorSignal); // read the value of pin 33, should be high or low 
  if (sensorValue == HIGH) {
    AdafruitIO_Feed *motion = io.feed("motion");
    Serial.println("Motion detected. Sending to Adafruit!");
    motion->save(sensorValue);
 } 

  delay(1000);
}
