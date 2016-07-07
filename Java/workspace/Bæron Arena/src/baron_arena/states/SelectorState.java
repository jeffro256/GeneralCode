package baron_arena.states;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.event.KeyEvent;
import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;

import jeffrey_ryan.game2d.gamestate.GameState;

public class SelectorState extends MenuState {
	private BufferedImage lock;
	private int currentChoice = 0;
	private int numLevels = 1;
	private int levelsUnlocked = 1;
	private int locksAcross = 6;
	
	public SelectorState() {
		try {
			lock = ImageIO.read(getClass().getResourceAsStream("/Images/lock.png"));
		}
		catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	@Override
	public void render(Graphics2D g, double interpolation) {
		super.render(g, interpolation);
		
		int firstX = 50;
		int firstY = 50;
		float scale = 2;
		float lockSizeRatio = 0.85f;
		
		int dropSideLen = (int) (Math.max(lock.getWidth(), lock.getHeight()) * scale);
		int padding = dropSideLen / 5;
		
		int lockDropGrayLevel = 200;
		Color lockDropColor = new Color(lockDropGrayLevel, lockDropGrayLevel, lockDropGrayLevel);
		
		Font levelFont = new Font("Century Gothic", Font.PLAIN, 40);
		g.setFont(levelFont);
		
		for (int i = 0; i < numLevels; i++) {
			int x = (dropSideLen + padding) * (i % locksAcross) + firstX;
			int y = (dropSideLen + padding) * (i / locksAcross) + firstY;
			
			g.setColor(lockDropColor);
			g.fillRect(x, y, dropSideLen, dropSideLen);
			
			if (i >= levelsUnlocked) {
				int lockWidth = (int) (lock.getWidth() * scale * lockSizeRatio);
				int lockHeight = (int) (lock.getHeight() * scale * lockSizeRatio);
				
				g.drawImage(lock, x + dropSideLen / 2 - lockWidth / 2, y + dropSideLen / 2 - lockHeight / 2, lockWidth, lockHeight, null);
			}
			else {
				String lvlString = new Integer(i + 1).toString();
				int strLen = (int) g.getFontMetrics().getStringBounds(lvlString, g).getWidth();
				int strHeight = g.getFont().createGlyphVector(g.getFontRenderContext(), lvlString).getPixelBounds(null, 0, 0).height;
				
				g.setColor(Color.BLACK);
				g.drawString(lvlString, x + dropSideLen / 2 - strLen / 2, y + dropSideLen / 2 + strHeight / 2);
			}
			
			if (i == currentChoice) {
				g.setColor(Color.BLUE);
				g.drawRect(x, y, dropSideLen, dropSideLen);
			}
		}
	}
	
	@Override
	public void keyPressed(KeyEvent e) {
		int key = e.getKeyCode();
		
		switch (key) {
		case KeyEvent.VK_UP:
			currentChoice -= locksAcross;
			break;
		case KeyEvent.VK_DOWN:
			currentChoice += locksAcross;
			break;
		case KeyEvent.VK_LEFT:
			currentChoice -= 1;
			break;
		case KeyEvent.VK_RIGHT:
			currentChoice += 1;
			break;
		case KeyEvent.VK_ENTER:
			try {
				GameState state = new MapState();
				gsm.addState(state);
				gsm.setState(gsm.getState() + 1);
			}
			catch (Exception ex) {
				ex.printStackTrace();
			}
			break;
		case KeyEvent.VK_ESCAPE:
			gsm.setState(BaronManager.TITLE_STATE);
		}
		
		if (currentChoice < 0) {
			currentChoice = 0;
		}
		else if (currentChoice >= levelsUnlocked) {
			currentChoice = levelsUnlocked - 1;
		}
	}
}
