public class JoinThreadExample {
    public static void main(String[] args) throws InterruptedException {
        Thread one = new Thread(() -> {
            for (int i = 0; i < 25; i++) {
                System.out.println("Thread 1 : " + i);
            }
        });

        Thread two = new Thread(() -> {
            for (int i = 0; i < 25; i++) {
                System.out.println("Thread 2 : " + i);
            }
        });

        System.out.println("Before invoking threads...");
        System.out.println(Thread.currentThread().getName());
        System.out.println(Thread.activeCount());
        one.start();
        two.start();

        one.join(); // -> This will make the main thread wait until the thread one is done executing

        two.join(); // -> This will make the main thread wait until the thread two is done executing

        System.out.println("Done executing the threads!");
        // -> Without hte join the main thread is of highest priority, gets access to
        // the CPU and prints this line before the threads are done executing
    }
}