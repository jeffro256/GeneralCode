package jeffrey_ryan.game2d.input;

import java.awt.event.MouseEvent;
import java.awt.event.MouseWheelEvent;

public class MouseInputHandler implements FullMouseListener {
	private int mouseX;
	private int mouseY;
	private int button;
	private double clicks;
	
	public MouseInputHandler(int startX, int startY) {
		mouseX = startX;
		mouseY = startY;
		button = MouseEvent.NOBUTTON;
		clicks = 0;
	}
	
	public MouseInputHandler() {
		this(0, 0);
	}
	
	public int getMouseX() {
		return mouseX;
	}
	
	public int getMouseY() {
		return mouseY;
	}
	
	public int getButton() {
		return button;
	}
	
	public int getClicks() {
		return (int) getPreciseClicks();
	}
	
	public double getPreciseClicks() {
		return clicks;
	}
	
	public void clearClicks() {
		clicks = 0;
	}
	
	@Override
	public void mouseWheelMoved(MouseWheelEvent e) {
		mouseX = e.getX();
		mouseY = e.getY();
		button = e.getButton();
		clicks += e.getPreciseWheelRotation();
	}

	@Override
	public void mouseDragged(MouseEvent e) {
		mouseX = e.getX();
		mouseY = e.getY();
		button = e.getButton();
	}

	@Override
	public void mouseMoved(MouseEvent e) {
		mouseX = e.getX();
		mouseY = e.getY();
		button = e.getButton();
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		mouseX = e.getX();
		mouseY = e.getY();
		button = e.getButton();
	}

	@Override
	public void mousePressed(MouseEvent e) {
		mouseX = e.getX();
		mouseY = e.getY();
		button = e.getButton();
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		mouseX = e.getX();
		mouseY = e.getY();
		button = e.getButton();	
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		mouseX = e.getX();
		mouseY = e.getY();
		button = e.getButton();
	}

	@Override
	public void mouseExited(MouseEvent e) {
		mouseX = e.getX();
		mouseY = e.getY();
		button = e.getButton();
	}
}
