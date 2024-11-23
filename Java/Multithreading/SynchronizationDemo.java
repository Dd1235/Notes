public class SynchronizationDemo {

    private static int counter = 0;

    // race condition
    // multiple threads trying to access the same resource

    public static void main(String[] args) {
        Thread one = new Thread(() -> {
            for (int i = 0; i < 1000; i++) {
                increment();
            }
        });

        Thread two = new Thread(() -> {
            for (int i = 0; i < 1000; i++) {
                increment();
            }
        });

        one.start();
        two.start();

        try {
            one.join();
            two.join();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        System.out.println("Counter is : " + counter);
    }

    // critical section
    // limit usage to one thread at a time
    // otherwise say both threads see that it is 0 and set it to 1, so essentially
    // instead of becoming two it becomes 1

    // monitor lock / intrinsic lock
    // when thread exists the synchronized block, it releases the lock
    // lock is class level
    private synchronized static void increment() {
        counter++;
    }
}