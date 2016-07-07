package jeffrey_ryan.mle.player;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Point;

import jeffrey_ryan.gamecore2d.node.GameNode;
import jeffrey_ryan.gamecore2d.physics.AABB;
import jeffrey_ryan.gamecore2d.physics.PhysicsBody;
import jeffrey_ryan.gamecore2d.physics.Vector2D;
import jeffrey_ryan.mle.map.GameMap;

public class Player extends GameNode {
	public Vector2D size = new Vector2D(0.75, 1.75);
	public double moveSpeed = 6; 		// TODO Make this not baked in
	public Color color;
	
	private GameMap map;
	
	public Player(String name, Color color) {
		super(name);
		
		if (color == null) throw new IllegalArgumentException("color == null");
		
		this.color = color;
		this.pbody = new PhysicsBody();
		this.pbody.node = this;
	}

	@Override
	public void update(double seconds) {
		pbody.accel.y -= 9.8;
		
		super.update(seconds);
	}
	
	@Override
	public void didUpdate() {
		loadMap();
		
		if (pos.y - size.y / 2 < -map.getSize().y / 2) {
			pbody.vel.y = 0;
			pos.y = -map.getSize().y / 2 + size.y / 2;
		}
		
		super.didUpdate();
	}
	
	@Override
	public void render(Graphics2D g, float interpolation) {
		super.render(g, interpolation);
		
		loadMap();
		
		Point rp1 = map.transformToScreen(new Vector2D(pos.x - size.x / 2, pos.y + size.y / 2));
		Point rp2 = map.transformToScreen(new Vector2D(pos.x + size.x / 2, pos.y - size.y / 2));
		g.setColor(color);
		g.fillRect(rp1.x, rp1.y, rp2.x - rp1.x, rp2.y - rp1.y);
	}
	
	private void loadMap() {
		if (map == null) {
			map = (GameMap) scene.getChildWithName("Map");
		}
	}
	
	// TODO make useless
	public AABB getBounds() {
		return new AABB(pos.x - size.x / 2, pos.y - size.y / 2, size.x, size.y);
	}
}
