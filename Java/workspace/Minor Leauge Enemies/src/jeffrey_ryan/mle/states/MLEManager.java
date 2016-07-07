package jeffrey_ryan.mle.states;

import jeffrey_ryan.gamecore2d.GameSceneManager;
import jeffrey_ryan.mle.misc.ExitMenuOption;
import jeffrey_ryan.mle.misc.MenuOption;

public class MLEManager extends GameSceneManager {
	public MLEManager() {
		PlayState ps = new PlayState();
		MenuOption[] options = { new MenuOption("Play", this, ps), new ExitMenuOption(this) };
		TitleState titleState = new TitleState("Jakor", options);
		addScene(titleState);
		
		addScene(ps);
	}
}
