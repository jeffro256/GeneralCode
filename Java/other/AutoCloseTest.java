public class AutoCloseTest implements AutoCloseable {
    public static void testMethod() {
        try (AutoCloseTest a = new AutoCloseTest()) {
            System.out.println("doing body stuff");
        }
        catch (Exception e) {
            System.out.println("got an error");
        }
    }

    @Override
    public void close() {
        System.out.println("Closing...");
    }
 
    public static void main(String[] args) {
        testMethod();
    }
}