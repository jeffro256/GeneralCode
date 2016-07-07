package baron_arena.main;

import javax.swing.SwingUtilities;

import baron_arena.states.BaronManager;
import jeffrey_ryan.game2d.core.GameFrame;

public class Game {
	public static final String TITLE = "Bæron Arena";
	
	private static final int WIDTH = 640;
	private static final int HEIGHT = WIDTH * 3 / 4;
	
	public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				createGUI();
			}
		});
	}
	
	public static void createGUI() {
		GameFrame frame = new GameFrame(TITLE, WIDTH, HEIGHT);
		frame.setResizable(false);
		frame.setManager(new BaronManager());
		frame.align();
		frame.getLoop().start();
		frame.setVisible(true);
	}
}
