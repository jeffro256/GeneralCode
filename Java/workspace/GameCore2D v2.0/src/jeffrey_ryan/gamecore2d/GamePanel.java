package jeffrey_ryan.gamecore2d;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;

import javax.swing.JPanel;

public class GamePanel extends JPanel implements LoopListener {
	private static final long serialVersionUID = 3566029733726647228L;
	
	private GameLoop loop;
	private GameSceneManager gsm;
	private BufferedImage image;
	private Graphics2D g;
	
	public GamePanel(int width, int height) {
		super();
		
		setManager(new GameSceneManager());
		setLoop(new GameLoop());
		
		setFocusable(true);
		requestFocusInWindow();
		
		initCanvas(width, height);
	}
	
	private void initCanvas(int width, int height) {
		image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
		g = image.createGraphics();

		setPreferredSize(new Dimension(width, height));
	}
	
	public Dimension getCanvasSize() {
		return new Dimension(image.getWidth(), image.getHeight());
	}
	
	public void setLoop(GameLoop loop) {
		if (loop == null) throw new IllegalArgumentException("loop == null");
		
		loop.clearLoopListeners();
		loop.addLoopListener(this);
		
		this.loop = loop;
	}
	
	public void setManager(GameSceneManager gsm) {
		if (gsm == null) throw new IllegalArgumentException("gsm == null");
		
		gsm.setPanel(this);
		
		this.gsm = gsm;
	}
	
	@Override
	public void addNotify() {
		super.addNotify();
		
		loop.start("Game Loop");
	}

	@Override
	public void update(double seconds) {
		gsm.update(seconds);
	}

	@Override
	public synchronized void render(double interpolation) {
		gsm.render(g, (float) interpolation); 

		repaint();
	}
	
	@Override
	public synchronized void paintComponent(Graphics g) {
		super.paintComponent(g);
		
		g.drawImage(image, 0, 0, getWidth(), getHeight(), null);
	}
}
