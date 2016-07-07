import jeffrey_ryan.game2d.core.GameFrame;
import jeffrey_ryan.game2d.gamestate.GameState;

public class BotMain {
	public static void main(String[] args) {
		GameFrame frame = new GameFrame("Roman Kangaroo", 640, 480);
		GameState state = new BotState();
		
		frame.getManager().addState(state);
		frame.getLoop().start();
		frame.setVisible(true);
	}
}
