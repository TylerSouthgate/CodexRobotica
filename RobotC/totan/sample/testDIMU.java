package nl.totan.sample;

import lejos.nxt.I2CPort;
import lejos.nxt.LCD;
import lejos.nxt.SensorPort;
import lejos.util.TextMenu;
import nl.totan.sensors.DIMUAccel;
import nl.totan.sensors.DIMUGyro;

public class testDIMU {

	/**
	 * Demo for Dexter Industries IMU
	 * @param args
	 */
	public static void main(String[] args) {
		SensorPort.S4.i2cEnable(I2CPort.HIGH_SPEED);
		DIMUAccel accel = new DIMUAccel(SensorPort.S4);
		DIMUGyro gyro = new DIMUGyro(SensorPort.S4);

		int index = 0;
		String[] menuItems = { "Gyro", "Accelerometer" };
		TextMenu menu = new TextMenu(menuItems, 1, "dIMU");
		boolean finished = false;
		while (!finished) {
			LCD.clear();
			LCD.drawString("Escape to end", 0, 7);
			index = menu.select();
			switch (index) {
				case -1:
					finished = true;
					break;
				case 0:
					gyro.runMenu();
					break;
				case 1:
					accel.runMenu();
					break;
				default:
					break;
			}
		}
	}
}
