package nl.totan.sample;

import nl.totan.sensors.L3G4200D_E;
import lejos.nxt.I2CPort;
import lejos.nxt.SensorPort;

public abstract class testL3G4200D_E {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		SensorPort.S4.i2cEnable(I2CPort.HIGH_SPEED);
		L3G4200D_E gyro = new L3G4200D_E(SensorPort.S4);
		gyro.runMenu();
	}

}
