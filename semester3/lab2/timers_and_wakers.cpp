#include "timers_and_wakers.h"


Timer::Timer(QTime t, QString s) : time(t), message(s){}


Waker::Waker(QTime t, QString s) : time(t), message(s), is_active(true){}
