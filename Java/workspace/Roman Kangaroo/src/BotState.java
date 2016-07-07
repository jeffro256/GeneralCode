import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Robot;
import java.awt.event.KeyEvent;

import jeffrey_ryan.game2d.gamestate.GameState;

public class BotState extends GameState {
	private Robot robot;
	private boolean creatingTab = true;
	private final double timeBetweenTabs = 1.5;
	private double timeSinceTab = 0;
	private int maxTabsPerDay = 500 * 5 / 4;
	private int tabsOpened = 0;
	
	public BotState() {
		try {
			Runtime.getRuntime().exec("Resources/chrome");
			robot = new Robot();
			doRobotStuff();
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	private void doRobotStuff() {
		if (tabsOpened < maxTabsPerDay) {
			if (creatingTab) {
				if (tabsOpened % 5 == 0) {
					// refresh
					robot.keyPress(KeyEvent.VK_META);
					robot.keyPress(KeyEvent.VK_R);
					robot.keyRelease(KeyEvent.VK_R);
					robot.keyRelease(KeyEvent.VK_META);
				}
				
				// open tab
				robot.keyPress(KeyEvent.VK_META);
				robot.keyPress(KeyEvent.VK_T);
				robot.keyRelease(KeyEvent.VK_T);
				robot.keyRelease(KeyEvent.VK_META);
			}
			else {
				// close tab
				robot.keyPress(KeyEvent.VK_META);
				robot.keyPress(KeyEvent.VK_W);
				robot.keyRelease(KeyEvent.VK_W);
				robot.keyRelease(KeyEvent.VK_META);
			}
			
			tabsOpened++;
		}
		else {
			System.exit(0);
		}
	}
	
	@Override
	public void update(double seconds) {
		timeSinceTab += seconds;
		
		if (timeSinceTab >= timeBetweenTabs) {
			doRobotStuff();
			creatingTab = !creatingTab;
			
			timeSinceTab -= timeBetweenTabs;
		}
	}
	
	@Override
	public void render(Graphics2D g, double interpolation) {
		super.render(g, interpolation);
		
		g.setColor(Color.GREEN);
		g.fillRect(50, 50, 50, 50);
	}
}
