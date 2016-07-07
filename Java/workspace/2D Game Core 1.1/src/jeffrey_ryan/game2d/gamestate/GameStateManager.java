package jeffrey_ryan.game2d.gamestate;

import java.awt.Graphics2D;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseWheelEvent;
import java.awt.Dimension;
import java.util.*;

public class GameStateManager implements GameListener {
	protected List<GameState> states = new ArrayList<GameState>();
	
	private int currentState = -1;
	private Dimension canvasSize;
	
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
		
		state.addNotify(this, canvasSize);
		
		if (currentState == -1) {
			currentState = 0;
		}
	}
	
	public void setCanvasSize(Dimension d) {
		canvasSize = d;
		
		for (GameState g : states) {
			g.setCanvasSize(d);
		}
	}
	
	public void update(double seconds) {
		if (currentState != -1) {
			states.get(currentState).update(seconds);
		}
	}
	
	public void render(Graphics2D g, double interpolation) {
		if (currentState != -1) {
			states.get(currentState).render(g, interpolation);
		}
	}

	@Override
	public void keyTyped(KeyEvent e) {
		if (currentState != -1) {
			states.get(currentState).keyTyped(e);
		}
	}

	@Override
	public void keyPressed(KeyEvent e) {
		if (currentState != -1) {
			states.get(currentState).keyPressed(e);
		}
	}

	@Override
	public void keyReleased(KeyEvent e) {
		if (currentState != -1) {
			states.get(currentState).keyReleased(e);
		}	
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		if (currentState != -1) {
			states.get(currentState).mouseClicked(e);
		}
	}

	@Override
	public void mousePressed(MouseEvent e) {
		if (currentState != -1) {
			states.get(currentState).mousePressed(e);
		}
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		if (currentState != -1) {
			states.get(currentState).mouseReleased(e);
		}
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		if (currentState != -1) {
			states.get(currentState).mouseEntered(e);
		}
	}

	@Override
	public void mouseExited(MouseEvent e) {
		if (currentState != -1) {
			states.get(currentState).mouseExited(e);
		}
	}

	@Override
	public void mouseDragged(MouseEvent e) {
		if (currentState != -1) {
			states.get(currentState).mouseDragged(e);
		}
	}

	@Override
	public void mouseMoved(MouseEvent e) {
		if (currentState != -1) {
			states.get(currentState).mouseMoved(e);
		}
	}

	@Override
	public void mouseWheelMoved(MouseWheelEvent e) {
		if (currentState != -1) {
			states.get(currentState).mouseWheelMoved(e);
		}
	}
}