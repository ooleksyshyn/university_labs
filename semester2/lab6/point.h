#pragma once

#include <random>
#include <iostream>


int RandomInt(int begin, int end) {
    static std::random_device rd;
    static std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}

struct Point{
    Point(){
        x = y = z = 0;
    }

    Point(int random_begin, int random_end){
        random_begin *= 1000;
        random_end *= 1000;
        x = RandomInt(random_begin, random_end)/1'000.;
        y = RandomInt(random_begin, random_end)/1'000.;
        z = RandomInt(random_begin, random_end)/1'000.;
    }

    Point(double x_, double y_, double z_){
        x = x_;
        y = y_;
        z = z_;
    }


  double x;
  double y;
  double z;
};



bool operator==(const Point& lhs, const Point rhs){
    return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
}


bool operator!=(const Point& lhs, const Point rhs){
    return !(lhs == rhs);
}


bool operator<(const Point& lhs, const Point& rhs){
    if (lhs.x != rhs.x) return lhs.x < rhs.x;
    if (lhs.y != rhs.y) return lhs.y < rhs.y;
    return lhs.z < rhs.z;
}


bool operator<=(const Point& lhs, const Point& rhs){
    if (lhs.x != rhs.x) return lhs.x < rhs.x;
    if (lhs.y != rhs.y) return lhs.y < rhs.y;
    return lhs.z <= rhs.z;
}


bool operator>(const Point& lhs, const Point& rhs){
    if (lhs.x != rhs.x) return lhs.x > rhs.x;
    if (lhs.y != rhs.y) return lhs.y > rhs.y;
    return lhs.z > rhs.z;
}


bool operator>=(const Point& lhs, const Point& rhs){
    if (lhs.x != rhs.x) return lhs.x > rhs.x;
    if (lhs.y != rhs.y) return lhs.y > rhs.y;
    return lhs.z >= rhs.z;
}


std::ostream& operator<<(std::ostream& os, Point P){
    os << "(" << P.x << ", " << P.y << ", " << P.z << ")";
    return os;
}


std::istream& operator>>(std::istream& is, Point& P){
    double x_, y_, z_;
    is >> x_ >> y_ >> z_;
    P = Point(x_, y_, z_);
    return is;
}


