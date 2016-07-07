package baron_arena.tile;

import java.awt.Dimension;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import javax.imageio.ImageIO;

import baron_arena.misc.InfoFileParser;

public class TileMap {
	private int[][] map;
	private Dimension mapSize;
	private Tile[] tiles;
	private Dimension tileSize;
	private int numTiles;
	
	public TileMap(String mapPath) throws IOException {
		mapPath = mapPath.replace("/$", "") + "/";
		InfoFileParser parser = new InfoFileParser(mapPath + "index.info");
		
		String[] mapSizeParts = parser.get("map-size").split("x");
		mapSize = new Dimension(Integer.parseInt(mapSizeParts[0].trim()), Integer.parseInt(mapSizeParts[1].trim()));
		
		map = getMapArray(new BufferedReader(new InputStreamReader(getClass().getResourceAsStream(mapPath + parser.get("map-file")))), mapSize);
		
		String[] tileSizeParts = parser.get("tile-res").split("x");
		tileSize = new Dimension(Integer.parseInt(tileSizeParts[0].trim()), Integer.parseInt(tileSizeParts[1].trim()));
		
		numTiles = Integer.parseInt(parser.get("max-tile-id"));
		
		String tilesetPath = mapPath + parser.get("tileset-file");
		BufferedImage[] tileImages = getTilesetArray(ImageIO.read(getClass().getResourceAsStream(tilesetPath)), tileSize, numTiles);
		
		tiles = getTiles(tileImages, numTiles);
	}
	
	public Dimension getMapSize() {
		return mapSize;
	}
	
	public Dimension getTileSize() {
		return tileSize;
	}
	
	public void render(Graphics2D g, double x1, double y1, double x2, double y2, double scale, Dimension canvasSize, double interpolation) {
		int tileWidth = (int) (tileSize.width * scale);
		int tileHeight = (int) (tileSize.height * scale);
		int colsToDraw = Math.min(canvasSize.width / tileWidth + 2, mapSize.width);
		int rowsToDraw = Math.min(canvasSize.height / tileWidth + 2, mapSize.height);
		int pixelX = (int) (tileWidth * ((x2 - x1) * interpolation + x1));
		int pixelY = (int) (tileHeight * ((y2 - y1) * interpolation + y1));
		int colOffset = pixelX / tileWidth;
		int rowOffset = pixelY / tileHeight;
		int startXTile = Math.max(-colOffset, 0);
		int startYTile = Math.max(-rowOffset, 0);
		
		for (int col = startXTile; col < startXTile + colsToDraw; col++) {
			int mapCol = col + colOffset;
			
			if (mapCol >= mapSize.width) break;
			
			for (int row = startYTile; row < startYTile + rowsToDraw; row++) {
				int mapRow = row + rowOffset;
				
				if (mapRow >= mapSize.height) break;
				
				int tileID = map[mapCol][mapRow] - 1;
				
				if (tileID < 0) continue;
				
				Tile tile = tiles[tileID];
				g.drawImage(tile.image, col * tileWidth - pixelX % tileWidth, row * tileHeight - pixelY % tileHeight, tileWidth, tileHeight, null);
			}
		}
	}
	
	public void render(Graphics2D g, double x, double y, double scale, Dimension canvasSize) {
		render(g, x, y, x, y, scale, canvasSize, 0);
	}
	
	private static int[][] getMapArray(BufferedReader mapReader, Dimension mapSize) throws IOException {
		int[][] map = new int[mapSize.width][mapSize.height];
		
		for (int row = 0; row < mapSize.height; row++) {
			String[] tokens = mapReader.readLine().trim().split(" ");
			
			for (int col = 0; col < mapSize.width; col++) {
				map[col][row] = Integer.parseInt(tokens[col]);
			}
		}
		
		return map;
	}
	
	private static BufferedImage[] getTilesetArray(BufferedImage tileset, Dimension tileSize, int numTiles) {
		BufferedImage[] tiles = new BufferedImage[numTiles];
		
		for (int i = 0; i < numTiles; i++) {
			BufferedImage subimage = tileset.getSubimage(i * tileSize.width % tileset.getWidth(), i * tileSize.width / tileset.getWidth(), tileSize.width, tileSize.height);
			tiles[i] = subimage;
		}
		
		return tiles;
	}
	
	private static Tile[] getTiles(BufferedImage[] tileImages, int numTiles) {
		Tile[] tiles = new Tile[numTiles];
		
		for (int i = 0; i < numTiles; i++) {
			tiles[i] = new Tile(tileImages[i]);
		}
		
		return tiles;
	}
}
