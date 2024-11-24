import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

public class BlockingQ {
    // blockingdeque and transferqueue
    // put take offer poll peek

    static final int QUEUE_CAPACITY = 19;
    static BlockingQueue<Integer> taskQueue = new ArrayBlockingQueue<>(QUEUE_CAPACITY);

    public static void main(String[] args) {

        Thread producer = new Thread(() -> {
            try {
                for (int i = 1; i <= 20; i++) {
                    System.out.println("Producing: " + i);
                    taskQueue.put(i);
                    Thread.sleep(50);
                }

            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        });

        Thread consumer1 = new Thread(() -> {
            try {
                while (true) {
                    int task = taskQueue.take();
                    processTask(task, "ConsumerOne");
                }

            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        });

        Thread consumer2 = new Thread(() -> {
            try {
                while (true) {
                    int task = taskQueue.take();
                    processTask(task, "ConsumerTwo");
                }

            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        });

        producer.start();
        consumer1.start();
        consumer2.start();
    }

    private static void processTask(int task, String consumerName) throws InterruptedException {
        System.out.println("Consuming: " + task + " by " + consumerName);
        Thread.sleep(1000);
        System.out.println("Consumed: " + task + " by " + consumerName);
    }

}
