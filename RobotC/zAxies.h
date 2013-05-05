float x_val,y_val,z_val;
float xAttitude,yAttitude,zAttitude;
float lastX,lastY,lastZ;

task testAxies(){
	int xCounts=0;int yCounts=0;int zCounts=0;
  xAttitude=0;yAttitude=0;zAttitude=0;x_val=0;y_val=0;z_val=0;lastX=0;lastY=0;lastZ=0;
	if(!DIMUconfigAccel(DIMU, DIMU_ACC_RANGE_2G))PlaySound(soundException);
	if(!DIMUconfigGyro(DIMU, DIMU_GYRO_RANGE_500))PlaySound(soundException);
  time1[T1]=0;
  while(true){
  	while(time1[T1]<10)wait1Msec(1);
  	time1[T1]=0;
  	x_val=1.68*DIMUreadGyroAxis(DIMU, DIMU_GYRO_X_AXIS);
  	y_val=1.68*DIMUreadGyroAxis(DIMU, DIMU_GYRO_Y_AXIS);
  	z_val=1.68*DIMUreadGyroAxis(DIMU, DIMU_GYRO_Z_AXIS);
  	if((x_val<2)&&(x_val>-2)){xAttitude+=0;xCounts++;if((xAttitude<6)&&(xAttitude>-6)&&(xCounts>10)){xAttitude=0;xCounts=0;}}else{xAttitude+=(x_val/2)*0.02;}
  	if((y_val<2)&&(y_val>-2)){yAttitude+=0;yCounts++;if((yAttitude<6)&&(yAttitude>-6)&&(yCounts>10)){yAttitude=0;yCounts=0;}}else{yAttitude+=(y_val/2)*0.02;}
  	if((z_val<2)&&(z_val>-2)){zAttitude+=0;zCounts++;if((zAttitude<6)&&(zAttitude>-6)&&(zCounts>10)){zAttitude=0;zCounts=0;}}else{zAttitude+=(z_val/2)*0.02;}
  }
}
