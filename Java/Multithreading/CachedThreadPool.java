import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

// no fixed number of threads
// queue: synchronous queue
// only single task in the queue at a time
// after some time, if threads are done completing their task, they are available for 60s to pick another task
// auto scaling based on the number of tasks

public class CachedThreadPool {

    public static void main(String[] args) {

        ExecutorService service = Executors.newCachedThreadPool();
        try {
            for (int i = 0; i < 1000; i++) {
                service.execute(new TaskOne(i));
            }
        } finally {
            service.shutdown();
        }

    }
}

class TaskOne implements Runnable {

    private final int taskId;

    public TaskOne(int taskId) {
        this.taskId = taskId;
    }

    @Override
    public void run() {
        System.out.println("Task: " + taskId + " being executed by " + Thread.currentThread().getName());
        try {
            Thread.sleep(500);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}