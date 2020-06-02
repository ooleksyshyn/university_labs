#pragma once

#include <iostream>
#include <utility>

struct Time{
    Time (){
        hours = 0;
        minutes = 0;
    }

    Time(int hs, int mins){
        hours = hs;
        minutes = mins;
    }

    int hours;
    int minutes;
};

std::ostream& operator<<(std::ostream& os, Time& time){
    if (time.minutes < 10) {
        os << time.hours << ':' << '0' << time.minutes ;
    } else {
        os << time.hours << ':' << time.minutes;
    }
    return os;
}

bool operator>(const Time lhs, const Time rhs){
    if (lhs.hours == rhs.hours) return (lhs.minutes > rhs.minutes);
    return lhs.hours > rhs.hours;
}

Time operator+(Time time1, Time time2){
    time1.minutes += time2.minutes;
    if (time1.minutes > 59) {
        time1.minutes = time1.minutes - 60;
        time1.hours += (time2.hours + 1);
    } else {
        time1.hours += time2.hours;
    }
    return time1;
}

bool operator==(Time lhs, Time rhs){
    return (lhs.minutes == rhs.minutes && lhs.hours == rhs.hours);
}

struct Task {
    Task(){
        beginning_time = Time();
        duration_time = Time();
        completed = false;
    }

    Task(Time b_t, Time d_t){
        beginning_time = b_t;
        duration_time = d_t;
        completed = false;
    }

    Time beginning_time;
    Time duration_time;
    bool completed;
};

std::ostream& operator<<(std::ostream& os, Task& task){

        os << "{ beg : " << task.beginning_time << " ; dur: " << task.duration_time << " }";


    return os;
}

template <class P>
struct Node{

    P data;
    Node* next;
    Node* previous;
    bool empty;
};

template <typename P>
Node<P>* create_empty(P){
    auto new_node = new Node<P>;
    new_node->next = nullptr;
    new_node->previous = nullptr;
    new_node->empty = true;
    return new_node;
}

template <class P>
Node<P>* create_list(const P data){
    auto new_node = new Node<P>;
    new_node->next = nullptr;
    new_node->previous = nullptr;
    new_node->data = data;
    new_node->empty = 0;
    return new_node;
}

void add_by_beginning_time(Node<Task>* list, Task task){

    if (list->empty) {
        list->data = task;
        list->empty = false;
    } else {
        while (list->previous != nullptr){
            list = list->previous;
        }
        Node<Task>* FirstData = create_list(task);


        if (list->data.beginning_time > task.beginning_time) {
            FirstData->next = list;
            list->previous = FirstData;
        } else {

            while (list->next != nullptr) {

                if (list->next->data.beginning_time > task.beginning_time) {
                    FirstData->next = list->next;
                    list->next->previous = FirstData;
                    FirstData->previous = list;
                    list->next = FirstData;


                    return;
                }
                list = list->next;
            }

            if (task.beginning_time > list->data.beginning_time | task.beginning_time == list->data.beginning_time) {
                FirstData->previous = list;
                list->next = FirstData;
            }
        }
    }
}

void add_by_duration_time(Node<Task>* list, Task task){
    if (list->empty) {
        list->data = task;
        list->empty = false;
    } else {
        while (list->previous != nullptr){
            list = list->previous;
        }
        Node<Task> *FirstData = create_list(task);

        if (list->data.duration_time > task.duration_time ) {
            FirstData->next = list;
            list->previous = FirstData;
        } else {

            while (list->next != nullptr) {
                if (list->next->data.duration_time > task.duration_time) {
                    FirstData->next = list->next;
                    list->next->previous = FirstData;
                    FirstData->previous = list;
                    list->next = FirstData;
                    return;
                }
                list = list->next;
            }

            if (task.duration_time > list->data.duration_time | task.duration_time == list->data.duration_time) {
                FirstData->previous = list;
                list->next = FirstData;
            }
        }
    }
}

void complete_task(Node<Task>* list, Time time){
    while (list->previous != nullptr){
        list = list->previous;
    }

    while (list->next != nullptr){
        if (!list->data.completed && (time > list->data.beginning_time)){
            list->data.completed = true;
            return;
        } else {
            list = list->next;
        }
    }

    list->data.completed = true;
}

void PrintList(Node<Task>* list){
    std::cout << "{ ";
    if (list->empty) {
        std::cout << "empty }";
        return;
    }

    while (list->previous != nullptr){
        list = list->previous;
    }

    while(list->next != nullptr){
        std::cout << list->data << ", ";
        list = list->next;
    }

    std::cout << list->data << " }";

}

void get_task(Task& task){
    int hs1, mins1, hs2, mins2;

    std::cin >> hs1 >> mins1 >> hs2 >> mins2;
    task = Task(Time(hs1,mins1), Time(hs2,mins2));
}

Task& first_task_to_do(Node<Task>* list, const Time& time){
    while (list->previous != nullptr){
        list = list->previous;
    }

    while (list->next != nullptr){
        if (!list->data.completed && (time > list->data.beginning_time)){
            return list->data;
        } else {
            list = list->next;
        }
    }

    return list->data;
}