package taskB;

import javax.swing.*;
import java.util.concurrent.atomic.AtomicInteger;

class  SliderInteractor {
    private JSlider slider;
    private int INITIAL_PRIORITY = 1;
    private int MAX_PRIORITY = 10;
    private int MIN_PRIORITY = 1;
    private Thread thread1;
    private Thread thread2;
    AtomicInteger semaphore = new AtomicInteger(0);
    public SliderInteractor(JSlider s) {
        slider = s;
    }


    public void startTesting() {
        startThread1();
        startThread2();
    }
    protected void startThread1() {
        thread1 = new Thread(() -> {
            while(!Thread.currentThread().isInterrupted()) {
                synchronized (slider) {
                    slider.setValue(slider.getValue() - 1);
                }
            }
        });
        thread1.setDaemon(true);
        thread1.setPriority(MIN_PRIORITY);
        thread1.start();
    }
    protected void startThread2() {
        thread2 = new Thread(() -> {
            while(!Thread.currentThread().isInterrupted()) {
                synchronized (slider) {
                    slider.setValue(slider.getValue() + 1);
                }
            }
        });
        thread2.setDaemon(true);
        thread2.setPriority(MAX_PRIORITY);
        thread2.start();
    }
    public void start1() {
        if (semaphore.compareAndSet(0,1)) {

            startThread1();

        }

    }
    public void stop1() {
        if (semaphore.compareAndSet(1,0)) {
            thread1.setPriority(INITIAL_PRIORITY);
            thread1.interrupt();

        }

    }
    public void start2() {
        if (semaphore.compareAndSet(0,1)) {

            startThread2();

        }
    }
    public void stop2() {

        if (semaphore.compareAndSet(1,0)) {
            thread2.setPriority(INITIAL_PRIORITY);
            thread2.interrupt();

        }

    }
}