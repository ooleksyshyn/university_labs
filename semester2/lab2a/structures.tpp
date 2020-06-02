#pragma once

#include "structures.h"


template<typename T>
Node<T>::Node(T data) : data(data), next(nullptr), previous(nullptr){

}


//------------------------------- Array queue -------------------------------------//


template<typename T>
ArrayQueue<T>::ArrayQueue(): size_(0){}

template<typename T>
void ArrayQueue<T>::push_back(T object){
    if (size_ == array_size){
        std::cout << "The array cant contai more than " << array_size << " elements" << std::endl;
        return;
    }
    array[size_] = object;
    ++size_;
}


template<typename T>
int ArrayQueue<T>::size() const {
    return size_;
}

template <typename T>
void ArrayQueue<T>::pop_front() {
    for (int i = 0; i < size_ - 1; ++i){
        array[i] = array[i+1];
    }
    array[size_] = T();
    --size_;
}


template <typename T>
T& ArrayQueue<T>::operator[](int index) {
    return array[index];
}



//------------------------------- List queue -------------------------------------//


template<typename T>
ListQueue<T>::ListQueue() : list(nullptr), size_(0){
}


template<typename T>
void ListQueue<T>::push_back(T object){
    ++size_;
    auto new_data = std::make_shared<Node<T>>(object);

    if (size_ == 1){
        list = new_data;
        return;
    }

    while (list->next){
        list = list->next;
    }

    list->next = new_data;
    list->next->previous = list;
    while (list->previous != nullptr) list = list->previous;
}


template<typename T>
void ListQueue<T>::pop_front() {
    if (size_ == 1 | size_ == 0) {
        std::cout << "Cant erase the single element of list";
        return;
    }

    --size_;

    list = list->next;
    list->previous = nullptr;
}

template<typename T>
T& ListQueue<T>::operator[](int index){

    int i = 0;
    while(i != index){
        ++i;
        list = list->next;
    }
    T& result = list->data;

    while (list->previous != nullptr) list = list->previous;
    return result;
}


template<typename T>
int ListQueue<T>::size() const{
    return size_;
}



//---------------------------------- VectorQueue --------------------------------------//



template<typename T>
VectorQueue<T>::VectorQueue() : data() {}

template<typename T>
void VectorQueue<T>::push_back(T object) {
    data.push_back(object);
}

template<typename T>
auto VectorQueue<T>::operator[](int index) -> T & {
    return data[index];
}

template<typename T>
auto VectorQueue<T>::size() const -> int {
    return data.size();
}

template<typename T>
void VectorQueue<T>::pop_front() {
    data.erase(data.begin());
}



//---------------------------------- others -------------------------------------------//



template<typename OStream, typename T>
OStream& operator<<(OStream& os, ArrayQueue<T>& queue){
    for (int i = 0; i < queue.size(); ++i){
        os << queue[i] << ' ';
    }
    if (queue.size() == 0) os << "The queue is empty";
    return os;
}


template<typename OStream, typename T>
OStream& operator<<(OStream& os, ListQueue<T>& queue){
    for (int i = 0; i < queue.size(); ++i){
        os << queue[i] << ' ';
    }
    if (queue.size() == 0) os << "The queue is empty";
    return os;
}


template<typename OStream, typename T>
OStream& operator<<(OStream& os, std::vector<T>& vec){
    for (int i = 0; i < vec.size(); ++i){
        os << vec[i] << ' ';
    }
    if (vec.size() == 0) os << "The queue is empty";
    return os;
}




template<typename OStream>
OStream& operator<<(OStream& os, const Point& p){
    os << '(' << p.X << ',' << p.Y << ',' << p.Z << ')';
    return os;
}


template<typename IStream>
IStream& operator>>(IStream& is, Point& p){
    double x = 0, y = 0, z = 0;
    is >> x >> y >> z;
    p = Point(x,y,z);
    return is;
}