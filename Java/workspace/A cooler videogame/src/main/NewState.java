package main;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics2D;

import jeffrey_ryan.game.core.GameState;
import jeffrey_ryan.game.core.GameStateManager;

public class NewState extends GameState {
	public NewState(GameStateManager gsm) {
		super(gsm);
		// TODO Auto-generated constructor stub
	}

	@Override
	public void keyPressed(int arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void keyReleased(int arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void keyTyped(int arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseClicked(int arg0, int arg1) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseEntered(int arg0, int arg1) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(int arg0, int arg1) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(int arg0, int arg1) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseReleased(int arg0, int arg1) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void render(Graphics2D g, float interpolation) {
		g.setColor(Color.WHITE);
		g.fillOval((int) x, 200, 20, 20);
	}

	private double x = canvasSize.getWidth() / 2.0;
	
	@Override
	public void update(double seconds) {
	}
	
	public void setCanvasSize(Dimension d) {
		super.setCanvasSize(d);
		
		x = d.getWidth() / 2.0;
	}
}
