public class helloThreads {
    static int answer = 0;
    static void badSum() throws InterruptedException { // The multithreading is work well and without any issues. But it wasn't very clear so I just did my it according to my own understanding.
        answer = 0;
        final int maxValue = 100;
        final int numThreads = 5;
        int threadNumber = (int) Thread.currentThread().getId();
        Thread [] threads = new Thread[numThreads];
        for(int j = 0; j < numThreads; j++) {
            final int finalI = j;
            Thread t = new Thread(() -> {
                for(int i = (finalI*maxValue/numThreads); i < (Math.min((finalI+1)*maxValue/numThreads, maxValue)); i++) {
                    answer += i;
                    System.out.println(answer);
                    answer = (maxValue * (maxValue - 1) / 2);
                    System.out.println("The correct answer is: " + answer);
                }
            });
            t.start();
            t.join(); // I have same answer for any number of threads as it seems like they are joined together and allows it to wait for the previous thread. I still see no difference expect the value changing drastically.

        }
        answer = (maxValue * (maxValue - 1) / 2);
        System.out.println("The correct answer is: " + answer);

    }
    static void counter() {
        int count = 0;
        while (count <= 100) {
            if (count % 10 != 0) {
                System.out.print("hello number " + count + " from thread number " + Thread.currentThread().getId());
                count++;
            } else {
                System.out.println('\n');
                count++;
            }
        }
    }

    static void sayHello() throws InterruptedException {
        Thread [] threads = new Thread[10];
        Runnable counter = new Runnable() {
            @Override
            public void run() {
                counter();
            }
        };
        for(Thread t: threads) {
            t = new Thread(counter);
            t.start();
            t.join(); // Made all the threads run in order.
        }
    }



    public static void main(String[] args) throws InterruptedException {
//        sayHello();
        badSum();
    }
}
