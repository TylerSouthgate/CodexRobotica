package nl.totan.sample;

import javax.microedition.lcdui.Graphics;

import lejos.nxt.LCD;
import lejos.util.Matrix;

public class CompassRose {
	private   int radius=32;
	private   int width=6;
	private   int height=15;
	private   int offset=8;
	private int xCenter=50;
	private int yCenter=32;


	
 	private   double[] lines={0,0,height,radius,0,0,
								radius,0,0,width,width,0,
								width,width,0,0,0,height,
								
								0,0,height,0,radius,0,
								0,radius,0,-width,width,0,
								-width,width,0,0,0,height,
								
								0,0,height,-radius,0,0,
								-radius,0,0,-width,-width,0,
								-width,-width,0,0,0,height,

								0,0,height,0,-radius,0,
								0,-radius,0,width,-width,0,
								width,-width,0,0,0,height,
								
								radius,0,0,width,-width,0,
								
								0,radius,0,width,width,0,
								
								-radius,0,0,-width,width,0,
								
								0,-radius,0,-width,-width,0,
								
								 radius-7,offset,0, radius,offset,0,
								 radius-7,-5+offset,0,radius,-5+offset,0,
								 radius,offset,0,radius-7,-5+offset,0,
							};
 	
 	private Matrix rose=new Matrix(lines,3); 
 	private int elements=rose.getColumnDimension()/2;
 	
 	public CompassRose(){
 	};
 	
 	public CompassRose(int xCenter, int yCenter) {
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
