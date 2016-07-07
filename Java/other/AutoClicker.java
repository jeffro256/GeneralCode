import java.awt.*;
import java.awt.event.*;
import java.io.*;
import javax.imageio.*;
import javax.swing.*;

public class AutoClicker extends JFrame implements ActionListener {
    public Robot bot;
    
    private JButton toggleButton;
    private boolean shouldClick = false;

    public AutoClicker() {
        super("Auto Clicker");
        Dimension size = new Dimension(200, 200);
        setPreferredSize(size);
        setSize(size);
        
        try {
            bot = new Robot();
        }
        catch (AWTException e) {
            System.err.println(e.getMessage());
            e.printStackTrace();
            System.exit(1);
        }
        
        try {
            Image img = ImageIO.read(getClass().getResource("crosshair.png"));
            Image small_img = img.getScaledInstance(getWidth() * 3 / 4, getHeight() * 3 / 4, Image.SCALE_SMOOTH);
            ImageIcon icon = new ImageIcon(small_img);
            toggleButton = new JButton(icon);
            toggleButton.setBackground(Color.GREEN);
            toggleButton.setOpaque(true);
            toggleButton.setHorizontalAlignment(SwingConstants.CENTER);
            toggleButton.setVerticalAlignment(SwingConstants.CENTER);
            toggleButton.addActionListener(this);
            add(toggleButton);
        }
        catch (IOException e) {
            System.err.println(e.getMessage());
            e.printStackTrace();
            System.exit(1);
        }
    }
    
    public void click() {
        if (!shouldClick) return;
        
        //Point old = MouseInfo.getPointerInfo().getLocation();
        int x = getLocationOnScreen().x + getWidth() / 2;
        int y = getLocationOnScreen().y + getHeight() / 2;
        bot.mouseMove(x, y);    
        bot.mousePress(InputEvent.BUTTON1_MASK);
        bot.mouseRelease(InputEvent.BUTTON1_MASK);
        //bot.mouseMove(old.x, old.y);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        shouldClick = !shouldClick;
        
        if (shouldClick) {
            toggleButton.setBackground(Color.RED);
            toBack();
        }
        else {
            toggleButton.setBackground(Color.GREEN);
        }
    }

    public static void main(String[] args) {    
        AutoClicker ac = new AutoClicker();
        
        ac.pack();
        ac.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        ac.setResizable(false);
        ac.setVisible(true);
        
        while (true) {
            ac.click();
            ac.bot.delay(50);
        }
    }
}