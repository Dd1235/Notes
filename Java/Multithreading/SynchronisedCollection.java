import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class SynchronisedCollection {
    public static void main(String[] args) {
        List<Integer> list = new ArrayList<>();
        List<Integer> syncList = Collections.synchronizedList(new ArrayList<>());

        Runnable r = () -> {
            for (int i = 0; i < 1000; i++) {
                list.add(i);
                syncList.add(i);
            }
        };

        Thread t1 = new Thread(r);
        Thread t2 = new Thread(r);

        t1.start();
        t2.start();

        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println(list.size());
        System.out.println(syncList.size());
    }
}