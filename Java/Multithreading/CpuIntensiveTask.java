import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class CpuIntensiveTask {

    public static void main(String[] args) {
        int cores = Runtime.getRuntime().availableProcessors();
        ExecutorService service = Executors.newFixedThreadPool(cores);
        System.out.println("Created thread pool with: " + cores + " cores");

        try {
            for (int i = 1; i < 30; i++) {
                service.execute(new CPUTask(i));
            }
        } finally {
            service.shutdown();
        }
    }

}

class CPUTask implements Runnable {

    private final int taskId;

    public CPUTask(int taskId) {
        this.taskId = taskId;
    }

    @Override
    public void run() throws RuntimeException {
        System.out.println("Task ID: " + this.taskId + " performed by " + Thread.currentThread().getName());
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        System.out.println("Task ID: " + this.taskId + " done");
    }

}
