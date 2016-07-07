package baron_arena.geom;

import java.awt.geom.Point2D.Double;

public class Vector2D extends Double {
	private static final long serialVersionUID = 1L;
	
	public Vector2D(double x, double y) {
		super(x, y);
	}
	
	public Vector2D(double angle) {
		super(Math.cos(angle), Math.sin(angle));
	}
	
	public Vector2D() {
		super();
	}
	
	public Vector2D(Vector2D a) {
		x = a.x;
		y = a.y;
	}
	
	public double angle() {
		return Math.atan2(y, x);
	}
	
	public double length() {
		return Math.sqrt(x * x + y * y);
	}
	
	public Vector2D normalized() {
		double length = length();
		return new Vector2D(x / length, y / length);
	}
}
