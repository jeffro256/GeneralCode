package jeffrey_ryan.game2d.gamestate;

import java.awt.Dimension;
import java.awt.Graphics2D;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseWheelEvent;

import jeffrey_ryan.game2d.input.KeyInputHandler;
import jeffrey_ryan.game2d.input.MouseInputHandler;

public abstract class GameState implements GameListener {
	protected GameStateManager gsm;
	protected Dimension canvasSize;	
	protected KeyInputHandler keyHandler;
	protected MouseInputHandler mouseHandler;
	
	public GameState() {
		keyHandler = new KeyInputHandler();
		mouseHandler = new MouseInputHandler();
	}
	
	public void addNotify(GameStateManager gsm, Dimension canvasSize) {
		setManager(gsm);
		setCanvasSize(canvasSize);
	}
	
	public void setManager(GameStateManager gsm) {
		this.gsm = gsm;
	}
	
	@Override
	public void render(Graphics2D g, double interpolation) {
		g.clearRect(0, 0, canvasSize.width, canvasSize.height);
	}
	
	@Override
	public void setCanvasSize(Dimension canvasSize) {
		this.canvasSize = canvasSize;
	}
	
	@Override
	public void keyTyped(KeyEvent e) {}
	
	@Override
	public void keyPressed(KeyEvent e)  {
		keyHandler.keyPressed(e);
	}
	
	@Override
	public void keyReleased(KeyEvent e)  {
		keyHandler.keyReleased(e);
	}
	
	@Override
	public void mouseClicked(MouseEvent e) {
		mouseHandler.mouseClicked(e);
	}
	
	@Override
	public void mouseEntered(MouseEvent e) {
		mouseHandler.mouseEntered(e);
	}
	
	@Override
	public void mouseExited(MouseEvent e) {
		mouseHandler.mouseExited(e);
	}
	
	@Override
	public void mousePressed(MouseEvent e) {
		mouseHandler.mousePressed(e);
	}
	
	@Override
	public void mouseReleased(MouseEvent e) {
		mouseHandler.mouseReleased(e);
	}
	
	@Override
	public void mouseDragged(MouseEvent e) {
		mouseHandler.mouseDragged(e);
	}
	
	@Override
	public void mouseMoved(MouseEvent e) {
		mouseHandler.mouseMoved(e);
	}
	
	@Override
	public void mouseWheelMoved(MouseWheelEvent e) {
		mouseHandler.mouseWheelMoved(e);
	}
}
