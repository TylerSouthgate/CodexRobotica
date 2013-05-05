


#include <Wire.h>
#include <NXShield.h>
#include <NXTTouch.h>
#include <NXTUS.h>
#include <SoftwareSerial.h>   //Software Serial Port
#define RxD 6
#define TxD 7
 
#define DEBUG_ENABLED  1
 
SoftwareSerial blueToothSerial(RxD,TxD);

NXShield nxshield;
NXTTouch touch1;
NXTTouch touch2;
NXTUS sonar1;

void setup() 
{ 
  Serial.begin(9600);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  setupBlueToothConnection();
  delay(500);
  nxshield.init( SH_HardwareI2C );
  //nxshield.init( SH_SoftwareI2C );
  delay(500);
  Serial.println ("Press GO button to continue");
  nxshield.waitForButtonPress(BTN_GO);
  touch1.init( &nxshield, SH_BAS1 );
  touch2.init( &nxshield, SH_BBS1 );

  //BY ORDER ORDER OF THE HIGH MASTER OF ROBOTS
  //DO NOT CHANGE THE FOLLOWING LINE OF CODE
  sonar1.init( &nxshield, SH_BAS2 );
  
  
  Serial.println("Waiting for NXT BlueTooth...");
  delay(500);
} 
 
void loop() 
{ 
  char str[256];
  bool touch_status;
  bool last_status;
  char recvChar;
  int ledPins[] = {3,5,6,9,10,11};
  //int i = 0;
  //for (int i = 0;i<=33;i++){
  
    do {delay(100);}while(!blueToothSerial.available());  
   if(blueToothSerial.available()){
     for (int i = 0;i<=41;i++){
      //check if there's any data sent from the remote bluetooth shield
      recvChar = blueToothSerial.read();
      Serial.print(recvChar);
      delay(50);
    }
   }
   Serial.println("NXT BlueTooth Connected...");  
   Serial.println ("Press GO button to continue");
   nxshield.waitForButtonPress(BTN_GO);
    while(1){
      // OLD DELAY > int myDelay = 500;
      // NOW LETS SEE HOW FAST THIS BABY CAN RUN!
      // 100 os too fast :-(
      int myDelay = 150;
      if(blueToothSerial.available()){
      recvChar = blueToothSerial.read();
      Serial.println(recvChar);
      }
      
      
      char ReturnReadings[1];
      int thisSensorReading = sonar1.getDist();
      
      if (touch1.isPressed()){
        Serial.println("touch1: is pressed");
        ReturnReadings[0] = 65;
        blueToothSerial.print(ReturnReadings);
        delay(myDelay);
      } else { 
        if (!touch1.isPressed()){
          Serial.println("touch1: is NOT pressed");
          ReturnReadings[0] = 66; 
          blueToothSerial.print(ReturnReadings);
          delay(myDelay);
        } 
      }
      if (touch2.isPressed()){
        Serial.println("touch2: is pressed");
        ReturnReadings[0] = 67;
        blueToothSerial.print(ReturnReadings);
        delay(myDelay);
      } else { 
        if (!touch2.isPressed()){
          Serial.println("touch2: is NOT pressed");
          ReturnReadings[0] = 68;  
          blueToothSerial.print(ReturnReadings);
          delay(myDelay);
        }
      }
      
      if (thisSensorReading > 20){
        Serial.println("sonar1: OUT OF RANGE");
        sprintf (str, "sonar1: Obstacle at: %d mm", thisSensorReading );
        Serial.println(str);
        ReturnReadings[0] = 69;
        blueToothSerial.print(ReturnReadings);
        delay(myDelay);
      } else { 
        if (thisSensorReading < 20){
          Serial.println("sonar1: IN RANGE");
          sprintf (str, "sonar1: Obstacle at: %d mm", thisSensorReading );
          Serial.println(str);
          ReturnReadings[0] = 70;
          blueToothSerial.print(ReturnReadings);
          delay(myDelay);
        }
      }
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
    }
   }
 
void setupBlueToothConnection()
{
  blueToothSerial.begin(38400); //Set BluetoothBee BaudRate to default baud rate 38400
  blueToothSerial.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
  blueToothSerial.print("\r\n+STNA=SeeedBTSlave\r\n"); //set the bluetooth name as "SeeedBTSlave"
  blueToothSerial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
  blueToothSerial.print("\r\n+STPIN=1234\r\n");//Set SLAVE pincode"1234"
  //blueToothSerial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
  delay(2000); // This delay is required.
  blueToothSerial.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
  Serial.println("The slave bluetooth is inquirable!");
  delay(2000); // This delay is required.
  blueToothSerial.flush();
}




