package jeffrey_ryan.game.core;

import java.awt.*;
import java.awt.image.BufferedImage;

import javax.swing.JPanel;

public class GamePanel extends JPanel implements LoopListener {
	private static final long serialVersionUID = 1L;
	
	private GameLoop loop = new GameLoop();
	private GameStateManager gsm;
	private BufferedImage image;
	private Graphics2D g;
	
	public GamePanel(GameStateManager gsm, int width, int height) {
		super();
		
		this.gsm = gsm;
		
		setFocusable(true);
		setPreferredSize(new Dimension(width, height));
		setCanvasSize(width, height);
		
		loop.setLoopListener(this);
	}
	
	public GamePanel(GameStateManager gsm) {
		this(gsm, 640, 480);
	}
	
	@Override
	public void addNotify() {
		super.addNotify();
		
		Thread thread = new Thread(loop);
		thread.start();
	}
	 
	public void setCanvasSize(int width, int height) {
		image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
		g = image.createGraphics();
		gsm.setCanvasSize(new Dimension(width, height));
	}

	public void update(double seconds) {
		gsm.update(seconds);
	}

	public void render(float interpolation) {
		gsm.render(g, interpolation);
		Graphics2D g2 = (Graphics2D) getGraphics();
		Dimension panelSize = getSize();
		g2.drawImage(image, 0, 0, panelSize.width, panelSize.height, null);
		g2.dispose();
	}
}
