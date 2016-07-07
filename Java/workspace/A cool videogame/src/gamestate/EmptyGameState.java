package gamestate;

import java.awt.Graphics2D;

public class EmptyGameState extends GameState {
	public EmptyGameState() {
		super(null);
	}
	
	public void update(double seconds) {}
	public void render(Graphics2D g2, float interpolation) {}
}
