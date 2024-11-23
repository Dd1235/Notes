import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

// size of thread pool is 1
// only one thread will be created and all tasks will be executed
// if a thread unexpectedly dies then a new thread will be created
// tasks ran sequentially

public class SingleExecutor {
    public static void main(String[] args) {
        ExecutorService service = Executors.newSingleThreadExecutor();
        try {
            for (int i = 0; i < 5; i++) {
                service.execute(new Task(i));
                // no need of calling .start() and all because executor service handles
            }
        } finally {
            service.shutdown();
        }
    }
}

class Task implements Runnable {
    private final int taskId;

    public Task(int taskId) {
        this.taskId = taskId;
    }

    @Override
    public void run() {
        System.out.println("Task ID: " + this.taskId + " performed by " + Thread.currentThread().getName());
        try {
            Thread.sleep(500);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

}