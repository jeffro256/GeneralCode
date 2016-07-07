package jeffrey_ryan.gamecore2d;

import javax.swing.JFrame;

public class GameFrame extends JFrame {
	private static final long serialVersionUID = 6020746239540948581L;
	
	private GamePanel panel;
	
	public GameFrame(String title, int width, int height) {
		super(title);
		
		setPanel(new GamePanel(width, height));

		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setLocationRelativeTo(null);
		setResizable(false);
	}
	
	public GamePanel getPanel() {
		return panel;
	}
	
	public void setPanel(GamePanel panel) {
		if (panel == null) {
			throw new IllegalArgumentException("panel == null!");
		}
		
		setContentPane(panel);
		pack();

		this.panel = panel;
	}
}
