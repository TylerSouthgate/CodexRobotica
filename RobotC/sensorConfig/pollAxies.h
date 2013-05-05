float xV,yV,zV;
float xA,yA,zA;
/*
float xVa,yVa,zVa;
float xAa,yAa,zAa;
*/
task pAxies(){
	//Gyro Vars
	int xC=0;
	int yC=0;
	int zC=0;
  xA=0;
  yA=0;
  zA=0;
  xV=0;
  yV=0;
  zV=0;

  //Accel Vars
  /*
  int xCa=0;
	int yCa=0;
	int zCa=0;
  xAa=0;
  yAa=0;
  zAa=0;
  xVa=0;
  yVa=0;
  zVa=0;
	*/
  if(!DIMUconfigAccel(DIMU, DIMU_ACC_RANGE_2G))PlaySound(soundException);
	if(!DIMUconfigGyro(DIMU, DIMU_GYRO_RANGE_500))PlaySound(soundException);
  time1[T1]=0;
  while(true){
  	while(time1[T1]<5)wait1Msec(1);
  	time1[T1]=0;

  	xV=-1.68*DIMUreadGyroAxis(DIMU, DIMU_GYRO_X_AXIS);
  	yV=-1.68*DIMUreadGyroAxis(DIMU, DIMU_GYRO_Y_AXIS);
  	zV=-1.68*DIMUreadGyroAxis(DIMU, DIMU_GYRO_Z_AXIS);
  	/*
  	xVa=1.68*DIMUreadAccelAxis10Bit(DIMU, DIMU_ACC_X_AXIS);
		yVa=1.68*DIMUreadAccelAxis10Bit(DIMU, DIMU_ACC_Y_AXIS);
		zVa=1.68*DIMUreadAccelAxis10Bit(DIMU, DIMU_ACC_Z_AXIS);
		*/
  	if ( ( xV < 2 ) && ( xV > -2 ) )
  			{
  				xA += 0;
  				xC++;
  				if ( ( xA < 3 ) && ( xA > -3 ) && ( xC > 3 ) )
  						{
  							xA = 0;
  							xC = 0;
  						}
  			}
  			else
  			{
  				xA += ( xV / 2 ) * 0.009;
  			}


  	if ( ( yV < 2 ) && ( yV > -2 ) )
  		{
  			yA += 0;
  			yC++;
  			if ( ( yA < 3 ) && ( yA > -3 ) && ( yC > 3 ) )
  				{
  					yA = 0;
  					yC = 0;
  				}
  			}
  			else
  			{
  				yA += ( yV / 2 ) *0.009;
  			}

  	if ( ( zV < 2 ) && ( zV > -2 ) )
  		{
  			zA += 0;
  			zC++;
  			if ( ( zA < 3 ) && ( zA > -3 ) && ( zC > 3 ) )
  				{
  					zA = 0;
  					zC = 0;
  				}
  			}
  			else
  			{
  					zA += ( zV / 2 ) * 0.009;
  			}

  }
}
