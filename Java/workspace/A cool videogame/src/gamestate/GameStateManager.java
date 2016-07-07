package gamestate;

import java.awt.Graphics2D;
import java.util.*;

public class GameStateManager {
	protected List<GameState> states;
	
	private int currentState = 0;
	
	public GameStateManager() {
		states = new ArrayList<GameState>();
		states.add(new EmptyGameState());
	}
	
	public int getCurrentState() {
		return currentState;
	}
	
	public void setCurrentState(int newState) {
		if (newState < 0 || newState >= states.size()) {
			throw new IllegalArgumentException("State: '" + newState + "' is not between 0 and " + states.size());
		}
		else {
			currentState = newState;
		}
	}
	
	public int getNumStates() {
		return states.size();
	}
	
	public GameState getState(int state) {
		if (state < 0 || state >= states.size()) {
			throw new IllegalArgumentException("State: '" + state + "' is not between 0 and " + states.size());
		}
		
		return states.get(state);
	}
	
	public void add(GameState gm) {
		states.add(gm);
	}
	
	public void update(double seconds) {
		states.get(currentState).update(seconds);
	}
	
	public void render(Graphics2D g2, float interpolation) {
		states.get(currentState).render(g2, interpolation);
	}
}
