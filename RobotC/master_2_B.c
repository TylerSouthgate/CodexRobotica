#pragma DebuggerWindows("debugStream")

void checkBTLinkConnected();

task main()
	{
		char inValue = 0;
		char inLastValue = 0;
		string PIN = 1234;
		int nIndex = 0;
		int touch01 = 0;
		int touch02 = 0;
		int sonar01 = 0;
		const int kHexDigitsPerLine = 3;
		ubyte BytesRead[kHexDigitsPerLine];
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
		while(true){
			nxtDisplayCenteredTextLine(1, "Reading");
			string str = "";
			//Create listener fot arduino feed

			//nxtReadRawBluetooth(&BytesRead[1], 2);

			nxtReadRawBluetooth(&BytesRead[1], 3);
			//nxtDisplayCenteredTextLine(2, "%d", BytesRead[1]);
			inValue = BytesRead[1];
			if (inValue == inLastValue){
				inLastValue = inLastValue;
				}else{
				writeDebugStream("%d", BytesRead[1]);
				writeDebugStream(",");
				inLastValue = inValue;
				//writeDebugStream("%d", BytesRead[1]);

				//Check Touch ONE

			if (inValue == 'A' )
				{
					touch01 = 1;
					nxtDisplayTextLine(2, "One is ON: %d", touch01);
				}	else if (inValue == 'B' )
					{
						touch01 = 0;
						nxtDisplayTextLine(2, "One is OFF: %d", touch01);
					}

			//Check Tough TWO
			else if (inValue == 'C' )
				{
					touch02 = 1;
					nxtDisplayTextLine(3, "Two is ON: %d", touch02);
				}
			else if (inValue == 'D' )
				{
					touch02 = 0;
					nxtDisplayTextLine(3, "Two is OFF: %d", touch02);
				}
			else if (inValue == 'E' )
				{
					sonar01 = 0;
					nxtDisplayTextLine(4, "Sonar1 OUT: %d", sonar01);
				}
			else if (inValue == 'F' ) // Theres something there!
				{
					sonar01 = 1;
					nxtDisplayTextLine(4, "Sonar1 IN: %d", sonar01);
				}
		}

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
