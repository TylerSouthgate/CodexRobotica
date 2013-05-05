#pragma DebuggerWindows("debugStream")

void checkBTLinkConnected();

task main()
	{
		char inValue = 0;
		char inLastValue = 0;
		string PIN = 1234;
		char nIndex = 0;
		char oIndex = 0;
		int touch01 = 0;
		int touch02 = 0;
		int sonar01 = 0;
		const int kHexDigitsPerLine = 2;
		ubyte MarkerRead[kHexDigitsPerLine];
		ubyte SensorRead[kHexDigitsPerLine];
		int usDistance = 0;
		//Establish arduino connection
		btConnect(3, "SeeedBTSlave");
		wait1Msec(1000);
		setSessionPIN(PIN);
		nxtDisplayCenteredBigTextLine(2, "Testing!");
		wait1Msec(5000);

		//Check that the connection is live
		checkBTLinkConnected();


		//Push bluecore into RAW mode
		nxtDisplayCenteredTextLine(4, "Before RAW");
		setBluetoothRawDataMode();
		while (!bBTRawMode)
			{
				nxtDisplayCenteredTextLine(4, "Inside RAW");
				wait1Msec(1);
			}
		nxtDisplayCenteredTextLine(4, "After RAW");

		//Send some data to the connected arduino
		ubyte count[3];
	  ubyte count2[3];
	  count[0]=70;
	  count[1]=	65;
	  count[2]=	66;
	  count2[0]=65;
	  count2[1]=70;
	  count2[2]=71;
	  nxtWriteRawBluetooth(count, sizeof(count));
		wait1Msec(1000);
		nxtWriteRawBluetooth(count2, sizeof(count2));
		wait1Msec(1000);
		eraseDisplay();
		while(true)
			{
				nxtDisplayCenteredTextLine(1, "Reading");
				string str = "";
				//MarkerRead[1] = 10;
				nxtReadRawBluetooth(&MarkerRead[1], 2);
				inValue = MarkerRead[1];
				if (inValue == 63)
					{

						//SensorRead[1] = 10;
						nxtReadRawBluetooth(&SensorRead[1], 2);
						nIndex = SensorRead[1];
						if ( ( nIndex >= 65 ) && ( nIndex <= 70 ) )
							{
								writeDebugStream("Data string: %d",inValue);writeDebugStream("+");nxtDisplayTextLine(6, "Value Check: %d", inValue);
								if 			(nIndex == 65 ){touch01 = 1;nxtDisplayTextLine(2, "One is ON: %d", touch01);writeDebugStream("%d",nIndex);writeDebugStream(", ");}
								else if (nIndex == 66 ){touch01 = 0;nxtDisplayTextLine(2, "One is OFF: %d", touch01);writeDebugStream("%d",nIndex);writeDebugStream(", ");}
								else if (nIndex == 67 ){touch02 = 1;nxtDisplayTextLine(3, "Two is ON: %d", touch02);writeDebugStream("%d",nIndex);writeDebugStream(", ");}
								else if (nIndex == 68 ){touch02 = 0;nxtDisplayTextLine(3, "Two is OFF: %d", touch02);writeDebugStream("%d",nIndex);writeDebugStream(", ");}
								else if (nIndex == 69 ){sonar01 = 0;nxtDisplayTextLine(4, "Sonar1 OUT: %d", sonar01);writeDebugStream("%d",nIndex);writeDebugStream(", ");}
								else if (nIndex == 70 ){sonar01 = 1;nxtDisplayTextLine(4, "Sonar1 IN: %d", sonar01);writeDebugStream("%d",nIndex);writeDebugStream(", ");}
								//else {writeDebugStream("%d",nIndex);writeDebugStream(" BAD DATA, ");}
								nIndex = oIndex;
							}
					}

			}
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
