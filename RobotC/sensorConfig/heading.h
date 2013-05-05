
task findNorth(){
    while ( round(DIMCreadHeading(DIMC)) != 0 ){
	    if ( round(DIMCreadHeading(DIMC)) > 180 ){
	    		nxtDisplayCenteredBigTextLine(2, "%3.2f", DIMCreadHeading(DIMC) );
					if ( round(DIMCreadHeading(DIMC)) < 330 ){
	    			motor[mLeft] = 50;
		  			motor[mRight] = -50;
		  		} else {
		  			motor[mLeft] = 0;
			  		motor[mRight] = 0;
		    		wait1Msec(200);
		    		while ( round(DIMCreadHeading(DIMC)) != 0 ){
			  			nxtDisplayCenteredBigTextLine(2, "%3.2f", DIMCreadHeading(DIMC) );
							motor[mLeft] = 12;
			  			motor[mRight] = -12;
			  			wait1Msec(100);
			  			motor[mLeft] = 0;
				  		motor[mRight] = 0;
			    		wait1Msec(200);
			    	}
		    	}
		  	}
		  else if ( round(DIMCreadHeading(DIMC)) < 180 ){
	    		nxtDisplayCenteredBigTextLine(2, "%3.2f", DIMCreadHeading(DIMC) );
					if ( round(DIMCreadHeading(DIMC)) > 30 ){
	    		motor[mLeft] = -50;
		  		motor[mRight] = 50;
		  		} else {
		  			motor[mLeft] = 0;
			  		motor[mRight] = 0;
		    		wait1Msec(200);
		    		while ( round(DIMCreadHeading(DIMC)) != 0 ){
			  			nxtDisplayCenteredBigTextLine(2, "%3.2f", DIMCreadHeading(DIMC) );
							motor[mLeft] = -12;
			  			motor[mRight] = 12;
			  			wait1Msec(100);
			  			motor[mLeft] = 0;
				  		motor[mRight] = 0;
			    		wait1Msec(200);
			    	}
		    	}
	    	}
	}
}
