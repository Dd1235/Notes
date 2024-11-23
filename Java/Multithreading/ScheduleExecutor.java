import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

// all tasks submitted to queue
// pq based on time

public class ScheduleExecutor {

    public static void main(String[] args) {
        ScheduledExecutorService service = Executors.newScheduledThreadPool(1);
        service.scheduleAtFixedRate(new ProbeTask(), 1000, 2000, TimeUnit.MILLISECONDS);

        try {
            if (!service.awaitTermination(10000, TimeUnit.MILLISECONDS)) {
                service.shutdownNow();
            }
        } catch (InterruptedException e) {
            service.shutdownNow();
        }
    }

}

class ProbeTask implements Runnable {
    @Override
    public void run() {
        System.out.println("Probing for updates");
    }
}
