package baron_arena.states;

import java.awt.Graphics2D;
import java.awt.event.KeyEvent;
import java.awt.geom.Point2D;
import java.awt.geom.Point2D.Double;
import java.awt.geom.Rectangle2D;

import javax.imageio.ImageIO;

import baron_arena.entity.Player;
import baron_arena.geom.DoubleDimension;
import baron_arena.tile.TileMap;
import jeffrey_ryan.game2d.gamestate.GameState;
import jeffrey_ryan.game2d.input.KeyInputHandler;

public class MapState extends GameState {
	private TileMap map;
	private KeyInputHandler handler;
	private Player p1;
	private Player p2;
	
	private double x;
	private double y;
	private double newX;
	private double newY;
	private double scale;
	private double newScale;
	
	public MapState() {
		try {
			map = new TileMap("/Maps/test_map2");
			handler = new KeyInputHandler();
			p1 = new Player(10, 10, ImageIO.read(getClass().getResourceAsStream("/Images/player.png")));
			p2 = new Player(18, 15, ImageIO.read(getClass().getResourceAsStream("/Images/player2.png")));
			Point2D centerPoint = getCenterPoint();
			newX = x = centerPoint.getX();
			newY = y = centerPoint.getY();
			//DoubleDimension screenSize = getScreenSize();
			//newScale = scale = 640.0 / (screenSize.width * map.getTileSize().getWidth());
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	private Point2D getCenterPoint() {
		return new Point2D.Double((p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0);
	}
	
	public DoubleDimension getScreenSize() {
		double xPadding = 1.5;
		double yPadding = 1.5;
		
		Rectangle2D.Double rect = new Rectangle2D.Double();
		Rectangle2D.union(p1.getBounds2D(), p2.getBounds2D(), rect);
		
		rect.width += xPadding;
		rect.height += yPadding;
		
		double aspRat = aspectRatio();
		if (rect.width / aspRat >= rect.height) {
			rect.height = rect.width / aspRat;
		}
		else {
			rect.width = rect.height * aspRat;
		}
		
		return new DoubleDimension(rect.width, rect.height);
	}
	
	private double aspectRatio() {
		return canvasSize.getWidth() / canvasSize.getHeight();
	}
	
	public void drawPlayer(Player p, double viewX, double viewY, double scale, Graphics2D g) {
		int x = (int) ((p.x - viewX) * map.getTileSize().getWidth() * scale);
		int y = (int) ((p.y - viewY) * map.getTileSize().getHeight() * scale);
		int width = (int) (p.width * map.getTileSize().getWidth() * scale);
		int height = (int) (p.height * map.getTileSize().getHeight() * scale);
		
		g.drawImage(p.image, x, y, width, height, null);
	}
	
	@Override
	public void update(double seconds) {
		double moveSpeed = 1.0 / 16.0;

		if (handler.getKey(KeyEvent.VK_W)) {
			p1.y -= moveSpeed;
		}
		
		if (handler.getKey(KeyEvent.VK_S)) {
			p1.y += moveSpeed;
		}
		
		if (handler.getKey(KeyEvent.VK_A)) {
			p1.x -= moveSpeed;
		}

		if (handler.getKey(KeyEvent.VK_D)) {
			p1.x += moveSpeed;
		}
		
		
		if (handler.getKey(KeyEvent.VK_UP)) {
			p2.y -= moveSpeed;
		}
		
		if (handler.getKey(KeyEvent.VK_DOWN)) {
			p2.y += moveSpeed;
		}
		
		if (handler.getKey(KeyEvent.VK_LEFT)) {
			p2.x -= moveSpeed;
		}

		if (handler.getKey(KeyEvent.VK_RIGHT)) {
			p2.x += moveSpeed;
		}
	}
	
	@Override
	public void render(Graphics2D g, double interpolation) {
		super.render(g, interpolation);
		
		Point2D.Double center = (Point2D.Double) getCenterPoint();
		DoubleDimension size = getScreenSize();
		
		double viewX = center.x - size.width / 2.0;
		double viewY = center.y - size.height / 2.0;
		double scale = canvasSize.getWidth() / size.width / map.getMapSize().getWidth();
		System.out.println(scale);
		
		map.render(g, viewX, viewY, scale, canvasSize);
		
		drawPlayer(p1, viewX, viewY, scale, g);
		drawPlayer(p2, viewX, viewY, scale, g);
	}
	
	@Override
	public void keyPressed(KeyEvent e) {
		handler.keyPressed(e);
	}
	
	@Override
	public void keyReleased(KeyEvent e) {
		handler.keyReleased(e);
	}
}
