package gamestate;

import java.awt.*;

public abstract class GameState {
	protected GameStateManager gsm;
	
	public GameState(GameStateManager gsm) {
		this.gsm = gsm;
	}
	
	public abstract void update(double seconds);
	public abstract void render(Graphics2D g2, float interpolation);
}
