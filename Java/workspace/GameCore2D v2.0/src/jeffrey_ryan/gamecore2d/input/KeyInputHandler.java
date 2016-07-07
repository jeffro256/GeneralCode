package jeffrey_ryan.gamecore2d.input;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class KeyInputHandler implements KeyListener {
	private boolean[] keys;
	
	public KeyInputHandler(int numKeys) {
		if (numKeys < 0) {
			throw new IllegalArgumentException("numKeys < 0!");
		}
		
		keys = new boolean[numKeys];
	}
	
	public KeyInputHandler() {
		this(256);
	}
	
	public boolean getKey(int key) {
		if (key >= 0 && key < keys.length) {
			return keys[key];
		}
		
		throw new IllegalArgumentException("key '" + key + "' not in bounds!");
	}
	
	@Override
	public void keyTyped(KeyEvent e) {}

	@Override
	public void keyPressed(KeyEvent e) {
		int key = e.getKeyCode();
		
		if (key >= 0 && key < keys.length) {
			keys[key] = true;
		}
	}

	@Override
	public void keyReleased(KeyEvent e) {
		int key = e.getKeyCode();
		
		if (key >= 0 && key < keys.length) {
			keys[key] = false;
		}
	}
}
