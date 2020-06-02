#include <iostream>
#include <string>
#include <vector>
#include "worker.h"
#include "list.h"

void demonstration();
void user();

int main() {

    std::string command = " ";
    while (command != "EXIT") {
        std::cout << "CHOOSE MODE (USER, DEMONSTRATION OR EXIT): ";
        std::cin >> command;
        if (command == "DEMONSTRATION") demonstration();
        if (command == "USER") user();
    }


    return 0;
}

void demonstration(){
    {
        Node<Task> *job_scheduler1 = create_empty(Task());


        const int workers_amount_1 = 2;

        add_by_beginning_time(job_scheduler1, Task(Time(8, 30), Time(1, 0)));
        add_by_beginning_time(job_scheduler1, Task(Time(8, 30), Time(1, 10)));
        add_by_beginning_time(job_scheduler1, Task(Time(8, 40), Time(5, 0)));
        add_by_beginning_time(job_scheduler1, Task(Time(8, 40), Time(2, 45)));
        add_by_beginning_time(job_scheduler1, Task(Time(8, 35), Time(0, 20)));


        std::vector<Worker> workers(workers_amount_1, Worker(Task(), Time(), false));
        Time timer = Time(8, 0);

        std::cout << "FCFS, amount of workers = 2. Tasks List:" << std::endl;
        PrintList(job_scheduler1);
        std::cout << std::endl;
        while (Time(18, 0) > timer) {


            for (int i = 0; i < workers_amount_1; ++i) {
                if (workers[i].busy && (timer == workers[i].task_time)) {
                    std::cout << "Task completed: " << workers[i].current_task << " by worker " << i + 1;

                    std::cout << " at " << timer << std::endl;

                    workers[i].busy = false;
                }
                if (!workers[i].busy) {

                    Task task = first_task_to_do(job_scheduler1, timer);
                    if (!task.completed && (timer + Time(0, 1) > (task.beginning_time))) {

                        workers[i].current_task = task;
                        workers[i].busy = true;
                        workers[i].task_time = timer + task.duration_time;
                        complete_task(job_scheduler1, timer);
                    }
                }
            }
            timer = timer + Time(0, 1);
        }
    }

    std::cout << std::endl;

    {
        Node<Task> *job_scheduler1 = create_empty(Task());


        const int workers_amount_1 = 2;

        add_by_duration_time(job_scheduler1, Task(Time(8, 30), Time(1, 0)));
        add_by_duration_time(job_scheduler1, Task(Time(8, 30), Time(1, 10)));
        add_by_duration_time(job_scheduler1, Task(Time(8, 40), Time(5, 0)));
        add_by_duration_time(job_scheduler1, Task(Time(8, 40), Time(2, 45)));
        add_by_duration_time(job_scheduler1, Task(Time(8, 35), Time(0, 20)));


        std::vector<Worker> workers(workers_amount_1, Worker(Task(), Time(), false));
        Time timer = Time(8, 0);

        std::cout << "SJF, amount of workers = 2. Tasks List:" << std::endl;
        PrintList(job_scheduler1);
        std::cout << std::endl;
        while (Time(18, 0) > timer) {


            for (int i = 0; i < workers_amount_1; ++i) {
                if (workers[i].busy && (timer == workers[i].task_time)) {
                    std::cout << "Task completed: " << workers[i].current_task << " by worker " << i + 1;

                    std::cout << " at " << timer << std::endl;

                    workers[i].busy = false;
                }
                if (!workers[i].busy) {

                    Task task = first_task_to_do(job_scheduler1, timer);
                    if (!task.completed && (timer + Time(0, 1) > (task.beginning_time))) {

                        workers[i].current_task = task;
                        workers[i].busy = true;
                        workers[i].task_time = timer + task.duration_time;
                        complete_task(job_scheduler1, timer);
                    }
                }
            }
            timer = timer + Time(0, 1);
        }
    }
}

void user(){

    Node<Task>* job_scheduler = create_empty(Task());

    int tasks_amount, workers_amount;
    std::cout << "TYPE AMOUNT OF TASKS: ";
    std::cin >> tasks_amount;
    std::cout << "CHOOSE PRINCIPLE: FCFS OR SJF: ";
    std::string principle;
    std::cin >> principle;
    std::cout << "INSERT " << tasks_amount << " TASKS, PROVIDING BEGINNING TIME AND DURATION"
              << " (HOURS, MINUTES, HOURS, MINUTES): " << std::endl;
    for (int i = 0; i < tasks_amount; ++i){
        Task task;
        get_task(task);
        if (principle == "FCFS") add_by_beginning_time(job_scheduler,task);
        if (principle == "SJF") add_by_duration_time(job_scheduler,task);
    }

    std::cout << "INSERT AMOUNT OF WORKERS: ";
    std::cin >> workers_amount;

    std::vector<Worker> workers(workers_amount, Worker(Task(),Time(),false));
    Time timer = Time(8, 0);
    PrintList(job_scheduler);
    std::cout << std::endl;
    while (Time(18,0) > timer ){


        for (int i = 0; i < workers_amount; ++i){
            if (workers[i].busy && (timer == workers[i].task_time)){
                std::cout << "Task completed: " << workers[i].current_task << " by worker " << i + 1;

                std::cout << " at " << timer << std::endl;

                workers[i].busy = false;
            }
            if (!workers[i].busy) {

                Task task = first_task_to_do(job_scheduler, timer);
                if (!task.completed && (timer > task.beginning_time)) {

                    workers[i].current_task = task;
                    workers[i].busy = true;
                    workers[i].task_time = timer + task.duration_time;
                    complete_task(job_scheduler, timer);
                }
            }
        }
        timer = timer + Time(0,1);
    }
}