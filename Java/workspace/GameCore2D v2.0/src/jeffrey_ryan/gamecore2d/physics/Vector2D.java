package jeffrey_ryan.gamecore2d.physics;

import java.awt.geom.Point2D;

public class Vector2D {
	public double x;
	public double y;
	
	public Vector2D(double x, double y) {
		this.x = x;
		this.y = y;
	}
	
	public Vector2D() {
		this(0, 0);
	}
	
	public Vector2D(Vector2D a) {
		this(a.x, a.y);
	}
	
	public void add(Vector2D a) {
		x += a.x;
		y += a.y;
	}
	
	public Vector2D plus(Vector2D a) {
		return new Vector2D(x + a.x, y + a.y);
	}
	
	public void subtract(Vector2D a) {
		x -= a.x;
		y -= a.y;
	}
	
	public Vector2D minus(Vector2D a) {
		return new Vector2D(x - a.x, y - a.y);
	}
	
	public void multiply(Vector2D a) {
		x *= a.x;
		y *= a.y;
	}
	
	public void multiply(double a) {
		x *= a;
		y *= a;
	}
	
	public Vector2D times(Vector2D a) {
		return new Vector2D(x * a.x, y * a.y);
	}
	
	public Vector2D times(double a) {
		return new Vector2D(x * a, y * a);
	}
	
	public void divide(Vector2D a) {
		x /= a.x;
		y /= a.y;
	}
	
	public void divide(double a) {
		x /= a;
		y /= a;
	}
	
	public Vector2D over(Vector2D a) {
		return new Vector2D(x / a.x, y / a.y);
	}
	
	public Vector2D over(double a) {
		return new Vector2D(x / a, y / a);
	}
	
	public double length() {
		return Math.sqrt(x * x + y * y);
	}
	
	public void normalize() {
		double l = length();
		
		x /= l;
		y /= l;
	}
	
	public Vector2D normalized() {
		double l = length();

		return new Vector2D(x / l, y / l);
	}
	
	public double dot(Vector2D a) {
		return x * a.x + y * a.y;
	}
	
	public Point2D toPoint() {
		return new Point2D.Double(x, y);
	}
	
	@Override
	public String toString() {
		return "jeffrey_ryan.gamecore2d.physics.Vector2D[x=" + x + ",y=" + y + "]";
	}
}
