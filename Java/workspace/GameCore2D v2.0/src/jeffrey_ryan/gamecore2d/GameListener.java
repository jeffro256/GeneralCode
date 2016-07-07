package jeffrey_ryan.gamecore2d;

import java.awt.Graphics2D;

public interface GameListener {
	public void update(double seconds);
	public void render(Graphics2D g, float interpolation);
}
