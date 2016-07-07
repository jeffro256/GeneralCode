package main;

import javax.swing.JFrame;

import jeffrey_ryan.game.core.GamePanel;
import jeffrey_ryan.game.core.GameState;
import jeffrey_ryan.game.core.GameStateManager;

public class Game {
	public static void main(String[] args) {
		JFrame frame = new JFrame("A really cool videogame");
		GameStateManager gsm = new GameStateManager();
		GamePanel gpanel = new GamePanel(gsm);
		GameState state = new NewState(gsm);
		
		gsm.addState(state);
		frame.setContentPane(gpanel);
		frame.pack();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
}
