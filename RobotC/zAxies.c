#pragma config(Sensor, S1,     DIMU,           sensorI2CCustomFastSkipStates)
#include "drivers/dexterind-imu.h"

float z_val = 0.00;
float y_val = 0.00;
float x_val = 0.00;
float zAttitude = 0.00;
float yAttitude = 0.00;
float xAttitude = 0.00;

task testAxies(){

	int counts = 0;
  eraseDisplay();
	if (!DIMUconfigAccel(DIMU, DIMU_ACC_RANGE_2G))
    PlaySound(soundException);
	if(!DIMUconfigGyro(DIMU, DIMU_GYRO_RANGE_500))
    PlaySound(soundException);

  time1[T1] = 0;

  while(true){
  	while(time1[T1] <10)
  		wait1Msec(1);
  	time1[T1] = 0;
  	z_val = -1.68*DIMUreadGyroAxis(DIMU, DIMU_GYRO_Z_AXIS);
  	y_val = -1.68*DIMUreadGyroAxis(DIMU, DIMU_GYRO_Y_AXIS);
  	x_val = -1.68*DIMUreadGyroAxis(DIMU, DIMU_GYRO_X_AXIS);

  	if ( ( z_val < 1 ) && ( z_val > 0 ) ){
  		zAttitude += 0;
  		counts = counts + 1;
  		if (counts > 5){
  			if ( zAttitude <= 4 ){;
  				zAttitude = 0;
  			}
  			counts = 0;
  		}
  	}else{
  		zAttitude += ( z_val / 2 ) * 0.01;
  	}




  	//nxtDisplayTextLine(2, "%2.0f", zAttitude);
  	//nxtDisplayTextLine(3, "%f", z_val);
  	//nxtDisplayTextLine(4, "%2.0f", counts);
  }
}
