#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDateTime>
#include <QMessageBox>
#include <QVideoWidget>
#include <QMediaPlayer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer* timer = new QTimer(this);

    player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/media/media/dinosaur.mp4"));


    ui->ShowActive->hide();
    connect(timer, SIGNAL(timeout()), this, SLOT(showCurrentTime()));
    timer->start();
    mode = Mode::Timers;
    ui->Timers->setStyleSheet("background-color: gray");
    showTimers();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showCurrentTime(){
    QTime time = QTime::currentTime();

    QString time_string = "Current time: " + time.toString("hh:mm:ss");
    if (time.second() % 2 == 0){
        time_string[16] = time_string[19] = ' ';
    }
    ui->statusBar->showMessage(time_string);

    updateTimers(time);
    updateWakers(time);
    if (mode == Mode::Timers){
        for (int i = 0; i < timers.size(); ++i){
            QString time = (timers[i].time - QTime::currentTime()).toString("hh:mm:ss");
            QString message = timers[i].message;
            ui->TimersAndWakers->item(i)->setText(time + " : " + message);
        }
        //showTimers();
    }
}

void MainWindow::updateTimers(QTime& time){
    int i = 0;
    while (i < timers.size()){
        if (timers[i].time == time){
            //ui->TimersAndWakers->item
            if (!ui->DoNotDisturb->isChecked()){
                showVideo();

                //QMessageBox::information(this, "Waker allert", time.toString() + "\n" + wakers[i].message);
                auto messageBox = new QMessageBox;
                messageBox->setIcon(QMessageBox::Information);
                messageBox->setText("Timer allert");
                messageBox->setStandardButtons(QMessageBox::Close);
                messageBox->setInformativeText(time.toString() + "\n" + timers[i].message);

                int result = messageBox->exec();
                player->stop();

                delete messageBox;
            }
            timers.erase(timers.begin() + i);
            if (mode == Mode::Timers){
                showTimers();
            }
        } else ++i;
    }

}

void MainWindow::updateWakers(QTime& time){
    int i = 0;
    while (i < wakers.size()){
        if (wakers[i].time == time && wakers[i].is_active){

            if (!ui->DoNotDisturb->isChecked()){
                showVideo();
                //QMessageBox::information(this, "Waker allert", time.toString() + "\n" + wakers[i].message);
                auto messageBox = new QMessageBox;
                messageBox->setIcon(QMessageBox::Information);
                messageBox->setText("Waker allert");
                messageBox->setStandardButtons(QMessageBox::Close);
                messageBox->setInformativeText(time.toString() + "\n" + wakers[i].message);

                int result = messageBox->exec();
                player->stop();

                delete messageBox;
            }
            wakers[i].is_active = false;
            if (mode == Mode::Wakers){
                showWakers();
            }
        } else ++i;
    }
}


MainWindow::InputError::InputError(QString& err): msg(err){}

QString MainWindow::InputError::what(){
    return msg;
}



void MainWindow::on_Wakers_clicked()
{
    ui->ShowActive->show();
    mode = Mode::Wakers;
    ui->Wakers->setStyleSheet("background-color: gray");
    ui->Timers->setStyleSheet("background-color: white");
    ui->message->setText("Enter new waker (hh:mm:ss):");
    showWakers();
}

void MainWindow::on_Timers_clicked()
{
    ui->ShowActive->hide();
    mode = Mode::Timers;
    ui->Wakers->setStyleSheet("background-color: white");
    ui->Timers->setStyleSheet("background-color: gray");
    ui->message->setText("Enter new timer (hh:mm:ss):");
    showTimers();
}

void MainWindow::showTimers(){
    ui->TimersAndWakers->clear();
    for (auto timer : timers){
        QString time = (timer.time - QTime::currentTime()).toString("hh:mm:ss");
        QString message = timer.message;
        ui->TimersAndWakers->addItem(time + " : " + message);
    }
}

void MainWindow::showWakers(){
    ui->TimersAndWakers->clear();
    for (auto waker : wakers){
        if (waker.is_active || !ui->ShowActive->isChecked()) {
            QString time = waker.time.toString("hh:mm:ss");
            QString message = waker.message;
            QString active = waker.is_active ? "active" : "inactive";
            ui->TimersAndWakers->addItem(time + " " + active + " : " + message);
        }
    }
}

QTime MainWindow::parse_input(QString& line){
    if (line.size() != 8) throw InputError(line);
    if (line[2] != ':' || line[5] != ':') throw InputError(line);

    for (auto index : {0, 1, 3, 4, 6, 7}){
        bool isDigit = false;
        for (auto digit : "1234567890"){
            if (line[index] == digit){
                isDigit = true;
            }
        }
        if (!isDigit) throw InputError(line);
    }

    int hours = 10 * QString(line[0]).toInt() + QString(line[1]).toInt();
    int minutes = 10 * QString(line[3]).toInt() + QString(line[4]).toInt();
    int seconds = 10 * QString(line[6]).toInt() + QString(line[7]).toInt();

    if (hours > 23) throw InputError(line);
    if (minutes > 59) throw InputError(line);
    if (seconds > 59) throw InputError(line);

    return QTime(hours, minutes, seconds);
}

void MainWindow::on_Add_clicked()
{
    QString input_time = ui->lineEdit->text();
    QString input_description = ui->messageEdit->text();

    if (input_time == "" && ui->TimersAndWakers->currentRow() >= -1 && mode == Mode::Wakers){
        wakers[ui->TimersAndWakers->currentRow()].is_active = true;
        showWakers();
    } else{
        try{
            QTime time = parse_input(input_time);
            if (mode == Mode::Timers){
                timers.push_back(Timer(time + QTime::currentTime(), input_description));
                showTimers();
            } else{
                wakers.push_back(Waker(time, input_description));
                showWakers();
            }
        } catch (InputError& err){
            QMessageBox::warning(this, "An error occured", "Invalid time input: " + err.what());
        }

        ui->lineEdit->clear();
        ui->messageEdit->clear();
    }
}

void MainWindow::on_Delete_clicked()
{
    auto row = ui->TimersAndWakers->currentRow();
    if (row == -1) return;
    if (mode == Mode::Timers){
        timers.erase(timers.begin() + row);
        showTimers();
    } else {
        wakers.erase(wakers.begin() + row);
        showWakers();
    }
}


void MainWindow::showVideo(){
    player->play();
}

QTime operator+(QTime left, QTime right){
    int seconds = left.second() + right.second();
    int minutes = left.minute() + right.minute();
    int hours = left.hour() + right.hour();

    if (seconds > 59){
        seconds -= 60;
        ++minutes;
    }

    if (minutes > 59){
        minutes -= 60;
        ++hours;
    }

    if (hours > 23){
        hours -= 23;
    }

    return QTime(hours, minutes, seconds);
}

QTime operator-(QTime left, QTime right){
    int seconds = left.second() - right.second();
    int minutes = left.minute() - right.minute();
    int hours = left.hour() - right.hour();

    if (seconds < 0){
        seconds += 60;
        --minutes;
    }

    if (minutes < 0){
        minutes += 60;
        --hours;
    }

    if (hours < 0){
        hours += 24;
    }

    return QTime(hours, minutes, seconds);
}

void MainWindow::on_ShowActive_toggled(bool checked)
{
    if (mode == Mode::Timers){
        showTimers();
    } else showWakers();
}
