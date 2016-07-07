package baron_arena.entity;

import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.util.Random;

public abstract class Entity {
	private final static Random idGenerator = new Random(System.currentTimeMillis());
	
	private final long id = idGenerator.nextLong();
	
	public final long getID() {
		return id;
	}
	
	public abstract Rectangle getBounds();
	public abstract double getHealth();
	public abstract String getName();
	
	public abstract void update(double seconds);
	public abstract void render(Graphics2D g, float interpolation);
}
