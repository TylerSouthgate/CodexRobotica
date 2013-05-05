int us_OldResult;
task USOLD()
{
	while(true){
		int i=SensorValue[us_old];
		if(i<22){i=(i-5);}else if((i>=22)&&(i<=51)){i=(i-1);}else if(i>=52){i=(i-2);}
		us_OldResult=i;
		wait1Msec(100);
	}
}
