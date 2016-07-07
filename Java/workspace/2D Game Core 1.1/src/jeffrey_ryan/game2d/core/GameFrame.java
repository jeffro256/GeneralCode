package jeffrey_ryan.game2d.core;

import javax.swing.JFrame;

import jeffrey_ryan.game2d.gamestate.GameStateManager;

public class GameFrame extends JFrame {
	private static final long serialVersionUID = 7688160905799558911L;

	private GameLoop loop;
	private GamePanel panel;
	private GameStateManager gsm;
	
	public GameFrame(String title, int width, int height) {
		super(title);
		
		setLoop(new GameLoop());
		setPanel(new GamePanel(width, height));
		setManager(new GameStateManager());
		
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setLocationRelativeTo(null);
		setResizable(false);
	}
	
	public GameFrame() {
		this("Game", 640, 480);
	}
	
	public GameStateManager getManager() {
		return gsm;
	}
	
	public void setManager(GameStateManager gsm) {
		if (gsm == null) {
			throw new IllegalArgumentException("gsm == null!");
		}
		
		panel.addGameListener(gsm);
		this.gsm = gsm;
	}
	
	public GamePanel getPanel() {
		return panel;
	}
	
	public void setPanel(GamePanel panel) {
		if (panel == null) {
			throw new IllegalArgumentException("panel == null!");
		}
		
		loop.addLoopListener(panel);
		setContentPane(panel);
		pack();
		this.panel = panel;
	}
	
	public GameLoop getLoop() {
		return loop;
	}
	
	public void setLoop(GameLoop loop) {
		if (loop == null) {
			throw new IllegalArgumentException("loop == null!");
		}
		
		this.loop = loop;
	}
}
