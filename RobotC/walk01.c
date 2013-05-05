#pragma config(Sensor, S1,     Tleft,               sensorTouch)
#pragma config(Sensor, S2,     Tright,              sensorTouch)
#pragma config(Sensor, S3,     TopLight,            sensorCOLORNONE)
#pragma config(Sensor, S4,     sonarSensor,         sensorSONAR)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void feetSet();
void walkF();

int turnCount = 0;
int fSpeed = 45;
int rSpeed = -45;


task main{
	int range = 25;
	int turnRange = ( range + 5 );
	int reverseRange = ( turnRange - 5 );
	int senTest = 0;
	int senTest2 = 0;
	while(true){
		feetSet();
		//walkF();
		wait1Msec(500);
  }
}

void feetSet(){
	motor[motorB] = fSpeed;
	motor[motorC] = fSpeed;
	if ( SensorValue[Tleft] == 1 ){
		motor[motorB] = 0;
	}
	if (SensorValue[Tright] == 1){
		motor[motorC] = 0;
	}
	nMotorEncoderTarget[motorB] = 180;
	motor[motorB] = fSpeed;

}
void walkF(){
	nMotorEncoderTarget[motorB] = 0;
	motor[motorB] = fSpeed;
	if (nMotorEncoderTarget[motorB] == 180){
		motor[motorB] = 0;
		wait1Msec(10);
	}
	motor[motorB] = fSpeed;
	motor[motorC] = fSpeed;
}


//task main () {
//  nMotorEncoderTarget[motorA] = 100;
//  motor[motorA] = 50;
//  while(nMotorRunState[motorA] != runStateIdle) {
//    wait1Msec(10);
//  }
//  PlaySound(soundBeepBeep);
//  while(bSoundActive) {
//    wait1Msec(10);
//  }
//}