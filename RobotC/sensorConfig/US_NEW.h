int us_NewResult;
task USNEW()
{
	while(true){
		int i=SensorValue[us_new];
		if(i<15){i=(i-3);}else if((i>=15)&&(i<21)){i=(i-4);}else if((i>=21)&&(i<30)){i=(i-1);}else if(i>=30){i=i;}
		us_NewResult=i;
		wait1Msec(100);
	}
}
