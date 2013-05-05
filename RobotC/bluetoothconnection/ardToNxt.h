void checkBTLinkConnected();



task establish_BT_Connection()
	{
		int inValue = 0
		string PIN = 1234;
		int nIndex = 0;
		const int kHexDigitsPerLine = 2;
		ubyte BytesRead[kHexDigitsPerLine];

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

		eraseDisplay();
		while(true){
			nxtDisplayCenteredTextLine(1, "Reading");

			//Create listener fot arduino feed

			//nxtReadRawBluetooth(&BytesRead[1], 2);

			nxtReadRawBluetooth(&BytesRead[1], 3);
			nxtDisplayCenteredTextLine(2, "%d", BytesRead[1]);
			inValue = BytesRead[1];

			//nxtReadRawBluetooth(&BytesRead[1], 3);
			//nxtReadRawBluetooth(&BytesRead[2], 2);

			//int touch2 = BytesRead[2];

			//int touch2 = nxtReadRawBluetooth(&BytesRead[2], 4);
			//nxtDisplayCenteredTextLine(2, "%d", BytesRead[1]);

			//nxtDisplayTextLine(4, "%d", BytesRead[1]);
			//nxtDisplayTextLine(5, "%d", BytesRead[2]);

			//nxtReadRawBluetooth(&BytesRead[3], 4);
			//nxtDisplayTextLine(6, "%d", BytesRead[3]);

			//nxtReadRawBluetooth(&BytesRead[4], 4);
			//nxtDisplayTextLine(7, "%d", BytesRead[4]);
			//Garb the readings that we want and act upon them


			//Check Touch ONE
			if (inValue == 65 )
				{
					nxtDisplayTextLine(4, "One is ON: %d", inValue);
				}
			if (inValue == 66 )
				{
					nxtDisplayTextLine(4, "One is OFF: %d", inValue);
				}

			//Check Tough TWO
			if (inValue == 67 )
				{
					nxtDisplayTextLine(5, "Two is ON: %d", inValue);
				}
			if (inValue == 68 )
				{
					nxtDisplayTextLine(5, "Two is OFF: %d", inValue);
				}


			//Check I2C Sonar
			if (inValue == 69 )
				{
					nxtDisplayTextLine(6, "Sonar1 OUT: %d", inValue);
				}
			if (inValue == 70 ) // Theres something there!
				{
					nxtDisplayTextLine(6, "Sonar1 IN: %d", inValue);
				}





			//if (BytesRead[1] == 68){nxtDisplayCenteredTextLine(6, "%d", BytesRead[1]);}else{if (BytesRead[1] == 65){nxtDisplayCenteredTextLine(6, "%d", BytesRead[1]);}}
			//if (BytesRead[1] == 68){nxtDisplayCenteredTextLine(7, "OFF");}else{if(BytesRead[1] == 65){nxtDisplayCenteredTextLine(7, "ON");}}
			wait1Msec(1);

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
