#pragma once


#include <iostream>


struct Date_Time{
    Date_Time(){
        hour = 0;
        minute = 0;
        day = 0;
        month = 0;
        year = 0;
    }

    Date_Time(int Hour, int Minute, int Day, int Month, int Year){
        hour = Hour;
        minute = Minute;
        day = Day;
        month = Month;
        year = Year;
    }

    int year;
    int month;
    int day;
    int hour;
    int minute;
};


std::ostream& operator<<(std::ostream& os, Date_Time time){
    if (time.minute < 10){
        os << time.hour << ":0" << time.minute << " " << time.day << "." << time.month << "." << time.year;
    } else{
        os << time.hour << ":" << time.minute << " " << time.day << "." << time.month << "." << time.year;
    }
    return os;
}


bool operator>(const Date_Time& left, const Date_Time& right){
    if (left.year != right.year) return left.year > right.year;
    if (left.month != right.month) return left.month > right.month;
    if (left.day != right.day) return left.day > right.day;
    if (left.hour != right.hour) return left.hour > right.hour;
    return left.minute > right.minute;
}


bool operator==(const Date_Time& left, const Date_Time& right){
    if (left.year != right.year) return false;
    if (left.month != right.month) return false;
    if (left.day != right.day) return false;
    if (left.hour != right.hour) return false;
    return left.minute == right.minute;
}