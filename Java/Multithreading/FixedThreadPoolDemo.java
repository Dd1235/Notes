import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class FixedThreadPoolDemo {

    public static void main(String[] args) {

        // if size of thread pool is 1 you can see that each task takes 0.5 seconds, it
        // takes 2.5 seconds to complete all tasks, when size of 5, it takes 0.5 seconds
        // to complete all, and when you have 4, it takes 1 second to complete all

        ExecutorService service = Executors.newFixedThreadPool(4);
        try {
            for (int i = 0; i < 5; i++) {
                service.execute(new Work(i));
            }
        } finally {
            service.shutdown();
        }
    }

}

class Work implements Runnable {

    private final int workId;

    public Work(int workId) {
        this.workId = workId;
    }

    @Override
    public void run() {
        System.out.println("Work ID: " + this.workId + " performed by " + Thread.currentThread().getName());
        try {
            Thread.sleep(500);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}
