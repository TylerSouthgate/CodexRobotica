#pragma config(Sensor, S1,     sRight,         sensorSONAR)
#pragma config(Sensor, S2,     sLeft,          sensorSONAR)
#pragma config(Sensor, S3,     touch,          sensorTouch)
#pragma config(Motor,  motorB,          turntable,     tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          foot,          tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void runForward();
void StopAndTurn(int which);
void resetFeet(int which2, int turnRate);

void runForward()
{
	motor[motorC] = -100;
	return;
}

void StopAndTurn(int which)
{
	do
		{
			motor[motorC] = 50;
		}while(SensorValue[touch] == 0);
	motor[motorC] = 0;
	return;
}

void resetFeet(int which2, int turnRate){
	nMotorEncoder[motorC] = 0;
	while(nMotorEncoder[motorC] < 800)
		{
			motor[motorC] = 50;
		}
	motor[motorC] = 0;

	if(which2 == 1)
			{
				nMotorEncoder[motorB] = 0;
				while(nMotorEncoder[motorB] > -turnRate)
					{
						motor[motorB] = -75;
					}
					motor[motorB] = 0;
			}
			else
			{
				nMotorEncoder[motorB] = 0;
				while(nMotorEncoder[motorB] < turnRate)
					{
						motor[motorB] = 75;
					}
					motor[motorB] = 0;
			}
		return;
}

task main()
{
	int range = 25;
	int turnRange = ( range + 5 );
	int reverseRange = ( turnRange - 5 );
	while (true){
		runForward();
		if (SensorValue[sRight] < range){
			StopAndTurn(1);
			resetFeet(1, 1400);
		}else if (SensorValue[sLeft] < range){
			StopAndTurn(0);
			resetFeet(0, 1400);
		}else if ((SensorValue[sLeft] < range) && (SensorValue[sRight] < range)){
			StopAndTurn(0);
			resetFeet(0, 3000):
		}
	}
}