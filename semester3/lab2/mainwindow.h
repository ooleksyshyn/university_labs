#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "timers_and_wakers.h"

#include <QMainWindow>
#include <QString>
#include <QListWidgetItem>
#include <QMediaPlayer>

#include <vector>
#include <utility>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    enum class Mode{Timers, Wakers, None};
    class InputError{
    public:
        InputError(QString& err);
        QString what();
    private:
        QString msg;
    };

private:
    QTime parse_input(QString& line);
    void updateTimers(QTime& time);
    void updateWakers(QTime& time);
    void showVideo();

private:
    Mode mode = Mode::None;
    Ui::MainWindow *ui;
    std::vector<Timer> timers;
    std::vector<Waker> wakers;
    QMediaPlayer* player;
    QVideoWidget* vw;

private slots:
    void showCurrentTime();
    void on_Wakers_clicked();
    void on_Timers_clicked();
    void showTimers();
    void showWakers();

    void on_Add_clicked();
    void on_Delete_clicked();
    void on_ShowActive_toggled(bool checked);
};

QTime operator+(QTime left, QTime right);
QTime operator-(QTime left, QTime right);

#endif // MAINWINDOW_H
