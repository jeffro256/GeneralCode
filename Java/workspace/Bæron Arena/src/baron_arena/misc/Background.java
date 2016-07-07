package baron_arena.misc;

import java.awt.Dimension;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;

public class Background {
	private BufferedImage image;
	private Dimension canvasSize;
	private double x;
	private double y;
	private double newX;
	private double newY;
	
	public double xVel = 0;
	public double yVel = 0;
	
	public Background(String path, Dimension canvasSize) throws IOException {
		image = ImageIO.read(getClass().getResourceAsStream(path));
		this.canvasSize = canvasSize;
		setX(0);
		setY(0);
	}
	
	public Background(String path) throws IOException {
		this(path, null);
	}
	
	public void update(double seconds) {
		x = newX;
		y = newY;
		
		if (x <= -image.getWidth()) {
			x += image.getWidth();
			newX += image.getWidth();
		}
		else if (x > 0) {
			x -= image.getWidth();
			newX -= image.getWidth();
		}
		
		if (y <= -image.getHeight()) {
			y += image.getHeight();
			newY += image.getHeight();
		}
		else if (y > 0) {
			y -= image.getHeight();
			newY -= image.getHeight();
		}
		
		newX += xVel * seconds;
		newY += yVel * seconds;
	}
	
	public void render(Graphics2D g, double interpolation) {
		if (canvasSize != null) {
			int imagesAcross = canvasSize.width / image.getWidth() + 1;
			int imagesDown = canvasSize.height / image.getHeight() + 1;
			int screenX = (int) ((newX - x) * interpolation + x);
			int screenY = (int) ((newY - y) * interpolation + y);
			
			for (int i = 0; i < imagesAcross; i++) {
				for (int j = 0; j < imagesDown; j++) {
					g.drawImage(image, screenX + i * image.getWidth(), screenY + j * image.getHeight(), image.getWidth(), image.getHeight(), null);
				}
			}
		}
	}
	
	public void setCanvasSize(Dimension canvasSize) {
		this.canvasSize = canvasSize;
	}
	
	public double getX() {
		return x;
	}
	
	public double getY() {
		return y;
	}
	
	public void setX(double x) {
		this.x = x;
		newX = x;
	}
	
	public void setY(double y) {
		this.y = y;
		newY = y;
	}
}
