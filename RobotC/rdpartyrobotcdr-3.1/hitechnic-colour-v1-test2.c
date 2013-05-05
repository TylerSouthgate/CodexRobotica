#pragma config(Sensor, S1,     HTCS,                sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: hitechnic-colour-v1-test2.c 123 2012-11-02 16:35:15Z xander $
 */

/**
 * hitechnic-colour-v1.h provides an API for the HiTechnic Color Sensor.  This program
 * demonstrates how to use that API.  This program allows you to calibrate the white
 * value for the Color Sensor.  Point the sensor at something you want the sensor to
 * detect as white and press the [enter] button.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: More comments
 * - 0.3: Removed common.h from includes
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.54 AND HIGHER.
 * Xander Soldaat (xander_at_botbench.com)
 * 20 February 2011
 * version 0.3
 */

#include "drivers/hitechnic-colour-v1.h"

task main () {
  // Get control over the buttons
  nNxtButtonTask  = -2;

  eraseDisplay();
  nxtDisplayTextLine(0, "HTCS Test 2");
  nxtDisplayTextLine(2, "Press orange");
  nxtDisplayTextLine(3, "button to start");
  nxtDisplayTextLine(4, "calibration.");
  nxtDisplayTextLine(5, "Press grey");
  nxtDisplayTextLine(6, "button to exit.");

  while(nNxtButtonPressed != kEnterButton) EndTimeSlice();
  eraseDisplay();
  nxtDisplayTextLine(3, "Starting");
  nxtDisplayTextLine(4, "calibration.");

  // This call calibrates the white value.
  if (!HTCScalWhite(HTCS)) {
    eraseDisplay();
    PlaySound(soundException);
    nxtDisplayTextLine(3, "ERROR!!");
    nxtDisplayTextLine(5, "Calibration");
    nxtDisplayTextLine(6, "failed!!");
    wait1Msec(2000);
    StopAllTasks();
  }
  wait1Msec(1000);
}

/*
 * $Id: hitechnic-colour-v1-test2.c 123 2012-11-02 16:35:15Z xander $
 */
