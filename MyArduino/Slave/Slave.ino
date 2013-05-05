#include <Wire.h>
#include <NXShield.h>
#include <NXTTouch.h>
#include <NXTLight.h>
#include <SoftwareSerial.h>   //Software Serial Port
#define RxD 6
#define TxD 7
 
#define DEBUG_ENABLED  1
 
SoftwareSerial blueToothSerial(RxD,TxD);
NXShield nxshield;
NXTTouch touch1;

void setup() 
{ 
  Serial.begin(9600);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  setupBlueToothConnection();
  delay(500);
  nxshield.init( SH_HardwareI2C );
  delay(500);
  Serial.println ("Press GO button to continue");
  nxshield.waitForButtonPress(BTN_GO);
  touch1.init( &nxshield, SH_BAS1 );
  Serial.println("Waiting for NXT BlueTooth...");
 delay(500);  
} 
 
void loop() 
{ 
  char str[256];
  bool touch_status;
  bool last_status;
  char recvChar;
  //int i = 0;
  //for (int i = 0;i<=33;i++){
  
    do {delay(100);}while(!blueToothSerial.available());  
   if(blueToothSerial.available()){
     for (int i = 0;i<=41;i++){
      //check if there's any data sent from the remote bluetooth shield
      recvChar = blueToothSerial.read();
      Serial.print(recvChar);
      delay(100);
      
    }
   }
   Serial.println("NXT BlueTooth Connected...");  
   Serial.println ("Press GO button to continue");
  nxshield.waitForButtonPress(BTN_GO);
    while(1){
      if(blueToothSerial.available()){
      recvChar = blueToothSerial.read();
      Serial.println(recvChar);
      }
      if (touch1.isPressed()){
        Serial.println("touch1: is pressed : TRUE");
        char readings[3];
        readings[0] = 65;
        readings[1] = 66;
        readings[2] = 67;
        blueToothSerial.print(readings);
        Serial.println(readings[1]);
        delay(500);
        blueToothSerial.flush();
      }else{
        Serial.println("touch1: is pressed : FALSE");
        char readingsTwo[3];
        readingsTwo[0] = 68;
        readingsTwo[1] = 69;
        readingsTwo[2] = 70;
        blueToothSerial.print(readingsTwo);
        Serial.println(readingsTwo[1]);
        delay(500);
        blueToothSerial.flush();
      }
      
      
      
      //touch_status = touch1.isPressed();
      //if ( touch_status != last_status ) {
      //      sprintf (str, "touch1: is pressed : %s", touch_status?"true":"false");
      //      Serial.println(str);
      //      char readings[]= {65};
      //      //blueToothSerial.print(78, HEX);
      //      blueToothSerial.print(readings);
      //      Serial.println(readings);
      //      //Serial.println(78, HEX);
      //      last_status = touch_status;
      //    }
      	  
      
    }
//    if(Serial.available()){//check if there's any data sent from the local serial terminal, you can add the other applications here
    //  recvChar  = Serial.read();
      
  //    int readings[]= {65};
      //readings[0] = 65;
    //  blueToothSerial.print(readings[0], 1);
   
   }
  //}
  
  
  
  
  
//} 
 
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




