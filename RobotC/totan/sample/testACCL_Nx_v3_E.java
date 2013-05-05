package nl.totan.sample;

import nl.totan.sensors.ACCL_Nx_v3_E;
import lejos.nxt.I2CPort;
import lejos.nxt.SensorPort;

public class testACCL_Nx_v3_E {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		SensorPort.S3.i2cEnable(I2CPort.HIGH_SPEED);
		ACCL_Nx_v3_E accel = new ACCL_Nx_v3_E(SensorPort.S2);
		accel.runMenu();
	}

}
