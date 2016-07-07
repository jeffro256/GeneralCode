package jeffrey_ryan.mle.main;

import javax.swing.SwingUtilities;

import jeffrey_ryan.gamecore2d.GameFrame;
import jeffrey_ryan.mle.states.MLEManager;

public class MLEMain {
public static final String TITLE = "Jakor";
	
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
		frame.getPanel().setManager(new MLEManager());
		frame.setVisible(true);
	}
}
