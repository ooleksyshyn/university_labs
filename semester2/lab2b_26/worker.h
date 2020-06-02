#include "list.h"


struct Worker{
    Worker(Task task, Time time, bool flag){
        current_task = task;
        task_time = time;
        busy = flag;
    }

    Task current_task;
    Time task_time;
    bool busy;
};