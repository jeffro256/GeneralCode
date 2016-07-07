package baron_arena.geom;

import java.awt.geom.Ellipse2D;

public class Circle extends Ellipse2D.Double {
	private static final long serialVersionUID = 1L;
	
	public double radius;
	
	public Circle(double x, double y, double radius) {
		super(x, y, radius * 2, radius * 2);
		
		this.radius = radius;
	}
	
	@Override
	public void setFrame(double x, double y, double w, double h) {
		if (w != h) {
			throw new IllegalArgumentException("width != height");
		}
		
		super.setFrame(x, y, w, h);
		this.radius = w / 2.0;
	}
	
	public void setFrame(double x, double y, double r) {
		setFrame(x, y, r * 2.0, r * 2.0);
	}
	
	public boolean intersects(Circle c) {
		double dx = c.x - x;
		double dy = c.y - y;
		double dist = Math.sqrt(dx * dx + dy * dy);
		
		return dist <= c.radius + radius;
	}
}
