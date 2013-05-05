package nl.totan.sample;

import java.io.IOException;

import nl.totan.sensors.*;
import nl.totan.sensors.ADXL345.SampleRate;
import nl.totan.sensors.TiltData.TiltUnits;
import nl.totan.filters.*;
import lejos.nxt.*;

public class testIMU {

	/**
	 * @param args
	 * @throws InterruptedException 
	 * @throws IOException 
	 */
	public static void main(String[] args) {
		LCD.drawString("IMU demo", 0, 0);
		LCD.drawString("Calibrating...", 0, 2);
		LCD.drawString("Demo by Aswin.", 0, 7);
		
		
		
		// setup the NLCFilter
		boolean[] autoOffset={false,false,false};
		
		int displayMode=0;

		SensorPort.S3.i2cEnable(I2CPort.HIGH_SPEED);
//		ADXL345 accel = new ADXL345(SensorPort.S3, 0xa6);
//		accel.setSampleRate(SampleRate._200Hz);
//		accel.setRange(ADXL345.Range._2G);
//		ITG3200 gyro = new ITG3200(SensorPort.S3, 0xd0);
//		CompassRose compass=new CompassRose(50,32);
//		gyro.calculateOffset();
		
		SensorPort.S4.i2cEnable(I2CPort.HIGH_SPEED);
		MMA7455L accel = new MMA7455L(SensorPort.S4);
		L3G4200D gyro = new L3G4200D(SensorPort.S4);
		dIMU compass=new dIMU(50,32);

		
		
		gyro.setDynamicOffset(autoOffset);
	
	
		NLCFilter attitude = new NLCFilter(gyro, accel);
		attitude.setMaxFrequency(0);
		attitude.setTiltUnit(TiltUnits.DEGREES);
		
		attitude.start();
		
		while (!Button.ESCAPE.isDown()) {
			if (Button.LEFT.isDown()) displayMode--;
			if (Button.RIGHT.isDown()) displayMode++;
			if (Button.ENTER.isDown()) attitude.start();
			LCD.clearDisplay();
			switch (displayMode % 4) {
				case 0:
					compass.draw(attitude.getAttitudeMatrix());
					break;
				case 1:
					attitude.displayAttitude();
					break;
				case 2:
					attitude.displayAngles();
					break;
				case 3:
					LCD.drawString("Freq : "+Float.toString(attitude.getFrequency()), 0, 6);
					break;
				default:
					break;
			}
			try {
				Thread.sleep(200);
			}
			catch (InterruptedException e) {
				e.printStackTrace();
			}
				
		}
    attitude.stop();
		}
	}
