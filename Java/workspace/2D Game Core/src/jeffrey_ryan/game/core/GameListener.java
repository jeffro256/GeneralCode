package jeffrey_ryan.game.core;

import java.awt.Graphics2D;

public interface GameListener {
	public void update(double seconds);
	public void render(Graphics2D g, float interpolation);
	
	public void mouseClicked(int x, int y);
	public void mouseEntered(int x, int y);
	public void mouseExited(int x, int y);
	public void mousePressed(int x, int y);
	public void mouseReleased(int x, int y);
	
	public void keyPressed(int key);
	public void keyReleased(int key);
	public void keyTyped(int key);
}
