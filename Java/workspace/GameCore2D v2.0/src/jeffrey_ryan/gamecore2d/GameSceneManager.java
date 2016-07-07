package jeffrey_ryan.gamecore2d;

import java.awt.Graphics2D;
import java.awt.Window;
import java.awt.event.WindowEvent;
import java.util.HashMap;
import java.util.Map;

import javax.swing.JComponent;
import javax.swing.SwingUtilities;

import jeffrey_ryan.gamecore2d.node.GameScene;

public class GameSceneManager implements GameListener {
	private Map<String, GameScene> scenes = new HashMap<String, GameScene>();
	private GameScene currentScene;
	private GamePanel panel;
	
	public GameScene getCurrentScene() {
		return currentScene;
	}
	
	public void setCurrentScene(String name) {
		if (currentScene != null && name == currentScene.name) return;
		
		if (currentScene != null) {
			currentScene.leave();
		}
		
		currentScene = scenes.get(name);
		safelyEnterScene();
	}
	
	public void addScene(GameScene scene) {
		if (scene == null) throw new IllegalArgumentException("scene == null");
		
		scenes.put(scene.getName(), scene);
		scene.setManager(this);
		
		if (currentScene == null) {
			setCurrentScene(scene.name);
		}
	}
	
	public GamePanel getPanel() {
		return panel;
	}
	
	public void setPanel(GamePanel panel) {
		if (panel == null) throw new IllegalArgumentException("panel == null");
		
		this.panel = panel;
		
		safelyEnterScene();
	}
	
	// TODO Maybe make GameScene implements Closeable
	public void requestExit() {
		currentScene.leave();
		Window window = SwingUtilities.getWindowAncestor(panel);
		window.dispatchEvent(new WindowEvent(window, WindowEvent.WINDOW_CLOSING));
		System.exit(0); // Window should exit, but this is here just in case
	}
	
	@Override
	public void update(double seconds) {
		if (currentScene != null) {
			currentScene.update(seconds);
			currentScene.didUpdate();
		}
	}
	
	@Override
	public void render(Graphics2D g, float interpolation) {
		if (currentScene != null) {
			currentScene.render(g, interpolation);
		}
	}
	
	private void safelyEnterScene() {
		if (panel == null || currentScene == null) return;
		
		currentScene.enter();
		panel.setInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW, currentScene.getInputMap());
		panel.setActionMap(currentScene.getActionMap());
	}
}