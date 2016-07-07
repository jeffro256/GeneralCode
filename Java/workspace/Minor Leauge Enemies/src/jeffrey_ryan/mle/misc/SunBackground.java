package jeffrey_ryan.mle.misc;

import java.awt.Color;
import java.awt.Graphics2D;
import java.io.IOException;

public class SunBackground extends Background {
	public SunBackground(String path) throws IOException {
		super(path);
	}
	
	@Override
	public void render(Graphics2D g, float interpolation) {
		g.setColor(Color.YELLOW);
		g.fillOval(getCanvasSize().width - 120, 40, 80, 80);
		
		super.render(g, interpolation);
	}
}
