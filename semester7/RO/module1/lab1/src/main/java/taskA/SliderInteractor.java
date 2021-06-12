package taskA;

import javax.swing.*;

class SliderInteractor {
    private JSlider slider;
    private int INITIAL_PRIORITY = 1;
    private int MAX_PRIORITY = 10;
    private int MIN_PRIORITY = 1;
    private Thread thread1;
    private Thread thread2;


    public SliderInteractor(JSlider s) {
        slider = s;
    }

    public void startTesting() {
        thread2 = new Thread(() -> {
            while(true) {
                synchronized (slider) {
                    slider.setValue(slider.getValue() + 1);
                }
            }
        });

        thread1 = new Thread(() -> {
            while(true) {
                synchronized (slider) {
                    slider.setValue(slider.getValue() - 1);

                }
            }
        });
        thread2.setDaemon(true);
        thread1.setDaemon(true);
        thread2.setPriority(INITIAL_PRIORITY);
        thread1.setPriority(INITIAL_PRIORITY);
        thread2.start();
        thread1.start();
    }

    protected void increase1() {
        int current = thread1.getPriority();
        if(current < MAX_PRIORITY) {
            current++;
            System.out.println(current);
            thread1.setPriority(current);
        }
        else {
            System.out.println("priority > MAX_PRIORITY");
        }
    }
    protected void decrease1() {
        int current = thread1.getPriority();
        if(current > MIN_PRIORITY) {
            current--;
            System.out.println(current);
            thread1.setPriority(current);
        }
        else {
            System.out.println("priority < MIN_PRIORITY");
        }

    }
    protected void increase2() {
        int current = thread2.getPriority();
        if(current < MAX_PRIORITY) {
            current++;
            System.out.println(current);
            thread2.setPriority(current);
        }
        else {
            System.out.println("priority > MAX_PRIORITY");
        }
    }
    void decrease2() {
        int current = thread2.getPriority();
        if(current > MIN_PRIORITY) {
            current--;
            System.out.println(current);
            thread2.setPriority(current);
        }
        else {
            System.out.println("priority < MIN_PRIORITY");
        }
    }
}