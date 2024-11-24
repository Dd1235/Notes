import java.util.concurrent.CountDownLatch;

public class CountdownLatchDemo {

    public static void main(String[] args) throws InterruptedException {
        int numOfChefs = 3;
        CountDownLatch latch = new CountDownLatch(numOfChefs);

        new Thread(new Chef("A", "Pizza", latch)).start();
        new Thread(new Chef("B", "Pasta", latch)).start();
        new Thread(new Chef("C", "Salad", latch)).start();

        latch.await(); // wait for all the dishes to be ready
        System.out.println("All the dishes are ready to serve");
    }

}

class Chef implements Runnable {
    private final String name;
    private final String dish;
    private final CountDownLatch latch;

    public Chef(String name, String dish, CountDownLatch latch) {
        this.name = name;
        this.dish = dish;
        this.latch = latch;
    }

    @Override
    public void run() {
        try {
            System.out.println("Chef " + name + " is preparing " + dish);
            Thread.sleep(2000);
            System.out.println(dish + " is prepared by Chef " + name);
            latch.countDown();
        } catch (InterruptedException e) {
            throw new RuntimeException(null, e);
        }
    }
}