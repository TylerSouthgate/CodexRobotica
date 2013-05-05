char inValue = 0;
char nIndex = 0;
char oIndex = 0;
int touch01 = 0;
int touch02 = 0;
int sonar01 = 0;
const int kHexDigitsPerLine = 2;
ubyte MarkerRead[kHexDigitsPerLine];
ubyte SensorRead[kHexDigitsPerLine];

void checkBTLinkConnected();
void makeConnection();
void SetRawSate();

task main()
	{
		makeConnection();
		checkBTLinkConnected();
		SetRawSate();
		while(true)
			{
				nxtDisplayCenteredTextLine(1, "Reading");


				nxtReadRawBluetooth(&MarkerRead[1], 2);
				inValue = MarkerRead[1];
				if (inValue == 63)
					{
						nxtReadRawBluetooth(&SensorRead[1], 2);
						nIndex = SensorRead[1];
						if ( ( nIndex >= 65 ) && ( nIndex <= 70 ) )
							{
								if 			(nIndex == 65 ){touch01 = 1;nxtDisplayTextLine(2, "One is ON: %d", touch01);}
								else if (nIndex == 66 ){touch01 = 0;nxtDisplayTextLine(2, "One is OFF: %d", touch01);}
								else if (nIndex == 67 ){touch02 = 1;nxtDisplayTextLine(3, "Two is ON: %d", touch02);}
								else if (nIndex == 68 ){touch02 = 0;nxtDisplayTextLine(3, "Two is OFF: %d", touch02);}
								else if (nIndex == 69 ){sonar01 = 0;nxtDisplayTextLine(4, "Sonar1 OUT: %d", sonar01);}
								else if (nIndex == 70 ){sonar01 = 1;nxtDisplayTextLine(4, "Sonar1 IN: %d", sonar01);}
								nIndex = oIndex;
							}
					}
			}
	}

void SetRawSate()
	{
		nxtDisplayCenteredTextLine(4, "Before RAW");
		setBluetoothRawDataMode();
		while (!bBTRawMode)
			{
				nxtDisplayCenteredTextLine(4, "Inside RAW");
				wait1Msec(1);
			}
		nxtDisplayCenteredTextLine(4, "After RAW");
		eraseDisplay();
	}
void makeConnection()
	{
		string PIN = 1234;
		btConnect(3, "SeeedBTSlave");
		wait1Msec(1000);
		setSessionPIN(PIN);
		nxtDisplayCenteredBigTextLine(2, "Testing!");
		wait1Msec(5000);
		eraseDisplay();
	}
void checkBTLinkConnected()
	{
		if (nBTCurrentStreamIndex >= 0)
			return;
		PlaySound(soundLowBuzz);
		PlaySound(soundLowBuzz);
		eraseDisplay();
		nxtDisplayCenteredTextLine(3, "BT not");
		nxtDisplayCenteredTextLine(4, "Connected");
		wait1Msec(3000);
		StopAllTasks();
	}
