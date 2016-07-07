package baron_arena.states;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.event.KeyEvent;

import baron_arena.main.Game;

public class TitleState extends MenuState {
	private Font titleFont;
	private Font optionFont;
	
	public TitleState() {
		titleFont = new Font("Century Gothic", Font.PLAIN, 50);
		optionFont = new Font("Century Gothic", Font.PLAIN, 35);
	}
	
	@Override
	public void update(double seconds) {
		super.update(seconds);
	}
	
	@Override
	public void render(Graphics2D g, double interpolation) {
		super.render(g, interpolation);
		
		g.setColor(Color.DARK_GRAY);
		g.setFont(titleFont);
		int strLen = (int) g.getFontMetrics().getStringBounds(Game.TITLE, g).getWidth();
		g.drawString(Game.TITLE, canvasSize.width / 2 - strLen / 2, canvasSize.height / 5);
		
		g.setColor(Color.RED);
		g.setFont(optionFont);
		strLen = (int) g.getFontMetrics().getStringBounds("PLAY", g).getWidth();
		g.drawString("PLAY", canvasSize.width / 2 - strLen / 2, canvasSize.height / 2);
	}
	
	@Override
	public void keyPressed(KeyEvent e) { 
		int key = e.getKeyCode();
		
		if (key == KeyEvent.VK_ENTER) {
			gsm.setState(BaronManager.SELECTOR_STATE);
		}
	}
}
