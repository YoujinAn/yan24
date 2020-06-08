/*
 * JAC444 Workshop 2
 * File: Triangle.java
 * Name: Youjin An (140413188)
 * Date: June 8, 2020
 */

package shapes;

public class Triangle implements Shape {
	private double side1;
	private double side2;
	private double side3;
	
	public Triangle(double side1, double side2, double side3) throws TriangleException {
		if (isSideValid(side1, side2, side3)) {
			this.side1 = side1;
			this.side2 = side2;
			this.side3 = side3;
		}
		else {
			throw new TriangleException("Invalid side(s)!");
		}
	}
	
	public double getSide1() {
		return side1;
	}

	public void setSide1(double side1) throws TriangleException {
		if(isSideValid(side1, this.side2, this.side3)) {
			this.side1 = side1;
		}
		else {
			throw new TriangleException("Invalid side!");
		}
	}

	public double getSide2() {
		return side2;
	}

	public void setSide2(double side2) throws TriangleException {
		if(isSideValid(this.side1, side2, this.side3)) {
			this.side2 = side2;
		}
		else {
			throw new TriangleException("Invalid side!");
		}
	}

	public double getSide3() {
		return side3;
	}

	public void setSide3(double side3) throws TriangleException {
		if(isSideValid(this.side1, this.side2, side3)) {
			this.side3 = side3;
		}
		else {
			throw new TriangleException("Invalid side!");
		}
	}
	
	public boolean isSideValid(double side1, double side2, double side3) {
		
		if(side1 <= 0 || side2 <= 0 || side3 <= 0) {
			return false;
		}
			
		if (side1 >= side2 && side1 >= side3) {	
			return side1 < side2 + side3;
		}
		
		if (side2 >= side1 && side2 >= side3) {
			return side2 < side1 + side3;
		}
		
		return side3 < side1 + side2;
	}

	@Override
	public double getPerimeter() {
		return getSide1() + getSide2() + getSide3();
	}
	
	@Override
	public String toString() {
		return String.format("Triangle {s1=%.1f, s2=%.1f, s3=%.1f} perimeter = %.4f", getSide1(), getSide2(), getSide3(), getPerimeter());
	}
}
