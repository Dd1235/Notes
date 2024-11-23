import java.util.ArrayList;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class CallableDemo {

    public static void main(String[] args) {
        ExecutorService service = Executors.newFixedThreadPool(2);
        try {
            // ReturnValueTask task = new ReturnValueTask();
            // Future: generics based class

            ArrayList<ReturnValueTask> tasks = new ArrayList<>();
            for (int i = 0; i < 3; i++) {
                tasks.add(new ReturnValueTask());
            }
            // Future<Integer> res = service.submit(task);
            ArrayList<Future<Integer>> results = new ArrayList<>();
            for (ReturnValueTask t : tasks) {
                results.add(service.submit(t));
            }
            for (Future<Integer> res : results) {
                System.out.println("Current results: " + results);
                System.out.println("Task result: " + res.get());
            }
            // Boolean isCancelled() and isDone();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            service.shutdown();
        }
    }

}

// callable is a generics based class
class ReturnValueTask implements Callable<Integer> {
    @Override
    public Integer call() throws Exception {
        System.out.println("Task being executed by " + Thread.currentThread().getName());
        Thread.sleep(5000);
        return 42;
    }
}