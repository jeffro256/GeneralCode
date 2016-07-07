package jeffrey_ryan.mle.misc;

import jeffrey_ryan.gamecore2d.GameSceneManager;

// TODO Change System.exit(0) to scene.requestExit() or something

public class ExitMenuOption extends MenuOption {
	public ExitMenuOption(GameSceneManager gsm) {
		super("Exit", gsm, "");
	}

	@Override
	public void run() {
		gsm.requestExit();
	}
}
