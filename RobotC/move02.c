#pragma config(Sensor, S1,     Tleft,               sensorTouch)
#pragma config(Sensor, S2,     Tright,              sensorTouch)
#pragma config(Sensor, S3,     TopLight,            sensorCOLORNONE)
#pragma config(Sensor, S4,     sonarSensor,         sensorSONAR)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void rangeResponce(int inTurnRange, int inReversRange);
void lowRangeResponce(int inReversRange);
void touchResponceL();
void touchResponceR();
void lightResponce();

int turnCount = 0;
int fSpeed = 60;
int rSpeed = -60;


task main{
	int range = 25;
	int turnRange = ( range + 5 );
	int reverseRange = ( turnRange - 5 );
	int senTest = 0;
	int senTest2 = 0;
	while(true){
	  SensorType[TopLight] = sensorCOLORNONE;
	  motor[motorB] = fSpeed;
		motor[motorC] = fSpeed;
		wait1Msec(50);

		if (SensorValue[sonarSensor] < reverseRange){
		  SensorType[TopLight] = sensorCOLORRED;
		  lowRangeResponce(reverseRange);
		  wait1Msec(250);
		} else if (SensorValue[sonarSensor] < range){
		  rangeResponce(turnRange, reverseRange);
		  wait1Msec(250);
		}
	  if (SensorValue[Tleft] == 1){
			touchResponceL();
		}
		if (SensorValue[Tright] == 1){
			touchResponceR();
		}
		//if (SensorValue[TopLight] < 10){
		//  lightResponce();
		//}
  }
}

void lowRangeResponce(int inReversRange){
  turnCount = ( turnCount + 1 );
  while	(SensorValue[sonarSensor] < ( inReversRange ) )
    {

			motor[motorB] = rSpeed;
	    motor[motorC] = rSpeed;
	    wait1Msec(350);
	    int turnRan = random(100);
	    if (turnRan > 50){
	      motor[motorB] = rSpeed;
	      motor[motorC] = fSpeed;
	      wait1Msec(350);
	    }else{
	      motor[motorB] = fSpeed;
	      motor[motorC] = rSpeed;
	      wait1Msec(350);
	    }
    }
}

void rangeResponce(int inTurnRange, int inReversRange){
  turnCount = ( turnCount + 1 );
  while (SensorValue[sonarSensor] < inTurnRange )
		{
		  int turnRan = random(100);
			if (SensorValue[sonarSensor] < inReversRange){
			  lowRangeResponce(inReversRange);
			} else if (turnRan >= 50)
				{
						while (SensorValue[sonarSensor] < inTurnRange )
							{
							  SensorType[TopLight] = sensorCOLORBLUE;
								motor[motorB] = fSpeed;
								motor[motorC] = rSpeed;
							}
				}
				else
				{
					while (SensorValue[sonarSensor] < inTurnRange )
						{
							SensorType[TopLight] = sensorCOLORBLUE;
							motor[motorB] = rSpeed;
							motor[motorC] = fSpeed;
						}
			  }
  }
}

void touchResponceL(){
  SensorType[TopLight] = sensorCOLORGREEN;
	turnCount = ( turnCount + 1 );
 	motor[motorB] = rSpeed;
	motor[motorC] = rSpeed;
	wait1Msec(350);
	motor[motorB] = fSpeed;
	motor[motorC] = rSpeed;
	wait1Msec(350);
}
void touchResponceR(){
	SensorType[TopLight] = sensorCOLORGREEN;
	turnCount = ( turnCount + 1 );
  motor[motorB] = rSpeed;
	motor[motorC] = rSpeed;
	wait1Msec(350);
	motor[motorB] = rSpeed;
	motor[motorC] = fSpeed;
	wait1Msec(350);
}
void lightResponce(){
	motor[motorB] = rSpeed;
	motor[motorC] = fSpeed;
	wait1Msec(350);
	motor[motorB] = fSpeed;
	motor[motorC] = fSpeed;
	wait1Msec(350);
}
