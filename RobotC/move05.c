#pragma config(Sensor, S1,     HTMSSUMO,       sensorLightActive)
#pragma config(Sensor, S2,     us_old,         sensorSONAR)
#pragma config(Sensor, S3,     us_new,         sensorSONAR)
#pragma config(Sensor, S4,     DIMU,           sensorI2CCustomFastSkipStates)
#pragma config(Motor,  motorA,          RIGHT,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          LEFT,          tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Drivers, API's and Configs
#include "drivers/mindsensors-sumoeyes.h"
#include "drivers/dexterind-compass.h"
#include "sensorConfig/US_NEW.h"
#include "sensorConfig/US_OLD.h"
#include "drivers/dexterind-imu.h"
#include "sensorConfig/pollAxies.h"

// Function Defs
void turnRight();
void turnHardRight();
void turnLeft();
void turnHardLeft();
void allStall();
void allGo();
void allBack();
void allStop();
//void checkLeft();
//void checkRight();
void sonarObsticalCheck(int inType, int heading);
int calcHeading(int OriginHeading);

//Global Vars
tObstacleZone zone = 0;
int blockLeft = 0;
int blockRight = 0;


//Lets Get this thing moving!
task main() {
	// Start up the compas!
	if (DIMCinit(DIMU))
    PlaySound(soundException);
	wait10Msec(200);
	// Start up the two sonar sensors - read them via their config files
	StartTask(USNEW);
	StartTask(USOLD);
  // Set Sumo to Long Range
	MSSUMOsetShortRange(HTMSSUMO);
  while(true) {
  	blockLeft = 0;
		blockRight = 0;
//		zone = MSSUMOreadZone(HTMSSUMO);
    // Check front IR sensor LEFT FRONT RIGHT
//    switch (zone) {
//      case MSSUMO_FRONT:
      	allStop();
//      	break;
//      case MSSUMO_LEFT:
//      	turnRight();
//      	break;
//      case MSSUMO_RIGHT:
//      	turnLeft();
//      	break;
//      case MSSUMO_NONE:
//      	allGo();
//      	break;
//    }
    //wait1Msec(1000);
   	// Check left and right sonar sensors for objects
//   	sonarObsticalCheck(1, 0);
      	StopAllTasks();
  }
}



// Start movement functions

//Go Stright
void allGo(){ motor[RIGHT] = 50; motor[LEFT] = 50; }
//Reverse
void allBack(){ motor[RIGHT] = -50; motor[LEFT] = -50; }
//Stop Motors
void allStall(){ motor[RIGHT] = 0; motor[LEFT] = 0; }
//Curve turn right
void turnRight(){ motor[RIGHT] = 25; motor[LEFT] = 75; }
//Curve turn left
void turnLeft(){ motor[RIGHT] = 75; motor[LEFT] = 25; }
//Rotate right
void turnHardRight(){ motor[RIGHT] = -50; motor[LEFT] = 50; }
//Rotate left
void turnHardLeft(){ motor[RIGHT] = 50; motor[LEFT] = -50; }
//Calcutate heading
int calcHeading(int OriginHeading){
	if ( OriginHeading < 0 ){
		OriginHeading = abs( OriginHeading );
	} else if ( OriginHeading > 360 ){
		OriginHeading = ( OriginHeading - 360);
	} else {
		OriginHeading = OriginHeading;
	}
	return OriginHeading;
}
//Left/right sonar turns, curve and hard with compas turn ratio
void sonarObsticalCheck(int inType, int heading){
	int leftTarget = 0;
	int leftPreTarget = 0;
	int rightTarget = 0;
	int rightPreTarget = 0;


	leftTarget = calcHeading( heading - 90 );
	leftPreTarget = calcHeading( leftTarget + 10 );

	rightTarget = calcHeading( heading + 90 );
	rightPreTarget = calcHeading( rightTarget - 10 );



	int newRightTarget = 0;
	int originalHeading = 0;
	int newHeading = 0;
	int headingMod = 0;

	//originalHeading = round(DIMCreadHeading(DIMC));
	//newRightTarget = ( ( round(DIMCreadHeading(DIMC)) + 90 ) - originalHeading );


	/*
	// Find the left target
	leftTarget = ( heading - 90 );

	if ( leftTarget < 0 ){
		leftTarget = abs( leftTarget );
	} else if ( leftTarget > 360 ){
		leftTarget = ( leftTarget - 360);
	} else {
		leftTarget = leftTarget;
	}

	leftPreTarget = ( leftTarget - 10 );



	// find the right target
	rightTarget = ( heading + 90 );

	if ( rightTarget < 0 ){
		rightTarget = abs( rightTarget );
	} else if ( rightTarget > 360 ){
		rightTarget = ( rightTarget - 360);
	} else {
		rightTarget = rightTarget;
	}


/*

We're at: 338degs - we need to get to points 90degs on each side of this ... so


338 - 90 = 248
338 + 90 = 428 - 360 = 68



okay - so

if calcResult is greater than 360 - we need to take away 360 from calcResult to get the left (as we face to bot) turn target ...
and if the calc result is less than 0 than abs(calcResult) to get the target


						Front

						0deg
			---------------
			|             |
			|             |
90deg	|             | 260deg
			|             |
			|             |
			---------------
					180deg


*/





	switch ( inType ){
		case 1:
			if ( ( us_NewResult < 10 ) && ( us_OldResult > 10 ) ){
	    		//turnRight();
	    		//wait1Msec(200);
	    	}	else if ( ( us_NewResult > 10 ) && ( us_OldResult < 10 ) ) {
	    		//turnLeft();
	    		//wait1Msec(200);
	    	}
				break;
		case 2:
			if ( ( us_NewResult > 20 ) && ( us_OldResult < 20 ) ){

			//	while ( round(DIMCreadHeading(DIMC)) != rightTarget ){
						do{
							nxtDisplayCenteredTextLine(1, "RIGHT");
    					nxtDisplayCenteredTextLine(2, "yA %d", yA);
    					nxtDisplayCenteredTextLine(3, "xA %d", xA);
    					nxtDisplayCenteredTextLine(4, "zA %d", zA );
    					motor[RIGHT] = 10;
	  					motor[LEFT] = -10;
	  			}while( ( round(DIMCreadHeading(DIMU)) - originalHeading ) < 80 );

	  					//}while( ( round(DIMCreadHeading(DIMC)) < ( rightTarget - 5 ) ) && ( ( rightTarget + 5 ) > round(DIMCreadHeading(DIMC)) ) );
						//if ( round(DIMCreadHeading(DIMC)) > rightTarget ){
    				//	nxtDisplayCenteredTextLine(1, "RIGHT");
    				//	nxtDisplayCenteredTextLine(2, "T %d", rightTarget);
    				//	nxtDisplayCenteredTextLine(3, "P %d", rightPreTarget);
    				//	nxtDisplayCenteredTextLine(4, "H %d", round(DIMCreadHeading(DIMC)));
    				//	motor[RIGHT] = 50;
	  				//	motor[LEFT] = -50;
	  				//	//wait1Msec(200);
	    			//} else {
	    				motor[RIGHT] = 0;
	  					motor[LEFT] = 0;
	  					wait1Msec(10000);
	    			//	while ( round(DIMCreadHeading(DIMC)) != rightTarget ){
		    		//		nxtDisplayCenteredTextLine(1, "RIGHT");
		    		//		nxtDisplayCenteredTextLine(2, "T %d", rightTarget);
		    		//		nxtDisplayCenteredTextLine(3, "P %d", rightPreTarget);
		    		//		nxtDisplayCenteredTextLine(4, "H %d", round(DIMCreadHeading(DIMC)));
		    		//		motor[RIGHT] = 12;
			  		//		motor[LEFT] = -12;
			  		//		wait1Msec(100);
			  		//		motor[RIGHT] = 0;
				  	//		motor[LEFT] = 0;
			    	//		wait1Msec(200);
			  //  		}
	  			//}
    	//	}
	    /*
	    }	else if ( ( us_NewResult < 20 ) && ( us_OldResult > 20 ) ) {
					//while ( round(DIMCreadHeading(DIMC)) < ( leftTarget + 15 ) ){
				  // 		turnHardLeft();
				  // 	}
				  // 	allStall();
	    		//	wait1Msec(100);

	    			while ( round(DIMCreadHeading(DIMC)) > leftPreTarget ){
	    				nxtDisplayCenteredTextLine(1, "LEFT");
	    				nxtDisplayCenteredTextLine(2, "T %d", leftTarget);
	    				nxtDisplayCenteredTextLine(3, "P %d", leftPreTarget);
	    				nxtDisplayCenteredTextLine(4, "H %d", round(DIMCreadHeading(DIMC)));
	    				wait1Msec(100000);
		  					turnHardLeft();
	    				}

	    			while ( round(DIMCreadHeading(DIMC)) != leftTarget ){
		  				nxtDisplayCenteredTextLine(1, "LEFT");
	    				nxtDisplayCenteredTextLine(2, "T %d", leftTarget);
	    				nxtDisplayCenteredTextLine(3, "P %d", leftPreTarget);
	    				nxtDisplayCenteredTextLine(4, "H %d", round(DIMCreadHeading(DIMC)));
	    				wait1Msec(100000);
		  				motor[RIGHT] = -12;
		  				motor[LEFT] = 12;
		  				wait1Msec(100);
		  				motor[RIGHT] = 0;
			  			motor[LEFT] = 0;
		    			wait1Msec(200);
		    		}
	    	} else {
	    		//PlaySound(soundFastUpwardTones);
	    	}*/
				break;
}}
	}

// Check for object functions - LEFT AND RIGHT
//void checkLeft(){
//		zone = MSSUMOreadZone(HTMSSUMO);
//		switch ( zone ) {
//				case MSSUMO_FRONT: blockLeft = 1; nxtDisplayCenteredBigTextLine(6, "FRONT %d", blockLeft); break;
//	      case MSSUMO_LEFT:  blockLeft = 0; nxtDisplayCenteredBigTextLine(6, "LEFT %d", blockLeft);  break;
//	      case MSSUMO_RIGHT: blockLeft = 0; nxtDisplayCenteredBigTextLine(6, "RIGHT %d", blockLeft); break;
//	      case MSSUMO_NONE:  blockLeft = 0; nxtDisplayCenteredBigTextLine(6, "NONE %d", blockLeft);  break;
//		}
//		wait1Msec(50);
//	}
//void checkRight(){
//		zone = MSSUMOreadZone(HTMSSUMO);
//		switch ( zone ) {
//				case MSSUMO_FRONT: blockRight = 1; nxtDisplayCenteredBigTextLine(6, "FRONT %d", blockRight); break;
//	      case MSSUMO_LEFT:  blockRight = 0; nxtDisplayCenteredBigTextLine(6, "LEFT %d", blockRight);  break;
//	      case MSSUMO_RIGHT: blockRight = 0; nxtDisplayCenteredBigTextLine(6, "RIGHT %d", blockRight); break;
//	      case MSSUMO_NONE:  blockRight = 0; nxtDisplayCenteredBigTextLine(6, "NONE %d", blockRight);  break;
//		}
//		wait1Msec(50);
//	}



void allStop(){
	allStall();
	wait1Msec(200);
	sonarObsticalCheck(2, round(DIMCreadHeading(DIMU)));
	wait1Msec(200);
}
/*
	turnHardRight();
	wait1Msec(750);
	allStall();
	checkLeft();
	wait1Msec(200);
	turnHardLeft();
  wait1Msec(1500);
  allStall();
	checkRight();
	wait1Msec(200);
	turnHardRight();
	wait1Msec(750);
	allStall();
	wait1Msec(200);
	 if ( ( blockLeft==1 ) && ( blockRight==1 ) ){
		allBack();
		wait1Msec(500);
		turnHardLeft();
		wait1Msec(1400);
		allStall();
  	wait1Msec(200);
	} else if ( ( blockLeft==0 ) && ( blockRight==1 ) ){
    turnHardRight();
		wait1Msec(250);
		allStall();
  	wait1Msec(200);
	} else if ( ( blockLeft==1 ) && ( blockRight==0 ) ){
  	turnHardLeft();
  	wait1Msec(250);
		allStall();
  	wait1Msec(200);
	} else {
		int turnRan = random(100);
		if (turnRan > 50){
	  	turnHardRight();
			wait1Msec(250);
	    }else{
	      turnHardLeft();
	      wait1Msec(250);
	    }
	}
}
*/



/*
 * $Id: mindsensors-sumoeyes-test1.c 123 2012-11-02 16:35:15Z xander $
 */