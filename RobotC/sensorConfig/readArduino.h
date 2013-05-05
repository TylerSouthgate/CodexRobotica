char inValue = 0;
char nIndex = 0;
char nReading = 0;
char nCheck = 0;

char lr01 = 0;
char lr02 = 0;
char lr03 = 0;
char lr04 = 0;

int touch01 = 0;
int touch02 = 0;
int sonar01 = 255;
const int kHexDigitsPerLine = 2;
ubyte MarkerRead[kHexDigitsPerLine];
ubyte SensorIndex[kHexDigitsPerLine];
ubyte SensorRead[kHexDigitsPerLine];
ubyte SensorReadCheck[kHexDigitsPerLine];

task readArduino(){
  while(true){
		nxtReadRawBluetooth(&MarkerRead[1], 1);
		inValue = MarkerRead[1];
		if (inValue==63)
			{
				nxtReadRawBluetooth(&SensorIndex[1], 1);
				nIndex = SensorIndex[1];
				if ((nIndex>=65)&&(nIndex<=69))
					{
						nxtReadRawBluetooth(&SensorRead[1], 1);
						nReading = SensorRead[1];
						nxtReadRawBluetooth(&SensorReadCheck[1], 1);
						nCheck = SensorReadCheck[1];

						if ((nIndex==65)&&(nReading==nCheck))
							{
								if (nReading==66){touch01=1;}else{touch01=0;}
							}else{touch01=0;}
						if ((nIndex==67)&&(nReading==nCheck))
							{
								if (nReading==68){touch02=1;}else{touch02=0;}
							}else{touch02=0;}

						if ((nIndex==69)&&(nReading==nCheck))
							{
									if ((nReading<=98)&&(nReading>=11))
										{
											sonar01=(nReading-10);
										}else{
											sonar01=255;
										}
							lr04 = lr03;
							lr03 = lr02;
							lr02 = lr01;
							lr01 = ( nReading - 10 );
							}
				}
			}
		}
	}
