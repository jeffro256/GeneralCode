package game;

import java.awt.*;
import java.awt.image.BufferedImage;

import javax.swing.*;

import gamestate.GameStateManager;

public class GamePanel extends JPanel implements Runnable {
	public static final int WIDTH = 640;
	public static final int HEIGHT = 480;
	
	private static final long serialVersionUID = 1L;
	
	private boolean running = false;
	private boolean paused = false;
	private BufferedImage image;
	private Graphics2D g2;
	
	public GameStateManager gsm;
	
	public GamePanel(GameStateManager gsm) {
		super();
		
		this.gsm  = gsm;
	}
	
	@Override
	public void addNotify() {
		super.addNotify();
		init();
		
		try {
			Thread thread = new Thread(this);
			thread.start();
		}
		catch (Exception e) {
			System.err.println(e);
		}
	}
	
	protected void init() {
		setPreferredSize(new Dimension(WIDTH, HEIGHT));
		
		running = true;
		image = new BufferedImage(WIDTH, HEIGHT, BufferedImage.TYPE_INT_RGB);
		g2 = image.createGraphics();
	}
	
	public void run() {
		final int GAME_HERTZ = 30;
		final long TIME_BETWEEN_UPDATES = 1_000_000_000 / GAME_HERTZ;
		final int MAX_UPDATES = 5;
		long lastUpdateTime = System.nanoTime();
		
		while (running) {
			if (!paused) {
				long now = System.nanoTime();
				int updates = 0;
				
				while (now - lastUpdateTime >= TIME_BETWEEN_UPDATES && updates < MAX_UPDATES) {
					update(TIME_BETWEEN_UPDATES / 1_000_000_000.0);
					lastUpdateTime += TIME_BETWEEN_UPDATES;
					updates++;
				}
				
				float interpolation = Math.min(1.0f, (float) (now - lastUpdateTime) / TIME_BETWEEN_UPDATES);
				render(g2, interpolation);
			}
			try {
				Thread.sleep(1);
			}
			catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	public void update(double seconds) {
		gsm.update(seconds);
	}
	
	public void render(Graphics2D g2, float interpolation) {
		gsm.render(g2, interpolation);
		Graphics2D thisGraphics = (Graphics2D) getGraphics();
		thisGraphics.drawImage(image, 0, 0, WIDTH, HEIGHT, null);
		thisGraphics.dispose();
	}
	
	public synchronized void pause() {
		paused = true;
	}
	
	public synchronized void play() {
		paused = false;
	}
	
	public synchronized void start() {
		running = true;
	}
	
	public synchronized void stop() {
		running = false;
	}
	
	public boolean paused() {
		return paused;
	}
	
	public boolean running() {
		return running;
	}
}
