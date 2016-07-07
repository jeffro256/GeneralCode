package jeffrey_ryan.gamecore2d.node;

import java.awt.Dimension;
import java.awt.Graphics2D;

import javax.swing.ActionMap;
import javax.swing.ComponentInputMap;

import jeffrey_ryan.gamecore2d.GameSceneManager;

public class GameScene extends GameNode {
	protected GameSceneManager gsm;
	protected ComponentInputMap inputMap;
	protected ActionMap actionMap;
	
	public GameScene() {
		parent = this;
		scene = this;
	}
	
	public void enter() {
		inputMap = new ComponentInputMap(gsm.getPanel());
		actionMap = new ActionMap();
	}
	
	public void leave() {}
	
	public void requestExit() {
		gsm.requestExit();
	}
	
	public Dimension getCanvasSize() {
		return new Dimension(gsm.getPanel().getCanvasSize());
	}

	public void setManager(GameSceneManager gsm) {
		if (gsm == null) throw new IllegalArgumentException("gsm == null");
		
		this.gsm = gsm;
	}
	
	public ComponentInputMap getInputMap() {
		return inputMap;
	}
	
	public ActionMap getActionMap() {
		return actionMap;
	}
	
	@Override
	public void addChild(GameNode child) {
		children.add(child);
		
		child.parent = this;
		child.scene = this;
	}
	
	@Override
	public void render(Graphics2D g, float interpolation) {
		Dimension canvasSize = gsm.getPanel().getCanvasSize();
		g.clearRect(0, 0, canvasSize.width, canvasSize.height);
		
		super.render(g, interpolation);
	}
}
