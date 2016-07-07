import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

public class MacKeyboardTest {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Mac Keyboard Test");
        JPanel panel = new JPanel();

        panel.setFocusable(true);
        panel.setPreferredSize(new Dimension(300, 300));

        frame.setContentPane(panel);
        frame.pack();

        panel.addKeyListener(new KeyAdapter() {
            private int pnum = 0;
            private int rnum = 0;

            @Override
            public void keyPressed(KeyEvent e) {
                pnum++;
                System.out.println("Press #" + pnum + " { code: " + e.getKeyCode() + ", char: " + e.getKeyChar() + ", modifiers: " + e.getModifiers() + " }");

                Graphics g = panel.getGraphics();
                g.setColor(new Color(e.getKeyCode() * 30));
                g.fillRect(0, 0, 300, 300);
            }

            @Override
            public void keyReleased(KeyEvent e) {
                rnum++;
                System.out.println("Release #" + rnum + " { code: " + e.getKeyCode() + ", char: " + e.getKeyChar() + ", modifiers: " + e.getModifiers() + " }");
            }
        });

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setResizable(false);
        frame.setVisible(true);
    }
}
