package jeffrey_ryan.game.core;

public class GameLoop implements Runnable {
	private boolean running = false;
	private boolean paused = false;
	private float gameHertz = 30.0f;
	private long timeBetweenUpdates = (long) (1_000_000_000 / gameHertz);
	private int maxUpdates = 5;
	private LoopListener loopListener;
	
	public void run() {
		long lastUpdateTime = System.nanoTime();
		running = true;
		
		while (running) {
			long now = System.nanoTime();
			
			if (!paused) {
				int updates = 0;
				
				while (now - lastUpdateTime >= timeBetweenUpdates && updates < maxUpdates) {
					if (loopListener != null) {
						loopListener.update((double) timeBetweenUpdates / 1_000_000_000);
					}
					
					lastUpdateTime += timeBetweenUpdates;
					updates++;
				}
				
				if (loopListener != null) {
					float interpolation = Math.min(1.0f, (float) (now - lastUpdateTime) / timeBetweenUpdates);
					loopListener.render(interpolation);
				}
			}
			
			try {
				Thread.sleep(1);
			}
			catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	public void start() {
		running = true;
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
	
	public void setLoopListener(LoopListener listener) {
		loopListener = listener;
	}
}
