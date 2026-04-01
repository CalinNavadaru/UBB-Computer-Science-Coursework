package cs.ubbcluj.ro;

import java.util.Arrays;
import java.util.Random;

class MyThread extends Thread {
    int start, end;
    int[] a, b, c;

    MyThread(int startI, int endI, int[] x, int[] y, int[] r) {
        start = startI;
        end = endI;
        a = x;
        b = y;
        c = r;
    }

    public void run() {
        for (int i = start; i < end; i++) {
            c[i] = (int) Math.sqrt(a[i] * a[i] * a[i] * a[i] * a[i] + b[i] * b[i] * b[i] * b[i] * b[i]);
        }
    }
}

class MyThread2 extends Thread {
    int index, n, pp;
    int[] a, b, c;

    MyThread2(int ind, int nn, int p, int[] x, int[] y, int[] r) {
        index = ind;
        n = nn;
        pp = p;
        a = x;
        b = y;
        c = r;
    }

    public void run() {
        for (int i = index; i < n; i += pp) {
            c[i] = (int) Math.sqrt(a[i] * a[i] * a[i] * a[i] * a[i] + b[i] * b[i] * b[i] * b[i] * b[i]);
        }
    }
}

public class Main {

    private static int[] vector(int n, int upperBound) {
        int[] result = new int[n];
        Random random = new Random();
        for (int i = 0; i < result.length; i++) {
            result[i] = random.nextInt(upperBound);
        }
        return result;
    }

    private static int[] sum(int[]a, int[] b) {
        int length = Math.min(a.length, b.length);
        int[] c = new int[length];
        for (int i = 0; i < length; i++) {
            c[i] = (int) Math.sqrt(a[i] * a[i] * a[i] * a[i] * a[i] + b[i] * b[i] * b[i] * b[i] * b[i]);
        }
        return c;
    }
//
//    public static void main(String[] args) {
//            int n = 10;
//            int[] a = Main.vector(n, 100);
//            int[] b = Main.vector(n, 10);
//            System.out.println(Arrays.toString(Main.sum(a, b)));
//    }
//    public static void main(String[] args) throws InterruptedException {
//
//        MyThread[] threadList = new MyThread[15];
//        for (int i = 0; i < threadList.length; i++) {
//            threadList[i] = new MyThread(i);
//            threadList[i].start();
//        }
//        for (MyThread myThread : threadList) {
//            myThread.join();
//        }
//    }

    public static void main(String[] args) throws InterruptedException {
        int n = 100_000_000;
        int p = 4;
        int[] a = Main.vector(n, 1000);
        int[] b = Main.vector(n, 1000);
        int[] cc = Main.vector(n, 1000);


        long startTime = System.currentTimeMillis();
        int[] c = Main.sum(a, b);
        long endTime = System.currentTimeMillis();
        System.out.println(endTime - startTime);

        startTime = System.currentTimeMillis();
        MyThread[] threadList = new MyThread[p];
        int start = 0, end = n / p, rest = n % p;
        for (int i = 0; i < threadList.length; i++) {
            if (rest > 0) {
                end += 1;
                rest -= 1;
            }
            threadList[i] = new MyThread(start, end, a, b, cc);
            threadList[i].start();
            start = end;
            end = start +  n / p;
        }
        for (MyThread myThread : threadList) {
            myThread.join();
        }
        endTime = System.currentTimeMillis();
        System.out.println(endTime - startTime);

        startTime = System.currentTimeMillis();
        MyThread2[] thread2List = new MyThread2[p];
        for (int i = 0; i < threadList.length; i++) {
            if (rest > 0) {
                end += 1;
                rest -= 1;
            }
            thread2List[i] = new MyThread2(i, n, p, a, b, cc);
            thread2List[i].start();
        }
        for (MyThread2 myThread : thread2List) {
            myThread.join();
        }
        endTime = System.currentTimeMillis();
        System.out.println(endTime - startTime);
    }
}