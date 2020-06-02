#pragma once

#include "point.hpp"

#include <iostream>
#include <vector>
#include <memory>

const int array_size = 100000;


template <typename T>
class BaseQueue{
public:

    virtual void push_back(T object) = 0;

    virtual void pop_front() = 0;

    [[nodiscard]]
    virtual auto size() const -> int = 0;

    virtual auto operator[](int index) -> T& = 0;
};


template <typename T>
class ArrayQueue : public BaseQueue<T>{
public:
    ArrayQueue();

    void push_back(T object) override;

    [[nodiscard]]
    auto size() const -> int override;

    void pop_front() override;

    auto operator[](int index) -> T& override;

private:
    T array[array_size];
    int size_;
};


template <typename T>
struct Node{
    explicit Node(T data);

    T data;
    std::shared_ptr<Node> next;
    std::shared_ptr<Node> previous;
};


template <typename T>
class ListQueue : public BaseQueue<T>{
public:
    ListQueue();

    void push_back(T object) override;

    void pop_front() override;

    auto operator[](int index) -> T& override;

    [[nodiscard]]
    auto size() const -> int override;

private:
    std::shared_ptr<Node<T>> list;
    int size_;
};


template<typename T>
class VectorQueue : public BaseQueue<T>{
public:
    VectorQueue();

    void push_back(T object) override;

    void pop_front() override;

    auto operator[](int index) -> T& override;

    [[nodiscard]]
    auto size() const -> int override;
private:
    std::vector<T> data;
};


template<typename OStream, typename T>
OStream& operator<<(OStream& os, BaseQueue<T>& queue);


template<typename OStream, typename T>
OStream& operator<<(OStream& os, std::vector<T>& vec);



template<typename OStream>
OStream& operator<<(OStream& os, const Point& p);

template<typename IStream>
IStream& operator>>(IStream& is, Point& p);


#include "structures.tpp"