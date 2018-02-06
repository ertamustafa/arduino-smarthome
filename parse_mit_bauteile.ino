#include "WiFiEsp.h"
#include <Servo.h>
#include <RCSwitch.h>

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(6, 7); // RX, TX
#endif

char ssid[] = "HTL-Schueler";            // your network SSID (name)
char pass[] = "1Schueler";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "192.168.27.153";  // server ip; 

// Initialize the Ethernet client object
WiFiEspClient client;

char message [255]; //globale Variable

int led1_pin = 22; //digital
int led1;
int led2_pin = 23; //digital
int led2;
int led3_pin = 24; //digital
int led3;
int led4_pin = 25; //digital
int led4;
int led5_pin = 26; //digital
int led5;
        int vnt_pin = 13; //pmw
        int vnt;
int pw_pin = A0; //analog 
int pwStatus; 
int ledPW = 27; //digital
        int rs_pin = A1; //analog
        int rsStatus;
        int buzzRS = 28; //digital
Servo srvF1; //pmw
int posF1;  
Servo srvF2; //pmw
int posF2;
Servo srvG; // pmw
int posG;
Servo srvT; //pmw
int posT;
        RCSwitch mySwitch = RCSwitch();
        
        int hg;
        int ka;
int t1_pin = A2; //analog
int t1Status;
int t2_pin = A3; //analog
int t2Status;
int t3_pin = A4; //analog
int t3Status;
        int pir = 7; //digital for some reason !!!!!!
        int pirStatus;
        int buzzPIR = 29; //digital
void nextLine(char term) {        // nextLine function
    int pos = 0;
    char c; 
    do {
      
      while(!client.available()) delay(1);
      
      c = client.read();
     // Serial.println(c);
      
      if(c == term) 
        message[pos] = '\0';
      
      else        message[pos] = c;
      
      pos++;
    } while(c!=term);
}

void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);
  // initialize serial for ESP module
  pinMode(led1_pin,OUTPUT);
  pinMode(led2_pin,OUTPUT);
  pinMode(led3_pin,OUTPUT);
  pinMode(led4_pin,OUTPUT);
  pinMode(led5_pin,OUTPUT);
  pinMode(vnt_pin, OUTPUT);
  pinMode(pw_pin, INPUT);
  pinMode(ledPW, OUTPUT);
  pinMode(rs_pin, INPUT);
  pinMode(buzzRS, OUTPUT);
  //servo pin und position declarieren
  srvF1.attach(12);
  srvF2.attach(11);
  srvG.attach(10);
  srvT.attach(9);
  mySwitch.enableTransmit(31);
  pinMode(t1_pin, INPUT);
  pinMode(t2_pin, INPUT);
  pinMode(t3_pin, INPUT);
  pinMode(pir, INPUT);
  pinMode(buzzPIR, OUTPUT);  
  Serial1.begin(115200);
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data
  Serial.println("You're connected to the network");

  printWifiStatus();
   Serial.println();
  Serial.println("Starting connection to server...");
  // if you get a connection, report back via serial
  if (client.connect(server, 50004)) {
  Serial.println("Connected to server");
  
  }
  
  client.println("login:Client:1234"); //login with Username and Password
  client.flush();

  nextLine('\n');
  Serial.println(message);
}

void loop()
{

  client.println("Get"); //get_state in Server senden
  client.flush();

  nextLine('\n');
  Serial.println(message);    //get_state_accepted receive
  delay(100);
  
  nextLine('\n');
  Serial.println(atoi(message));
  int  led1 = atoi(message);    //Status of Led1   received
     
  nextLine('\n');
  Serial.println(atoi(message));
  int led2 = atoi(message);

  nextLine('\n');
  Serial.println(atoi(message));
  int led3 = atoi(message);

  nextLine('\n');
  Serial.println(atoi(message));
  int led4 = atoi(message);

  nextLine('\n');
  Serial.println(atoi(message));
  int led5 = atoi(message);


  nextLine('\n');
  Serial.println(atoi(message));
  int posF1 = atoi(message);

  nextLine('\n');
  Serial.println(atoi(message));
  int posF2 = atoi(message);

   nextLine('\n');
  Serial.println(atoi(message));
  int posG = atoi(message);

   nextLine('\n');
  Serial.println(atoi(message));
  int posT = atoi(message);

   nextLine('\n');
  Serial.println(atoi(message));
  int hg = atoi(message);

   nextLine('\n');
  Serial.println(atoi(message));
  int ka = atoi(message);

    nextLine('\n');
  Serial.println(atoi(message));
  int vnt = atoi(message);
  
  // if there are incoming bytes available
  // from the server, read them and print them
  /*while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  delay(200);


  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  delay(200);
  client.println("logout");
  client.flush();

  delay(200);

  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  
*/
   delay(1000);
   digitalWrite(led1_pin, led1);// wegen high muss man hier schreiben den wert von led1 die eingesetzt wir
  digitalWrite(led2_pin, led2);
  digitalWrite(led3_pin, led3);
  digitalWrite(led4_pin, led4);
  digitalWrite(led5_pin, led5);
  // if the server's disconnected, stop the client
  if (!client.connected()) {
    Serial.println();
    Serial.println("Disconnecting from server...");
    client.stop();

 
  }
}


void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
