import java.awt.*;

import javax.swing.*;

public class App {
//Attributes used to display the application
    private JFrame frame;

//Attribute which display a waiting frame
    private static LoadingFrame loadingFrame;

/**
     * Launch the application.
     */
    public static void main(String[] args) {
        try {
        SwingUtilities.invokeAndWait(new Runnable() {
            public void run() {
                try {
                    loadingFrame = new LoadingFrame();
                    loadingFrame.start();

                    System.out.println("i got this far");

                    Thread.sleep(3000);

                    //App window = new App();

                    loadingFrame.stop();

                    //window.frame.setVisible(true);
                } 
                catch (Exception e) 
                {
                    e.printStackTrace();
                }
            }
        });
        }
        catch (Exception e) {
        e.printStackTrace();
        }
    }

/**
     * Create the application.
     */
    public App() 
    {
        initialize();
        synchronizeScriptReferenceList();
        synchronizeTests();
    }

    // blah blah blah

    private void initialize() { try { Thread.currentThread().sleep(1000); } catch (Exception e) { e.printStackTrace(); } }
    private void synchronizeScriptReferenceList() {}
    private void synchronizeTests() {}
}
