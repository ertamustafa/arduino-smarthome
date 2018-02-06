
const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data
char tempChars[numChars];       // temporary array for use when parsing

      // variables to hold the parsed data
char messageFromPC[numChars] = {0};
int integerFromPC = 0;
char V0;
int V1;
//float floatFromPC = 0.0;

boolean newData = false;

void setup() {
    Serial.begin(9600);
    Serial.println("<Arduino is ready>");
}

void loop() {
    recvWithEndMarker();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
//         if (messageFromPC == "T1") {
//              V1 = integerFromPC;
//    }  
        showNewData();
        showParsedData();
        newData = false;
    }
}

//============

void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = ',';
    char rc;
    
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;   
        }
    }
}
//============

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,":");      // get the first part - the string
    strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC
 
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    integerFromPC = atoi(strtokIndx);     // convert this part to an integer

//    strtokIndx = strtok(NULL, ",");
//    floatFromPC = atof(strtokIndx);     // convert this part to a float
}
//============

void showNewData() {
    if (newData == true) {
   //     Serial.print("This just in ... ");
        Serial.println(receivedChars);
        Serial.print("\n");
        newData = false;
    }
}
//============

void showParsedData() {
    Serial.print("Message ");
    Serial.println(messageFromPC);
    Serial.print("Integer ");
    Serial.println(integerFromPC);
    Serial.print("V1: ");
    Serial.println(V1);
    Serial.print("----------");
    Serial.print("\n");
//    Serial.print("Float ");
//    Serial.println(floatFromPC);
}

/* 
 Ich muss so etwas schicken T1:23,T2:16384,T3:2025,
 und so bekommen 
 <Arduino is ready>
T1:23

Message T1
Integer 23
V1: 0
----------
T2:16384

Message T2
Integer 16384
V1: 0
----------
T3:2025

Message T3
Integer 2025
V1: 0
----------
 */
