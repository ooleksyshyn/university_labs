#pragma once

#include "point.h"
#include <functional>
#include <utility>


using Lambda = std::function<void(Point&)>;


struct Array {
    explicit Array(int n){
        if (n == 0){
            points = new Point[1];
            size = 0;
            capacity = 1;
            empty = true;
        } else {
            points = new Point[n];
            size = n;
            capacity = n;
            empty = n;
        }
    }
    Point& operator[](int i){
        return points[i];
    }
    Point* points;
    bool empty;
    int size;
    int capacity;

    ~Array(){
        if (!empty) delete[] points;
    }
};


Array create_empty(Array& a){
    a = Array(0);
    return a;
}


Array create(Point P, Array&){
    auto new_array = Array(1);
    new_array[0] = P;
    new_array.empty = false;
    new_array.size = 1;
    return new_array;
}


int binary_search_left(Array& a, Point compataror, int left, int right){
    if (left > right) return -1;
    if (left == right && (compataror > a[right] || compataror < a[left])) return -1;
    if (left == right) return left;
    if (left == right - 1){
        if (a[left] >= compataror) return left;
        if (a[right] >= compataror) return right;
        return -1;
    }

    int middle = (left + right)/2;


    if (compataror < a[middle]){
        return binary_search_left(a, compataror, left, middle);
    }

    if (compataror == a[middle]){
        return binary_search_left(a, compataror, left, middle);
    }

    if (compataror > a[middle]){
        return binary_search_left(a, compataror, right, middle);
    }

    return -1;
}


int binary_search_right(Array& a, Point compataror, int left, int right){
    if (left > right) return -1;
    if (left == right && (compataror > a[right] || compataror < a[left])) return -1;
    if (left == right) return left;
    if (left == right - 1){
        if (a[right] <= compataror) return right;
        if (a[left] <= compataror) return left;
        return -1;
    }

    int middle = (left + right)/2;


    if (compataror < a[middle]){
        return binary_search_right(a, compataror, left, middle);
    }

    if (compataror == a[middle]){
        return binary_search_right(a, compataror, middle, right);
    }

    if (compataror > a[middle]){
        return binary_search_right(a, compataror, middle, right);
    }

    return -1;
}


void add(Array& a, Point P) {
    if (a.empty){
        a[0] = P;
        a.empty = false;
        a.size = 1;
        return;
    }
    if (a.capacity == a.size) {
        a.capacity *= 2;
        auto new_array = new Point[a.size];
        for (int i = 0; i < a.size; ++i){
            new_array[i] = a.points[i];
        }
        delete[] a.points;
        a.points = new Point[a.capacity];
        for (int i = 0; i < a.size; ++i) {
            a.points[i] = new_array[i];
        }
        delete[] new_array;
    }


    a.size += 1;

    int insert_index = binary_search_right(a, P, 0, a.size - 2) + 1;

    if (a[a.size - 2] < P) {
        a.points[a.size - 1] = P;
    } else {
        for (int j = a.size - 1; j > insert_index; --j) {
            a.points[j] = a.points[j - 1];
        }
        a.points[insert_index] = P;
    }

}


void add_random(Array& a, int n){
    for (int i = 0; i < n; ++i) {
        add(a, Point(0, 1000));
    }
}


void access(Array& a, Lambda lambda){
    for (int i = 0; i < a.size; ++i){
        lambda(a[i]);
    }
}


void print(Array& a){
    std::cout << "[ ";
    if (a.size == 0) std::cout << "empty array";
    access(a, [](Point& p){std::cout << p << "\n";});
    std::cout << "]";
}


void search(Array& a, Point comparator){
    int left = binary_search_left(a, comparator, 0, a.size - 1);
    int right = binary_search_right(a, comparator, 0, a.size - 1);


    if (left != -1 && right != -1){
        for (int i = left; i <= right; ++i){
            std::cout << a[i] << std::endl;
        }
    }
}


void search(Array& a, Point left, Point right){
    int left_ = binary_search_left(a, left, 0, a.size - 1);
    int right_ = binary_search_right(a, right, 0, a.size - 1);


    std::cout << left_ << " " << right_ << std::endl;
    if (left_ != -1 && right_ != -1){
        for (int i = left_; i <= right_; ++i){
            std::cout << a[i] << std::endl;
        }
    }
}


void delete_(Array& a, Point p){
    int left = binary_search_left(a, p, 0, a.size - 1);
    int right = binary_search_right(a, p, 0, a.size - 1);


    if (right != -1 && left != -1 && (right >= left)){
        for (int i = left; i < a.size - (right - left); ++i){
            a[i] = a[i + right - left + 1];
        }
        a.size = a.size - (right - left + 1);
    }
    if (a.size == 0) a.empty = true;
}