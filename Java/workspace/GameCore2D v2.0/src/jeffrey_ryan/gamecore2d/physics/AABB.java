package jeffrey_ryan.gamecore2d.physics;

import java.awt.geom.Rectangle2D;

public class AABB extends Rectangle2D.Double {
	private static final long serialVersionUID = -8144864317205414339L;
	
	public AABB(double x, double y, double w, double h) {
		super(x, y, w, h);
	}
}
