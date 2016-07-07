package jeffrey_ryan.game2d.core;

import java.util.*;

public class GameLoop implements Runnable {
	private boolean running = false;
	private boolean paused = false;
	private float gameHertz = 32.0f;
	private long timeBetweenUpdates = (long) (1_000_000_000 / gameHertz);
	private int maxUpdates = 5;
	private List<LoopListener> loopListeners = new ArrayList<LoopListener>();
	
	public void run() {
		long lastUpdateTime = System.nanoTime();
		running = true;
		
		while (running) {
			long now = System.nanoTime();
			if (!paused) {
				int updates = 0;
				
				while (now - lastUpdateTime >= timeBetweenUpdates && updates < maxUpdates) {
					double seconds = 1 / gameHertz;

					for (LoopListener listener : loopListeners) {	
						listener.update(seconds);
					}

					lastUpdateTime += timeBetweenUpdates;
					updates++;
				}
				
				double interpolation = Math.min(1.0, (double) (now - lastUpdateTime) / timeBetweenUpdates);
				
				for (LoopListener listener : loopListeners) {
					listener.render(interpolation);
				}
				
				long timeRemaining = (timeBetweenUpdates - (now - lastUpdateTime)) / 1_000_000;
				
				try {
					Thread.sleep(Math.max(timeRemaining - 5, 0));
				}
				catch (InterruptedException ie) {
					ie.printStackTrace();
				}
			}
			else {
				try {
					Thread.sleep(25);
				}
				catch (InterruptedException ie) {
					ie.printStackTrace();
				}
			}
		}
	}
	
	public boolean isRunning() {
		return running;
	}
	
	public void start(String name) {
		new Thread(this, name).start();
	}
	
	public void start() {
		start("GameLoop");
	}
	
	public void stop() {
		running = false;
	}
	
	public void pause() {
		paused = true;
	}
	
	public void play() {
		paused = false;
	}
	
	public float getSpeed() {
		return gameHertz;
	}
	
	public void setSpeed(float hertz) {
		gameHertz = hertz;
		timeBetweenUpdates = (long) (1_000_000_000 / gameHertz);
	}
	
	public int getMaxUpdates() {
		return maxUpdates;
	}
	
	public void setMaxUpdates(int updates) { 
		maxUpdates = updates;
	}
	
	public void addLoopListener(LoopListener listener) {
		if (listener == null) {
			throw new IllegalArgumentException("listener == null!");
		}
		
		loopListeners.add(listener);
	}
	
	public boolean removeLoopListener(LoopListener listener) {
		return loopListeners.remove(listener);
	}
}
