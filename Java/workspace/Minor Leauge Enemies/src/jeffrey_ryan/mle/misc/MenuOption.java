package jeffrey_ryan.mle.misc;

import jeffrey_ryan.gamecore2d.GameSceneManager;
import jeffrey_ryan.gamecore2d.node.GameScene;

public class MenuOption implements Runnable {
	public String name;
	
	protected GameSceneManager gsm;
	protected String newSceneName;
	
	public MenuOption(String name, GameSceneManager gsm, String newSceneName) {
		this.name = name;
		this.gsm = gsm;
		this.newSceneName = newSceneName;
	}
	
	public MenuOption(String name, GameSceneManager gsm, GameScene newScene) {
		this(name, gsm, newScene.name);
	}
	
	@Override
	public void run() {
		gsm.setCurrentScene(newSceneName);
	}
}
