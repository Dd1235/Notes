public class WaitNotify {

    private static final Object LOCK = new Object();

    public static void main(String[] args) {

        Thread one = new Thread(() -> {
            try {
                one();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        });

        Thread two = new Thread(() -> {
            try {
                two();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        });

        one.start();
        two.start();

    }

    // wait() and notify() should be called from synchronized block
    // wait() releases the lock and goes to waiting state
    // notify() wakes up one of the waiting threads
    // notifyAll() wakes up all the waiting threads
    // wait() is used for inter thread communication
    private static void one() throws InterruptedException {
        synchronized (LOCK) {
            System.out.println("Hello from method one...");
            LOCK.wait();
            System.out.println("Back Again in the method one");
        }
    }

    private static void two() throws InterruptedException {
        synchronized (LOCK) {
            System.out.println("Hello from method two...");
            LOCK.notify(); // Remaining code lines in the block are executed
            System.out.println("Hello from method two even after notify...");
        }
    }

}
