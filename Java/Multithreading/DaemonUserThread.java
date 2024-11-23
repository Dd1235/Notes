public class DaemonUserThread {

    public static void main(String[] args) {
        Thread bgThread = new Thread(new DaemonHelper());
        Thread userThread = new Thread(new UserThreadHelper());
        System.out.println(Thread.currentThread().getName());
        bgThread.setDaemon(true);
        bgThread.start();
        userThread.start();
        for (int i = 0; i < 10; i++) {
            System.out.println("Main Thread: " + i);
        }
        System.out.println(Thread.currentThread().getName());
    }

}

class DaemonHelper implements Runnable {
    @Override
    public void run() {
        int count = 0;
        while (count < 500) {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            count++;
            System.out.println("Daemon Thread: " + count);
        }
    }
}

class UserThreadHelper implements Runnable {
    @Override
    public void run() {
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        System.out.println("User Thread Helper done with execution!");
    }
}