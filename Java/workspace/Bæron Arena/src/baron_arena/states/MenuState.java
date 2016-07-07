package baron_arena.states;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics2D;

import baron_arena.misc.Background;
import jeffrey_ryan.game2d.gamestate.GameState;

public class MenuState extends GameState {
	private static Background back;
	
	static {
		try {
			back = new Background("/Images/clouds.png");
			back.xVel = 30;
			back.yVel = -5;
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	@Override
	public void update(double seconds) {
		back.update(seconds);
	}
	
	@Override
	public void render(Graphics2D g, double interpolation) {
		g.setBackground(Color.CYAN);
		super.render(g, interpolation);
		
		g.setColor(Color.YELLOW);
		g.fillOval(canvasSize.width - 120, 40, 80, 80);
		
		back.render(g, interpolation);
	}
	
	@Override
	public void setCanvasSize(Dimension canvasSize) {
		super.setCanvasSize(canvasSize);

		back.setCanvasSize(canvasSize);
	}
}
