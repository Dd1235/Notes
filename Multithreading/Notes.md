### Multithreading in Java

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