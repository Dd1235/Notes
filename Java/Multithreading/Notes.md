# Multithreading in Java

## Daemon vs User Threads

- Daemon threads are low priority threads that run in the background and do not prevent the JVM from exiting when all the user threads finish their execution
- Daemon threads are used for tasks that need to run in the background without affecting the termination of the program

## Monitor Lock and Synchronization

- Every object in Java has an intrinsic lock associated with it
- Synchronization in Java is implemented using the concept of monitor lock
- Con: say you have two synchronized methods in a class
    - If one thread is executing one synchronized method, the other thread cannot execute the other synchronized method of the same class
    - This is because both methods are synchronized on the same object lock
    - To avoid this, you can use synchronized block with different locks

## locks

- The synchronized(lock) statement ensures that the block of code within it is executed by only one thread at a time for the given lock object.
-  In other words, it allows threads to coordinate and ensures mutual exclusion.
- The lock object is used as a monitor or mutex (mutual exclusion object). Only one thread can hold the intrinsic lock of the lock object at any time.
- If another thread tries to execute a block synchronized on the same lock object while the first thread is inside it, it will be blocked (wait) until the lock is released.

## Wait Notify

 ### wait():

- When a thread calls lock.wait(), it temporarily releases the lock on the lock object and goes into the waiting state.
It will stay in the waiting state until another thread calls lock.notify() (or lock.notifyAll()), signaling that the waiting thread should wake up and attempt to reacquire the lock.
### notify():
- The notify() method wakes up a single thread waiting on the monitor (lock). If multiple threads are waiting, one is chosen at random.
- It does not release the lock immediately; the thread that calls notify() must finish executing the synchronized block before the lock is released.

## Executor Service

- ExecutorService is a higher-level replacement for working with threads directly.
- In JAVA every thread is a OS level thread, so creating a thread is a costly operation.
- ExecutorService allows you to create a pool of threads that can be reused, so you don't have to create a new thread every time you need to perform a task.
- 4 types: 
    - SingleThreadExecutor
    - FixedThreadPoolExecutor
    - CachedThreadPool
    - ScheduledExecutor

## Ideal thread pool size

- say 4 cores, creating 100s of threads wont help if cpu intensive tasks
- lots of threads contensting for CPU time will slow down the system
- #threads = #cores but wont ensure all cores will be running your threads, some would be used for OS level tasks

- When you have 8 cores but 1000 threads, it involves a process called thread scheduling.

- Physical Cores: You have 8 cores, meaning 8 threads can execute simultaneously (assuming no hyper-threading).
1000 Threads: Far more threads than cores, so the CPU uses time-slicing to share the cores among threads.
Context Switching: The operating system switches between threads, giving each one a slice of CPU time.

- Threads waiting for I/O (e.g., file reads, network requests) do not consume CPU time, allowing other threads to use the CPU while they wait.

## **Callable and Future in Java - Key Points**

1. **Callable**:
   - A functional interface in `java.util.concurrent` used to define tasks that return a result and can throw checked exceptions.
   - The `call()` method is invoked when the task is executed, and it returns a value of a specified type (`V`).
   - Similar to `Runnable` but with the ability to return results and handle exceptions.

   **Example**:
   ```java
   Callable<Integer> task = () -> {
       Thread.sleep(1000); // Simulate work
       return 42; // Return result
   };
   ```

2. **Future**:
   - Represents the result of an asynchronous computation.
   - Methods:
     - **`get()`**: Blocks until the task is complete and retrieves the result.
     - **`isDone()`**: Checks if the task is completed.
     - **`cancel()`**: Attempts to cancel the task.
   - Allows checking the status or obtaining results of tasks submitted to an executor.

   **Example**:
   ```java
   ExecutorService executor = Executors.newSingleThreadExecutor();
   Future<Integer> future = executor.submit(task);
   System.out.println(future.get()); // Waits for and retrieves result
   executor.shutdown();
   ```
