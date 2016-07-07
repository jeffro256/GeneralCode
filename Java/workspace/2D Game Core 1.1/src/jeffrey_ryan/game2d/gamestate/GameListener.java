package jeffrey_ryan.game2d.gamestate;

import java.awt.Dimension;
import java.awt.Graphics2D;

import jeffrey_ryan.game2d.input.KeyAndMouseListener;

public interface GameListener extends KeyAndMouseListener {
	public void update(double seconds);
	public void render(Graphics2D g, double interpolation);
	public void setCanvasSize(Dimension canvasSize);
}
