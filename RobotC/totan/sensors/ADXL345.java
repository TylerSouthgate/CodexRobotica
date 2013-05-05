package nl.totan.sensors;

import lejos.nxt.I2CPort;
import lejos.util.EndianTools;

/**
 *
 * @author Aswin
 */
public class ADXL345 extends Accelerometer {

  private static byte ACCEL = 0x32;
  private static byte RATE = 0x2c;
  private static byte REG_RANGE=0x31;
  private static int DEFAULT_I2C_ADDRESS = 0xa6;
  
  protected SampleRate sampleRate=SampleRate._800Hz;
  protected Range range=Range._4G; 
  
  int[] raw=new int[3];
  byte[] buf=new byte[6];

  public enum Range {

    _2G((byte) 0x00,256),
    _4G((byte) 0x01,256),
    _8G((byte) 0x02, 256),
    _16G((byte) 0x03, 256);

    private final byte code;
    private final int devider;

    Range(byte code, int devider) {
      this.code = code;
      this.devider=devider;
    }

    /**
     * Get to command code to set the sensitivity
     * @return byte code
     */
    public byte getCode() {
      return code;
    }
    public int getDevider() {
      return devider;
    }
}
 

  public enum SampleRate {

    _1600Hz((byte) 15),
    _800Hz((byte) 14),
    _400Hz((byte) 13),
    _200Hz((byte) 12),
    _100Hz((byte) 11),
    _50hz((byte) 10),
    _25hz((byte) 9),
    _12_5hz((byte) 8),
    _6_25Hz((byte) 7),
    _3_125HZ((byte) 6);
    private final byte code;

    SampleRate(byte code) {
      this.code = code;
    }

    /**
     * Get to command code to set the sensitivity
     * @return byte code
     */
    public byte code() {
      return code;
    }
  }
  
  public ADXL345(I2CPort port) {
	  this(port,DEFAULT_I2C_ADDRESS);
  }

  public ADXL345(I2CPort port, int address) {
    super(port, address);
    setSampleRate(sampleRate);
    // set range and dataformat
    setRange(range);
    // set measurement mode
    sendData(0x2d, (byte) 0x08);
    Settings.load();
  }


  public final void setSampleRate(ADXL345.SampleRate rate) {
  	this.sampleRate=rate;
    sendData(RATE, rate.code());
  }

  public final ADXL345.SampleRate getSampleRate() {
    return sampleRate;
  } 
  
  public void setRange(Range range) {
  	this.range=range;
  	multiplier=1f/range.getDevider();
  	sendData(REG_RANGE, (byte) ((byte) 0x08 | range.getCode()));
  }
 
  public Range getRange(){
  	return range;
  }
  
  public void fetchRawAccel(int[] ret) {
   getData(ACCEL, buf, 6);
   for(int i=0;i<3;i++)
     ret[i]=EndianTools.decodeShortLE(buf, i*2);
  }


  /**
   * Acceleration along 3 axis.
   * @param unit of acceleration
   * @return Acceleration in provided unit
   */
  public void fetchAllAccel(float[] ret,AccelUnits unit) {
    fetchRawAccel(raw);
    for (int i = 0; i < 3; i++) {
      ret[i] = (raw[i] - Settings.offset[i]) * multiplier * Settings.scale[i];
    }
    AccelUnits.G.convertTo(ret, unit);
  }

  
  
  @Override
  public String getProductID() {
    return "Analog Devices";
  }

  @Override
  public String getSensorType() {
    return "ADXL345";
  }

  @Override
  public String getVersion() {
    return "1.0";
  }


	
  
  
}
