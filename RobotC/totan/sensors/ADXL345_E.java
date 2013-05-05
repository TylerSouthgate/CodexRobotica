package nl.totan.sensors;

import lejos.nxt.Button;
import lejos.nxt.I2CPort;
import lejos.nxt.LCD;
import lejos.util.TextMenu;

public class ADXL345_E extends ADXL345 implements SensorUserInterface{
  public ADXL345_E(I2CPort port) {
		super(port);
}

	/**
   * Runs the top level interface of the sensor
   */
  public void runMenu() {
    int index = 0;
    String[] menuItems = {"View", "Settings", "Calibrate", "About"};
    TextMenu menu = new TextMenu(menuItems, 1, getSensorType());
    while (true) {
      LCD.clear();
      LCD.drawString("Escape to return", 0, 7);
      index = menu.select();
      switch (index) {
        case -1:
          return;
        case 0:
          displaySensorValue();
          break; 
        case 1:
          runSettingsMenu();
          break;
        case 2:
          runCalibrationMenu();
          break;
        case 3:
          displayAbout();
        default:
          break;
      }
    }
  }

  /**
   * Runs the settings interface to the sensor
   */
  public void runSettingsMenu() {
    int index = 0;
    String[] menuItems = {"Sens  :" + getRange(), "Accel :" + getAccelUnit(), "Tilt  :" + getTiltUnit()};
    TextMenu menu = new TextMenu(menuItems, 1, "Settings menu");
    while (true) {
      LCD.clear();
      LCD.drawString("Escape to return", 0, 7);
      index = menu.select();
      switch (index) {
        case -1:
          return;
        case 0:
          selectRange();
          menuItems[0] = "Sens  :" + getRange();
          break;
        case 1:
          selectAccelUnit();
          menuItems[1] = "Accel :" + getAccelUnit();
          break;
        case 2:
          selectTiltUnit();
          menuItems[2] = "Tilt  :" + getTiltUnit();
          break;
        default:
          break;
      }
      menu.setItems(menuItems);
    }
  }

  /**
   * Runs the sensitivity interface to the sensor
   */
  public void selectRange() {
    int index = 0;
    String[] menuItems;
    menuItems = new String[4];
    int i = 0;
    for (Range p : Range.values()) {
      menuItems[i++] = p.name();
    }

    TextMenu menu = new TextMenu(menuItems, 1, "Select Sensitivity");
    LCD.clear();
    LCD.drawString("Escape to return", 0, 7);
    Range s;
    s = getRange();
    index = menu.select(s.ordinal());

    if (index != -1) {
      Range[] p;
      p = Range.values();
      setRange(p[index]);
    }

  }

  /**
   * Runs the acceleration units interface to the sensor
   */
  public void selectAccelUnit() {
    int index = 0;
    String[] menuItems;
    menuItems = new String[4];
    int i = 0;
    for (AccelUnits p : AccelUnits.values()) {
      menuItems[i++] = p.name();
    }

    TextMenu menu = new TextMenu(menuItems, 1, "Select accel unit");
    LCD.clear();
    LCD.drawString("Escape to return", 0, 7);
    AccelUnits s;
    s = getAccelUnit();
    index = menu.select(s.ordinal());

    if (index != -1) {
      AccelUnits[] p;
      p = AccelUnits.values();
      setAccelUnit(p[index]);
    }
  }

  /**
   * Runs the tilt units interface to the sensor
   */
  public void selectTiltUnit() {
    int index = 0;
    String[] menuItems;
    menuItems = new String[3];
    int i = 0;
    for (TiltUnits p : TiltUnits.values()) {
      menuItems[i++] = p.name();
    }

    TextMenu menu = new TextMenu(menuItems, 1, "Select tilt unit");
    LCD.clear();
    LCD.drawString("Escape to return", 0, 7);
    TiltUnits s;
    s = getTiltUnit();
    index = menu.select(s.ordinal());

    if (index != -1) {
      TiltUnits[] p;
      p = TiltUnits.values();
      setTiltUnit(p[index]);
    }
  }

  /**
   * Runs the about interface to the sensor
   */
  public void displayAbout() {
    LCD.clear();
    LCD.drawString(this.getProductID(), 1, 1);
    LCD.drawString(this.getSensorType(), 1, 2);
    LCD.drawString(this.getVersion(), 1, 3);
    LCD.drawString("Escape to return", 0, 7);
    Button.ESCAPE.waitForPressAndRelease();
  }

  /**
   * Displays output from the sensor, acceleration and tilt, in the selected units
   */
  public void displaySensorValue() {
    float[] accel = new float[3];
    float[] tilt = new float[3];
    while (!Button.ESCAPE.isDown()) {
      fetchAllAccel(accel);
      fetchAllTilt(tilt);
      LCD.clear();
      LCD.drawString("Accel   Tilt", 4, 0);
      LCD.drawString("" + getAccelUnit(), 4, 1);
      LCD.drawString("" + getTiltUnit(), 12, 1);
      LCD.drawString("X", 1, 2);
      LCD.drawString("Y", 1, 3);
      LCD.drawString("Z", 1, 4);
      LCD.drawString("Escape to return", 0, 7);
      for (int i = 0; i < 3; i++) {
        LCD.drawString(String.valueOf((accel[i])), 4, i + 2);
        LCD.drawString(" ", 11, i + 2);
        LCD.drawString(String.valueOf((tilt[i])), 12, i + 2);
      }
      try {
        Thread.sleep(50);
      } catch (InterruptedException ex) {
      }

    }
    while (Button.ESCAPE.isDown());

  }

  /**
   * Runs the calibration interface of the sensor
   */
  public void runCalibrationMenu() {
  	Settings.runCalibrationMenu();
  }


}
