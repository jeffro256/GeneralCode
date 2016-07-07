package baron_arena.states;

import jeffrey_ryan.game2d.gamestate.GameStateManager;

public class BaronManager extends GameStateManager {
	public static final int TITLE_STATE = 0;
	public static final int SELECTOR_STATE = 1;
	
	public BaronManager() {
		addState(new TitleState());
		addState(new SelectorState());
	}
}
