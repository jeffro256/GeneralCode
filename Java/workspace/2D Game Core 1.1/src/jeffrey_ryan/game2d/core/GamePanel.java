package jeffrey_ryan.game2d.core;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseWheelEvent;
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JPanel;

import jeffrey_ryan.game2d.gamestate.GameListener;
import jeffrey_ryan.game2d.input.KeyAndMouseListener;

public class GamePanel extends JPanel implements LoopListener, KeyAndMouseListener {
	private static final long serialVersionUID = 3566029733726647228L;

	private List<GameListener> listeners;
	private BufferedImage image;
	private Graphics2D g;
	
	public GamePanel(int width, int height) {
		super();
		
		listeners = new ArrayList<GameListener>();
		
		setFocusable(true);
		setPreferredSize(new Dimension(width, height));
		setCanvasSize(width, height);
	}
	
	public GamePanel() {
		this(640, 480);
	}
	
	@Override
	public void addNotify() {
		super.addNotify();
		
		addKeyListener(this);
		addMouseListener(this);
		addMouseMotionListener(this);
	}
	
	public void addGameListener(GameListener listener) {
		if (listener == null) {
			throw new IllegalArgumentException("listener == null!");
		}
		
		listener.setCanvasSize(getCanvasSize());
		listeners.add(listener);
	}
	
	public Dimension getCanvasSize() {
		return new Dimension(image.getWidth(), image.getHeight());
	}
	 
	public void setCanvasSize(int width, int height) {
		image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
		g = image.createGraphics();
		
		for (GameListener listener : listeners) {
			listener.setCanvasSize(new Dimension(width, height));
		}
	}
	
	public GameListener[] getListeners() {
		return (GameListener[]) listeners.toArray();
	}

	@Override
	public void update(double seconds) {
		for (GameListener listener : listeners) {
			listener.update(seconds);
		}
	}

	@Override
	public synchronized void render(double interpolation) {
		for (GameListener listener : listeners) {
			listener.render(g, interpolation);
		}
		
		repaint();
	}
	
	@Override
	public synchronized void paintComponent(Graphics g) {
		g.drawImage(image, 0, 0, getWidth(), getHeight(), null);
	}
	
	public Point getPointOnCanvas(int x, int y) {
		return new Point(x * image.getWidth() / getWidth(), y * image.getHeight() / getHeight());
	}
	
	public MouseEvent getCanvasMouseEvent(MouseEvent e) {
		Point p = getPointOnCanvas(e.getX(), e.getY());
		return new MouseEvent(e.getComponent(), e.getID(), e.getWhen(), e.getModifiers(), p.x, p.y, e.getXOnScreen(), e.getYOnScreen(), e.getClickCount(), e.isPopupTrigger(), e.getButton());
	}

	@Override
	public void keyTyped(KeyEvent e) {
		for (GameListener listener : listeners) {
			listener.keyTyped(e);
		}
	}

	@Override
	public void keyPressed(KeyEvent e) {
		for (GameListener listener : listeners) {
			listener.keyPressed(e);
		}
	}

	@Override
	public void keyReleased(KeyEvent e) {
		for (GameListener listener : listeners) {
			listener.keyReleased(e);
		}
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		for (GameListener listener : listeners) {
			listener.mouseClicked(getCanvasMouseEvent(e));
		}
	}

	@Override
	public void mousePressed(MouseEvent e) {
		for (GameListener listener : listeners) {
			listener.mousePressed(getCanvasMouseEvent(e));
		}
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		for (GameListener listener : listeners) {
			listener.mouseReleased(getCanvasMouseEvent(e));
		}
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		for (GameListener listener : listeners) {
			listener.mouseEntered(getCanvasMouseEvent(e));	
		}
	}

	@Override
	public void mouseExited(MouseEvent e) {
		for (GameListener listener : listeners) {
			listener.mouseExited(getCanvasMouseEvent(e));
		}
	}

	@Override
	public void mouseDragged(MouseEvent e) {
		for (GameListener listener : listeners) {
			listener.mouseDragged(getCanvasMouseEvent(e));
		}
	}

	@Override
	public void mouseMoved(MouseEvent e) {
		for (GameListener listener : listeners) {
			listener.mouseMoved(getCanvasMouseEvent(e));
		}
	}

	@Override
	public void mouseWheelMoved(MouseWheelEvent e) {
		Point p = getPointOnCanvas(e.getX(), e.getY());
		MouseWheelEvent we = new MouseWheelEvent(e.getComponent(), e.getID(), e.getWhen(), e.getModifiers(), p.x, p.y, e.getXOnScreen(), e.getYOnScreen(), e.getClickCount(), e.isPopupTrigger(), e.getScrollType(), e.getScrollAmount(), e.getWheelRotation(), e.getPreciseWheelRotation());
		
		for (GameListener listener : listeners) {
			listener.mouseWheelMoved(we);
		}
	}
}
