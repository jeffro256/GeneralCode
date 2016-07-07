package jeffrey_ryan.game.core;

import java.awt.Graphics2D;
import java.awt.Dimension;
import java.util.*;

public class GameStateManager implements GameListener {
	protected List<GameState> states = new ArrayList<GameState>();
	
	private int currentState = -1;
	
	public int getState() {
		return currentState;
	}
	
	public void setState(int state) {
		if (state < 0 || state >= states.size()) {
			throw new IllegalArgumentException("State '" + state + "' is out of bounds!");
		}
		
		currentState = state;
	}
	
	public void addState(GameState state) {
		states.add(state);
		
		if (currentState == -1) {
			currentState = 0;
		}
	}
	
	public void setCanvasSize(Dimension d) {
		for (GameState g : states) {
			g.setCanvasSize(d);
		}
	}
	
	public void update(double seconds) {
		if (currentState != -1) {
			states.get(currentState).update(seconds);
		}
	}
	
	public void render(Graphics2D g, float interpolation) {
		if (currentState != -1) {
			states.get(currentState).render(g, interpolation);
		}
	}

	public void mouseClicked(int x, int y) {
		if (currentState != -1) {
			states.get(currentState).mouseClicked(x, y);
		}
	}

	public void mouseEntered(int x, int y) {
		if (currentState != -1) {
			states.get(currentState).mouseEntered(x, y);
		}
	}

	public void mouseExited(int x, int y) {	
		if (currentState != -1) {
			states.get(currentState).mouseExited(x, y);
		}
	}

	public void mousePressed(int x, int y) {
		if (currentState != -1) {
			states.get(currentState).mousePressed(x, y);
		}
	}

	public void mouseReleased(int x, int y) {
		if (currentState != -1) {
			states.get(currentState).mouseReleased(x, y);
		}
	}

	public void keyPressed(int key) {
		if (currentState != -1) {
			states.get(currentState).keyPressed(key);
		}
	}

	public void keyReleased(int key) {
		if (currentState != -1) {
			states.get(currentState).keyReleased(key);
		}
	}

	public void keyTyped(int key) {
		if (currentState != -1) {
			states.get(currentState).keyTyped(key);
		}
	}
}
