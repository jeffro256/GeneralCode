package jeffrey_ryan.mle.states;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;

import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.KeyStroke;

import jeffrey_ryan.gamecore2d.node.GameScene;
import jeffrey_ryan.mle.misc.SunBackground;

public class MenuState extends GameScene {
	private static SunBackground back;
	
	static {
		try {
			back = new SunBackground("/Backgrounds/clouds.png");
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
	public void render(Graphics2D g, float interpolation) {
		g.setBackground(Color.CYAN);
		super.render(g, interpolation);
		
		back.render(g, interpolation);
	}

	@Override
	public void enter() {
		super.enter();
		
		inputMap.put(KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0), "Exit Game");
		
		Action exitAction = new AbstractAction() {
			private static final long serialVersionUID = 1L;

			@Override
			public void actionPerformed(ActionEvent e) {
				requestExit();
			}
		};

		actionMap.put("Exit Game", exitAction);
		
		back.setCanvasSize(gsm.getPanel().getCanvasSize());
	}
}
