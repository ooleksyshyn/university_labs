package taskB;

import javax.swing.*;

public class Slider extends JFrame{

    private JButton startButton2;
    private JButton startButton1;

    private JButton stopButton2;
    private JButton stopButton1;
    private JSlider slider;
    private JPanel mainPanel;
    private JLabel semaphoreLabel;

    public Slider() {
        super("Slider");
        setContentPane(mainPanel);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setLocation(new java.awt.Point(400, 200));
        setResizable(false);
        setVisible(true);
        pack();

        SliderInteractor sliderInteractor = new SliderInteractor(slider);



        startButton1.addActionListener(e ->{
            sliderInteractor.start1();
            semaphoreLabel.setText("Thread1 locked the slider");
            startButton2.setEnabled(false);

        });

        stopButton1.addActionListener(e ->{
            sliderInteractor.stop1();
            semaphoreLabel.setText("Thread1 unlocked the slider");
            startButton2.setEnabled(true);

        } );

        startButton2.addActionListener(e -> {
            sliderInteractor.start2();
            semaphoreLabel.setText("Thread2 locked the slider");
            startButton1.setEnabled(false);

        });

        stopButton2.addActionListener(e ->{
            sliderInteractor.stop2();
            semaphoreLabel.setText("Thread2 unlocked the slider");
            startButton1.setEnabled(true);

        } );
    }
}