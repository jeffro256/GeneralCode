import java.awt.*;
import java.awt.geom.*;
import java.awt.image.*;
import java.io.*;
import java.util.*;

import javax.swing.*;
import javax.imageio.*;

public class FractalTest2 extends JPanel {
    private static int WIDTH = 2560;
    private static int HEIGHT = 1600;
    private static int WIN_SCALE_NUM = 1;
    private static int WIN_SCALE_DENOM = 4;
    private static int WIN_WIDTH = WIDTH * WIN_SCALE_NUM / WIN_SCALE_DENOM;
    private static int WIN_HEIGHT = HEIGHT * WIN_SCALE_NUM / WIN_SCALE_DENOM;
    private static int IMG_SCALE = 3;
    private static int IMG_WIDTH = WIDTH * IMG_SCALE;
    private static int IMG_HEIGHT = HEIGHT * IMG_SCALE;
    
    private FractalFormula formula;
    private BufferedImage canvas = new BufferedImage(IMG_WIDTH, IMG_HEIGHT, BufferedImage.TYPE_INT_RGB);
    private double centerCx = 0;
    private double centerCy = 0;
    private double pixelSize = WIDTH / 3;
    
    private boolean done = false;
    
    public FractalTest2() {
        super();
        
        new Thread(new Runnable() {
            @Override
            public void run() {
                int frames = 300;
                double x1 = -0.368, x2 = -0.551, y1 = 0.652, y2 = 0.470;
                double dx = (x2 - x1) / frames, dy = (y2 - y1) / frames;
                
                // frames -200 to 500 is classic
                for (int i = 500; i < 600; i++) {
                    formula = new Julia(x1 + dx * i, y1 + dy * i);

                    long oldTime = System.nanoTime();
                    render();
                    long newTime = System.nanoTime();
                    long elapsed = (newTime - oldTime) / 1_000_000;
                    System.out.println("Rendering frame " + i + " took " + elapsed + " milliseconds.");
                    
                    try {
                        ImageIO.write(canvas, "png", new File("Julia Animation 2/frame" + String.format("%03d", i + 201) + ".png"));
                    }
                    catch (IOException ioe) {
                        ioe.printStackTrace();
                    }
                    
                    canvas.createGraphics().clearRect(0, 0, IMG_WIDTH, IMG_HEIGHT);
                }
                
                done = true;
            }
        }).start();
        
        Thread painterThread = new Thread(new Runnable() {
            @Override
            public void run() {
                while (!done) {
                    repaint();
            
                    try {
                        Thread.sleep(1000);
                    }
                    catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });
        
        painterThread.setDaemon(true);
        painterThread.start();
    }
    
    public void render() {
        Point2D Cmin = new Point2D.Double(centerCx - (double) WIDTH / 2.0 / pixelSize, 
                                          centerCy - (double) HEIGHT / 2.0 / pixelSize);
        Point2D Cmax = new Point2D.Double(centerCx + (double) WIDTH / 2.0 / pixelSize,
                                          centerCy + (double) HEIGHT / 2.0 / pixelSize);
        
        FractalRenderer.linearRender(canvas, Cmin, Cmax, formula);
        repaint();
    }
    
    @Override
    public Dimension getPreferredSize() {
        return new Dimension(WIN_WIDTH, WIN_HEIGHT);
    }
    
    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        
        if (g != null) {
            g.drawImage(canvas, 0, 0, WIN_WIDTH, WIN_HEIGHT, null);
        }
    }
    
    public static void main(String[] args) {
        JFrame frame = new JFrame("Fractal Test");
        JPanel panel = new FractalTest2();
        
        frame.setContentPane(panel);
        frame.pack();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setResizable(false);
        frame.setVisible(true);
    }
}

class FractalRenderer {
    public static void linearRender(BufferedImage dest, Point2D Cmin, Point2D Cmax, 
                                    FractalFormula form) {
        double fstepx = (Cmax.getX() - Cmin.getX()) / dest.getWidth();
        double fstepy = (Cmax.getY() - Cmin.getY()) / dest.getHeight();
        
        long lastProgessTime = 0;
        
        for (int i = 0; i < dest.getWidth(); i++) {
            for (int j = 0; j < dest.getHeight(); j++) {
                double Cx = Cmin.getX() + fstepx * i;
                double Cy = Cmax.getY() - fstepy * j;

                int fColor = form.colorAt(Cx, Cy);
                dest.setRGB(i, j, fColor);
                
                long newTime = System.currentTimeMillis();
                long elapsed = newTime - lastProgessTime;
                
                if (elapsed > 500) {
                    float progess = (float) (i * dest.getHeight() + j) / 
                                    (float) (dest.getWidth() * dest.getHeight()) * 
                                    100.0f;
                    System.out.print(String.format("%2.1f", progess) + "%\r");
                    lastProgessTime = newTime;
                }
            }
        }
        
        System.out.print("100.0%\r");
    }
}

class Julia extends FractalFormula {
    private double Cx;
    private double Cy;
    
    private PrintWriter out;
    
    public Julia(double Cx, double Cy, long maxIters, double bailout) {
        super(maxIters, bailout);
    
        this.Cx = Cx;
        this.Cy = Cy;
        
        try {
            out = new PrintWriter("julia_log.txt", "UTF-8");
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public Julia(double Cx, double Cy) {
        this(Cx, Cy, 10000000, 4000000);
    }
    
    @Override
    public Point2D getInitialZ(double x, double y) {
        return new Point2D.Double(x, y);
    }
    
    @Override
    public Point2D calculateZ(double Zx, double Zy, double x, double y) {
        double Zx2 = Zx * Zx - Zy * Zy + Cx;
        double Zy2 = 2.0 * Zx * Zy + Cy;
        
        return new Point2D.Double(Zx2, Zy2);
    }

    @Override
    public int getOutsideColor(long escapeTime) {
        int color = (int) (escapeTime * 0xFFL);
        out.println(escapeTime + " -> " + color);
        return color;
    }
}

class Mandelbrot extends FractalFormula {
    public Mandelbrot(long maxIters, double bailout) {
        super(maxIters, bailout);
    }
    
    public Mandelbrot() {
        super(10000000, 4000000);
    }

    @Override
    public Point2D getInitialZ(double x, double y) {
        return new Point2D.Double();
    }
    
    @Override
    public Point2D calculateZ(double Zx, double Zy, double Cx, double Cy) {
        double Zx2 = Zx * Zx - Zy * Zy + Cx;
        double Zy2 = 2.0 * Zx * Zy + Cy;

        return new Point2D.Double(Zx2, Zy2);
    }

    @Override
    public int getOutsideColor(long escapeTime) {
        return new Random(escapeTime).nextInt();
    }
}

abstract class FractalFormula {
    public abstract Point2D getInitialZ(double x, double y);
    public abstract Point2D calculateZ(double Zx, double Zy, double x, double y);
    public abstract int getOutsideColor(long escapeTime);

    long maxIters;
    double bailout;

    public FractalFormula(long maxIters, double bailout) {
        this.maxIters = maxIters;
        this.bailout = bailout;
    }

    public int colorAt(double x, double y) {
        Point2D initZ = getInitialZ(x, y);
        double Zx = initZ.getX();
        double Zy = initZ.getY();
        double pZx = Zx;
        double pZy = Zy;
        
        long iters;
        for (iters = 0; iters < maxIters && !shouldBail(Zx, Zy); iters++) {
            Point2D Z = calculateZ(Zx, Zy, x, y);
            Zx = Z.getX();
            Zy = Z.getY();

            if (pZx == Zx && pZy == Zy) {
                iters = maxIters;
            }
            else if (isPowerOf2(iters)) {
                pZx = Zx;
                pZy = Zy;
            }
        }
        
        if (iters >= maxIters) return 0;
        else return getOutsideColor(iters);
    }
    
    public boolean shouldBail(double Zx, double Zy) {
        return Zx * Zx + Zy * Zy > bailout * bailout;
    }
    
    private static boolean isPowerOf2(long num) {
        return (num & (num - 1)) == 0 && num > 1;
    }
}

class JeffsFractal extends FractalFormula {
    public JeffsFractal(long maxIters, double bailout) {
        super(maxIters, bailout);
    }

    @Override
    public Point2D getInitialZ(double x, double y) {
        return new Point2D.Double();
    }
    
    @Override
    public Point2D calculateZ(double Zx, double Zy, double Cx, double Cy) {
        double Zx2 = Zx * Zx * Zx - 3.0 * Zx * Zy * Zy + Cx;
        double Zy2 = 3.0 * Zx * Zx * Zy - Zy * Zy * Zy + Cy;
        
        return new Point2D.Double(Zx2, Zy2);
    }
    
    @Override
    public int getOutsideColor(long escapeTime) {
        return new Random(escapeTime).nextInt();
    }
}
