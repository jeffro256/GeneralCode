package game;

import java.awt.*;
import javax.swing.*;
import gamestate.*;

public class Game {
	public static final String NAME = "Videogame";
	
	public static void main(String[] args) {
		JFrame frame = new JFrame(NAME);
		GameStateManager gsm = new GameStateManager();
		gsm.add(new GameState(gsm) {
			private double x;
			private double newX = GamePanel.WIDTH / 2;
			private double xVel = 60;
			
			public void update(double seconds) {
				x = newX;
				x += xVel * seconds;
				
				if (lastX - 20 < 0 || lastX + 20 >= GamePanel.WIDTH) {
					xVel *= -1;
				}
			}
			
			public void render(Graphics2D g2, float interpolation) {
				g2.setColor(new Color(0, (int) x % 255, 0));
				g2.fillRect(0, 0, GamePanel.WIDTH, GamePanel.HEIGHT);
				g2.setColor(new Color(255, 255, 255));
				g2.fillOval((int) ((x - lastX) * interpolation + lastX), GamePanel.HEIGHT / 2, 20, 20);
			}
		});
		gsm.setCurrentState(gsm.getCurrentState() + 1);
		GamePanel panel = new GamePanel(gsm);
		
		frame.add(panel);
		frame.pack();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setResizable(false);
		frame.setVisible(true);
	}
}
