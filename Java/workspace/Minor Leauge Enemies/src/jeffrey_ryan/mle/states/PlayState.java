package jeffrey_ryan.mle.states;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.event.KeyEvent;

import jeffrey_ryan.gamecore2d.input.KeyInputHandler;
import jeffrey_ryan.gamecore2d.node.GameScene;
import jeffrey_ryan.gamecore2d.physics.Collision;
import jeffrey_ryan.gamecore2d.physics.Vector2D;
import jeffrey_ryan.mle.map.GameMap;
import jeffrey_ryan.mle.player.Player;

public class PlayState extends GameScene {
	private GameMap map;
	private Player p1, p2;
	private KeyInputHandler keyHandler;
	
	public PlayState() {
		name = "Play State";
		keyHandler = new KeyInputHandler();
		
		String mapName = "Map";
		Vector2D mapSize = new Vector2D(20, 10);
		Vector2D camPos = new Vector2D();
		map = new GameMap(mapName, mapSize, camPos);
		map.zPos = -10;
		
		p1 = new Player("Player 1", Color.RED);
		p1.pos.x = 4;
		p1.pos.y = -map.getSize().y / 2 + p1.size.y;
		p1.zPos = 10;
		p1.pbody.mass = 80;
		
		p2 = new Player("Player 2", Color.BLUE);
		p2.pos.x = -4;
		p2.pos.y = -map.getSize().y / 2 + p2.size.y;
		p2.zPos = 10;
		p2.pbody.mass = 80;

		addChild(map);
		addChild(p1);
		addChild(p2);
	}
	
	@Override
	public void update(double seconds) {
		boolean onGround = p1.pos.y <= -map.getSize().y / 2 + p1.size.y / 2;
		if (keyHandler.getKey(KeyEvent.VK_UP) && onGround) {
			p1.pbody.applyImpluse(new Vector2D(0, 1000));
		}
		
		if (keyHandler.getKey(KeyEvent.VK_LEFT)) {
			p1.pbody.applyForce(new Vector2D(-p1.moveSpeed * 10, 0));
		}
		else if (keyHandler.getKey(KeyEvent.VK_RIGHT)){
			p1.pbody.applyForce(new Vector2D(p1.moveSpeed * 10, 0));
		}
		
		onGround = p2.pos.y <= -map.getSize().y / 2 + p2.size.y / 2;
		if (keyHandler.getKey(KeyEvent.VK_W) && onGround) {
			p2.pbody.applyImpluse(new Vector2D(0, 1000));
		}
		
		if (keyHandler.getKey(KeyEvent.VK_A)) {
			p2.pbody.applyForce(new Vector2D(-p2.moveSpeed * 10, 0));
		}
		else if (keyHandler.getKey(KeyEvent.VK_D)){
			p2.pbody.applyForce(new Vector2D(p2.moveSpeed * 10, 0));
		}
		
		if (p1.getBounds().intersects(p2.getBounds())) {
			Collision.resolveCollision(p1.pbody, p2.pbody, p1.getBounds(), p2.getBounds());
		}
		
		System.out.println(p1.pbody.vel.times(p2.pbody.vel));
		
		super.update(seconds);
	}
	
	@Override
	public void render(Graphics2D g, float interpolation) {
		g.setBackground(Color.CYAN);
		super.render(g, interpolation);
	}

	@Override
	public void enter() {
		gsm.getPanel().addKeyListener(keyHandler);
		
		double zoom = getCanvasSize().getWidth() / map.getSize().x;
		map.setUnitRatio(zoom);
	}
}
