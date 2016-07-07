package baron_arena.entity;

import java.awt.Rectangle;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.awt.image.BufferedImage;

public class Player {
	public double x;
	public double y;
	public double newX;
	public double newY;
	public double width;
	public double height;
	public BufferedImage image;
	public double health = 20;
	
	public Player(double x, double y, double width, double height, BufferedImage image) {
		this.x = x;
		this.y = y;
		newX = x;
		newY = y;
		this.width = width;
		this.height = height;
		this.image = image;
	}
	
	public Player(double x, double y, BufferedImage image) {
		this(x, y, image.getWidth() / 16.0, image.getHeight() / 16.0, image);
	}
	
	public Player(BufferedImage image) {
		this(0, 0, image);
	}
	
	public Rectangle2D getBounds2D() {
		return new Rectangle.Double(x, y, width, height);
	}
	
	public Point2D.Double getInterpPoint(double interpolation) {
		return new Point2D.Double((newX - x) * interpolation + x, (newY - y) * interpolation + y);
	}
}
