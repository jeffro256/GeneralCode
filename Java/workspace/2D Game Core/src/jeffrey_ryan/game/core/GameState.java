package jeffrey_ryan.game.core;

import java.awt.Dimension;

public abstract class GameState implements GameListener {
	protected GameStateManager gsm;
	protected Dimension canvasSize;	
	
	public GameState(GameStateManager gsm) {
		this.gsm = gsm;
	}
	
	public void setCanvasSize(Dimension d) {
		canvasSize = d;
	}
}
