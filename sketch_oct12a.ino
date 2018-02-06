
#include <WiFiClient.h>
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(18, 19); // RX, TX
#endif

const char* ssid = "ALBtelecom-beni";
const char* pass = "12345678a";
const char* host = "192.168.40.1";
const int status = WL_IDLE_STATUS;
void setup() {
  delay(500);
  Serial.begin(9600);
  Serial1.begin(115200);
  // initialize ESP module
  WiFi.init(&Serial1);
  Serial.println();
  Serial.print("conecting to: ");
  Serial.println(ssid);
  Serial.println("Try to connect to server: ");
  Serial.println(host);
  
 
  delay(1000);
  status=WiFi.begin(ssid, pass);
  //IPAddress subnet(255,255,255,0);
  //WiFi.config(IPAddress(192,168,1,150),IPAddress(192,168,1,10),subnet);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("My IP: ");
  Serial.println(WiFi.localIP());
  long rssi = WiFi.RSSI();
  Serial.print("RSSI: ");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void loop() {

  WiFiClient client;
  
  if (!client.connect(host,3000)) { //The problem start here
    Serial.println(".");
    return;
  }
  
  Serial.println();
  Serial.print("Conected to IP: ");
  Serial.println(host);

  Serial.println("Sending string to server: ");
  client.println("OK");
  delay(100);
  
  String line = client.readStringUntil('\n');
  Serial.print(line);

  Serial.println();
  Serial.println("Closing connection");
  client.flush();
  client.stop();
  Serial.println("Connection Closed");
  
}
