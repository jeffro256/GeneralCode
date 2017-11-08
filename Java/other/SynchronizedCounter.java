public class SynchronizedCounter {
    private int c = 0;

    public synchronized void increment() {
        c++;
        try {
            Thread.currentThread().sleep(1000);
        }
        catch (InterruptedException ie) {
            ie.printStackTrace();
            Thread.currentThread().interrupt();
        }
        System.out.println(c);
    }

    public synchronized void decrement() {
        c--;
    }

    public static void main(String[] args) {
        SynchronizedCounter s = new SynchronizedCounter();
        s.increment();
        s.decrement();
    }
}
