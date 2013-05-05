


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
  
   do {delay(100);}while(!blueToothSerial.available());  
   if(blueToothSerial.available()){
     for (int i = 0;i<=41;i++){
      /*
      check if there's any data sent from the remote bluetooth shield
      */
      recvChar = blueToothSerial.read();
      Serial.print(recvChar);
      delay(50);
    }
   }
   Serial.println("NXT BlueTooth Connected...");  
   Serial.println ("Press GO button to continue");
   nxshield.waitForButtonPress(BTN_GO);
    while(1){
      /* 
        OLD DELAY > int myDelay = 500;
        NOW LETS SEE HOW FAST THIS BABY CAN RUN!
        100 is too fast :-(
        ...
        Well maybe not that fast? - trying at 10?????
       */
      int myDelay = 35;
      if(blueToothSerial.available()){
      recvChar = blueToothSerial.read();
      Serial.println(recvChar);
      }
      
      
      char ReturnDataPointer[2];
      char ReturnReadings[1];
      int thisSensorReading = sonar1.getDist();
      
      if (touch1.isPressed()){
        ReturnDataPointer[0] = 63;
        ReturnDataPointer[1] = 65;
        blueToothSerial.print(ReturnDataPointer);
        delay(myDelay);
      } else { 
        if (!touch1.isPressed()){
          ReturnDataPointer[0] = 63;
          ReturnDataPointer[1] = 66;
          blueToothSerial.print(ReturnDataPointer);
          delay(myDelay);
       } 
      }
      if (touch2.isPressed()){
        ReturnDataPointer[0] = 63;
        ReturnDataPointer[1] = 67;
        blueToothSerial.print(ReturnDataPointer);
        delay(myDelay);
      } else { 
        if (!touch2.isPressed()){
          ReturnDataPointer[0] = 63;
          ReturnDataPointer[1] = 68;
          blueToothSerial.print(ReturnDataPointer);
          delay(myDelay);
        }
      }
      
      if (thisSensorReading > 20){
        ReturnDataPointer[0] = 63;
        ReturnDataPointer[1] = 69;
        blueToothSerial.print(ReturnDataPointer);
        delay(myDelay);
      } else { 
        if (thisSensorReading < 20){
          ReturnDataPointer[0] = 63;
          ReturnDataPointer[1] = 70;
          blueToothSerial.print(ReturnDataPointer);
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




