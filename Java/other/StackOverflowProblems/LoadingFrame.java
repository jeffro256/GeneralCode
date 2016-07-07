import java.awt.*;
import java.io.*;

import javax.swing.*;
import javax.imageio.*;

public class LoadingFrame
{
    private  JFrame frame;

    public LoadingFrame()
    {
        frame = new JFrame("Loading...");
        frame.setPreferredSize(new Dimension(800, 600));
        frame.setSize(frame.getPreferredSize());
        frame.setLocationRelativeTo(null);               
        frame.setUndecorated(true);

        frame.setContentPane(new Panneau());
        frame.pack();
    }
    public void start()
    {
        frame.setVisible(true);
    }

    public void stop()
    {
        frame.setVisible(false);
    }

    public static void main(String[] args)
    {
        LoadingFrame l = new LoadingFrame();
        l.start();
        try
        {
            Thread.sleep(3000);
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }

        l.stop();
    }
}

class Panneau extends JPanel
{
    Image img;

    public Panneau() {
        System.out.println("init");

        try
        {
          img = ImageIO.read(new File("loading.png"));
        }
        catch (IOException e)
        {
          e.printStackTrace();
        }
    }

    @Override
    public void paintComponent(Graphics g)
    {
        super.paintComponent(g);

        System.out.println("hi!");

        g.drawImage(img, 0, 0, getWidth(), getHeight(), this);
    }
}
