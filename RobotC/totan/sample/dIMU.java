package nl.totan.sample;

import javax.microedition.lcdui.Graphics;

import lejos.util.Matrix;

public class dIMU {

	private static int length=42;
	private static int width=24;
	private static int height=2;
	private static int margin=5;
	private static int plugHeight=14;
	private static int plugLength=15;
	private static int overhang=4;
	private static int xCenter=50;
	private static int yCenter=32;
	private static float scale=1.2f;


	
 	private static double[] lines={
 			// bottom off PCB
 			0,0,0,
 			0,width,0,
 			0,width,0,
 			length,width,0,
 			length,width,0,
 			length,0,0,
 			length,0,0,
 			0,0,0,
 			// top off PCB
 			0,0,height,
 			0,width,height,
 			0,width,height,
 			length,width,height,
 			length,width,height,
 			length,0,height,
 			length,0,height,
 			0,0,height,
 			// sides of PCB
 			0,0,0,
 			0,0,height,
 			0,width,0,
 			0,width,height,
 			length,width,0,
 			length,width,height,
 			length,0,0,
 			length,0,height,
 			//back of plug
 			-overhang,margin,height,
 			-overhang,width-margin,height,
 			-overhang,width-margin,height,
 			-overhang,width-margin,height+plugHeight,
 			-overhang,width-margin,height+plugHeight,
 			-overhang,margin,height+plugHeight,
 			-overhang,margin,height+plugHeight,
 			-overhang,margin,height,
 			// front off plug
 			plugLength-overhang,margin,height,
 			plugLength-overhang,width-margin,height,
 			plugLength-overhang,width-margin,height,
 			plugLength-overhang,width-margin,height+plugHeight,
 			plugLength-overhang,width-margin,height+plugHeight,
 			plugLength-overhang,margin,height+plugHeight,
 			plugLength-overhang,margin,height+plugHeight,
 			plugLength-overhang,margin,height,
 			// other sides off plug
 			-overhang,margin,height,
 			plugLength-overhang,margin,height,
 			-overhang,width-margin,height,
 			plugLength-overhang,width-margin,height,
 			-overhang,width-margin,height+plugHeight,
 			plugLength-overhang,width-margin,height+plugHeight,
 			-overhang,margin,height+plugHeight,
 			plugLength-overhang,margin,height+plugHeight,
 			
 			// gyro
 			24,3,height,
 			24,7,height,
 			24,7,height,
 			28,7,height,
 			28,7,height,
 			28,3,height,
 			28,3,height,
 			24,3,height,
 			// accel
 			36,4,height,
 			36,7,height,
 			36,7,height,
 			41,7,height,
			41,7,height,
			41,4,height,
 			41,4,height,
 			36,4,height,
 			
 	};
 	
 	static {
 		for (int i=0;i<lines.length;i=i+3) {
 			lines[i]=(lines[i]-length/2)*scale;
 			lines[i+1]=(lines[i+1]-width/2)*scale;
 		}
 	}
							
 	private Matrix rose=new Matrix(lines,3); 
 	private int elements=rose.getColumnDimension()/2;
 	
 	public dIMU(){
 	};
 	
 	public dIMU(int xCenter, int yCenter) {
 		this.xCenter=xCenter;
 		this.yCenter=yCenter;
 	}
 	

 	// converts world coordinate to NXT screen coordinate (y=-x, x=-y)
  private Matrix toScreen(Matrix m) {
  	Matrix ret=new Matrix(m.getRowDimension(),m.getColumnDimension());
  	for (int i=0;i<m.getColumnDimension();i++) {
  		ret.set(0, i, xCenter-m.get(1,i));
  		ret.set(1, i, yCenter- m.get(0,i));
  	}
  	return ret;
  }
	
	
public void draw() {
	Matrix ss=toScreen(rose);
	Graphics g=new Graphics();
	for (int i=0;i<elements;i++) {
		g.drawLine((int)ss.get(0,i*2),(int)ss.get(1,i*2),(int)ss.get(0,i*2+1),(int)ss.get(1,i*2+1));
	}
}

public void draw(Matrix R) {
	Matrix ss;
	Graphics g=new Graphics();
	ss=toScreen(R.times(rose));
	for (int i=0;i<elements;i++) {
		g.drawLine((int)ss.get(0,i*2),(int)ss.get(1,i*2),(int)ss.get(0,i*2+1),(int)ss.get(1,i*2+1));
	}
}




}
