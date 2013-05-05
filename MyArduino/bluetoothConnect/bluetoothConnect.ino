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
  Serial.println("Off We Go!");
} 

bool lastTouch, touchPressed;
 
void loop() 
{ 
  char recvChar;
  char str[256];
  touchPressed = touch1.isPressed();
  
  if ( touchPressed != lastTouch ) {
    if ( touchPressed == true ) {
        //Serial.println( "Touched" );
        blueToothSerial.flush();
        blueToothSerial.print(touchPressed);
        } //else {
        //blueToothSerial.flush();
       // blueToothSerial.print(touchPressed);
      //}
    lastTouch = touchPressed;
  }
  if (blueToothSerial.available())
    Serial.write(blueToothSerial.read());
  //if (Serial.available())
  //  blueToothSerial.write(Serial.read());
 
 
 
  
  //  if(blueToothSerial.available()){//check if there's any data sent from the remote bluetooth shield
  //    recvChar = blueToothSerial.read();
  //    Serial.println(recvChar);
  //    delay(500); 
  //  }
  
} 
 
void setupBlueToothConnection()
{
  blueToothSerial.begin(38400); //Set BluetoothBee BaudRate to default baud rate 38400
  blueToothSerial.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
  blueToothSerial.print("\r\n+STNA=SeeedBTSlave\r\n"); //set the bluetooth name as "SeeedBTSlave"
  blueToothSerial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
  blueToothSerial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
  delay(2000); // This delay is required.
  blueToothSerial.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
  Serial.println("The slave bluetooth is inquirable!");
  delay(2000); // This delay is required.
  blueToothSerial.flush();
}
