#ifndef TIMERS_AND_WAKERS_H
#define TIMERS_AND_WAKERS_H


#include <QTime>
#include <QString>


class Timer{
public:
    Timer(QTime t, QString s);

    QTime time;
    QString message;
};


class Waker{
public:
    Waker(QTime t, QString s);

    QTime time;
    QString message;

    bool is_active;
};

#endif // TIMERS_AND_WAKERS_H
