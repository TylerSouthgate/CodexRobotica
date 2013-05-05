package nl.totan.sensors;

import lejos.nxt.I2CPort;
import lejos.util.EndianTools;

/**
 * This class works with the Mindsensors acceleration sensor
 * @author Aswin
 */
public class ACCL_Nx_v3 extends Accelerometer {
	
	public enum Range {

    /**
     * Range to 1.5 G
     */
    _1_5G((byte) 49),
    /**
     * Range to 2 G
     */
    _2G((byte) 50),
    /**
     * Range to 4 G
     */
    _4G((byte) 51),
    /**
     * Range to 6 G
     */
    _6G((byte) 52);
    private final byte code;

    Range(byte code) {
      this.code = code;
    }

    /**
     * Get to command code to set the sensitivity
     * @return byte code
     */
    public byte getCode() {
      return code;
    }
}


  private static byte ACCEL = 0x45;
  private static byte REGRANGE = 0x41;
  
  Range range=Range._4G;
  
  int[] raw=new int[3];
  byte[] buf=new byte[6];

  
  /**
   * 
   * @param port
   */
  public ACCL_Nx_v3(I2CPort port) {
    this(port, DEFAULT_I2C_ADDRESS);
  }

  /**
   * 
   * @param port
   * @param address
   */
  public ACCL_Nx_v3(I2CPort port, int address) {
    super(port, address);
    Settings.load();
  }

  
  /**
   * Sets the sensitivity unit
   * @param sensitivity
   */
  public void setRange(Range range) {
  	this.range=range;
    sendData(REGRANGE, range.getCode());
    try {
      Thread.sleep(150);
    } catch (InterruptedException ex) {
    }
  }

  /**
   * Returns the current sensitivity of the sensor
   * @return sensitivity
   */
  public Range getRange() {
    return range;
  }


  
 public void fetchRawAccel(int[] ret) {
   getData(ACCEL, buf, 6);
   for(int i=0;i<3;i++)
     ret[i]=EndianTools.decodeShortLE(buf, i*2);
  }

@Override
public void fetchAllAccel(float[] ret, AccelUnits unit) {
	fetchRawAccel(raw);
	for (int i=0;i<3;i++) 
		ret[i]=(raw[i]-Settings.offset[i])*multiplier*Settings.scale[i];
	AccelUnits.MILLIG.convertTo(ret, unit);
	
}

@Override
public String getProductID() {
  return "MindSensors";
}

@Override
public String getSensorType() {
  return "ACCL-Nx";
}

@Override
public String getVersion() {
  return "v3";
}
  
}

