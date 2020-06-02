#pragma once

#include <string>
#include <fstream>
#include <iostream>

class Time{
public:
    Time(){
        Minutes = 0;
        Hours = 0;
    }

    Time(const int hrs, const int mns){
        Minutes = mns;
        Hours = hrs;
    }

    void operator=(const Time& rhs){
        Minutes = rhs.minutes();
        Hours = rhs.hours();
    }


    int minutes() const {
        return Minutes;
    }

    int hours() const {
        return Hours;
    }

    void change_minutes(const int mns) {
        Minutes = mns;
    }

    void change_hours(const int hrs) {
        Hours = hrs;
    }

private:
    int Minutes;
    int Hours;
};

std::ostream& operator<<(std::ostream& os, const Time& time){
    os << time.hours() << ' ' << time.minutes();
    return os;
}

std::istream& operator>>(std::istream& is, Time& time){
    int mins, hours;
    is >> hours >> mins;
    time = Time(hours,mins);
    return is;
}

bool operator>=(const Time& lhs, const Time& rhs){
    if (lhs.hours() == rhs.hours()) return lhs.minutes() >= rhs.minutes();
    return lhs.hours() > rhs.hours();
}

bool operator==(const Time& lhs, const Time& rhs){
    return (lhs.minutes() == rhs.minutes() && lhs.hours() == rhs.hours());
}

class Date{
public:

    Date(){
        Day = 0;
        Month = 0;
        Year = 0;
    }

    Date(const int day, const int month, const int year){
        Day = day;
        Month = month;
        Year = year;
    }

    int day() const {
        return Day;
    }

    int month() const {
        return Month;
    }

    int year() const {
        return Year;
    }

    void change_day(const int& d) {
        Day = d;
    }

    void change_month(const int& m) {
        Month = m;
    }

    void change_year(const int y) {
        Year = y;
    }

    void operator=(const Date& rhs){
        Day = rhs.day();
        Month = rhs.month();
        Year = rhs.year();
    }

private:
    int Day;
    int Month;
    int Year;
};

std::ostream& operator<<(std::ostream& os, const Date& date){
    os << date.day() << ' ' << date.month() << ' ' << date.year();
    return os;
}

std::istream& operator>>(std::istream& is, Date& date){
    int day, month, year;
    is >> day >> month >> year;
    date = Date(day,month,year);
    return is;
}

bool operator>=(const Date& lhs, const Date& rhs){
    if (lhs.year() == rhs.year() && lhs.month() == rhs.month()) return lhs.day() >= rhs.day();
    if (lhs.year() == rhs.year()) return lhs.month() >= rhs.month();
    return lhs.year() == rhs.year();
}

bool operator==(const Date& lhs, const Date& rhs){
    return (lhs.day() == rhs.day() && lhs.month() == rhs.month() && lhs.year() == rhs.year());
}

class Train{
public:

    Train(
    const int data_id = 0,
    const std::string name = "No_Name",
    const int number = 0,
    const std::string type = "No_Type",
    const Date departure_date = Date(),
    const Time departure_time = Time(),
    const Date arrival_date = Date(),
    const Time arrival_time = Time(),
    const double popularity_rate = 0){
        Data_ID = data_id;
        Name = name;
        Number = number;
        Type = type;
        Departure_Date = departure_date;
        Departure_Time = departure_time;
        Arrival_Date = arrival_date;
        Arrival_Time = arrival_time;
        Popularity_Rate = popularity_rate;
    }

    int data_id() const {
        return Data_ID;
    }

    std::string name() const {
        return Name;
    }

    int number() const {
        return Number;
    }

    std::string type() const {
        return Type;
    }

    Date arrival_date() const {
        return Arrival_Date;
    }

    Time arrival_time() const {
        return Arrival_Time;
    }

    Date departure_date() const {
        return Departure_Date;
    }

    Time departure_time() const {
        return Departure_Time;
    }

    double popularity_rate() const {
        return Popularity_Rate;
    }

    void change_name(const std::string name){
        Name = name;
    }

    void change_number(const int num) {
        Number = num;
    }

    void change_type(const std::string typ) {
        Type = typ;
    }

    void change_arrival_date(const Date arr_dat) {
        Arrival_Date = arr_dat;
    }

    void change_arrival_time(const Time arrival_time){
        Arrival_Time = arrival_time;
    }

    void change_departure_date(const Date dep_dat) {
        Departure_Date = dep_dat;
    }

    void change_departure_time(const Time departure_time){
        Departure_Time = departure_time;
    }

    void change_popularity_rate(const double popul_rate) {
        Popularity_Rate = popul_rate;
    }


private:
    int Data_ID;
    std::string Name;
    int Number;
    std::string Type;
    Date Departure_Date;
    Time Departure_Time;
    Date Arrival_Date;
    Time Arrival_Time;
    double Popularity_Rate;
};

std::ostream& operator<<(std::ostream& os, const Train& train){
    os << train.data_id() << ' ' << train.name() << ' ' << train.number() << ' ' << train.type() << ' '
       << train.departure_date() << ' ' << train.departure_time() << ' '
       << train.arrival_date()   << ' ' << train.arrival_time()   << ' '
       << train.popularity_rate();
    return os;
}

std::istream& operator>>(std::istream& is, Train& train){
    int Data_ID, Number;
    std::string Name, Type;
    Date Departure_Date, Arrival_Date;
    Time Departure_Time, Arrival_Time;
    double Popularity_Rate;
    is >> Data_ID >> Name >> Number >> Type
       >> Departure_Date >> Departure_Time
       >> Arrival_Date >> Arrival_Time >> Popularity_Rate;
    train = Train(Data_ID,Name,Number,Type,Departure_Date,Departure_Time,Arrival_Date,Arrival_Time,Popularity_Rate);
    return is;
}

template <class T>
T GetData(const std::string message, const T& DataType){
    T NewData;
    std::cout << message << ": ";
    std::cin >> NewData;
    return NewData;
}

void GetTrain(std::istream& is, Train& train){
    std::cout << "Insert ";
    int Data_ID = GetData("Data ID", Data_ID);
    std::string Name = GetData("Name", Name);
    int Number = GetData("Number", Number);
    std::string Type = GetData("Type", Type);
    Date Departure_Date = GetData("Departure date", Departure_Date);
    Time Departure_Time = GetData("Departure time", Departure_Time);
    Date Arrival_Date = GetData("Arrival Date", Arrival_Date);
    Time Arrival_Time = GetData("Arrival time", Arrival_Time);
    double Popularity_Rate = GetData("Popularity rate", Popularity_Rate);
    train = Train(Data_ID,Name,Number,Type,Departure_Date,Departure_Time,Arrival_Date,Arrival_Time,Popularity_Rate);
}

void PrintTrain(std::ostream& os, const Train& train){
    os << train.data_id() << ' ' << train.name() << ' ' << train.number() << ' ' << train.type() << ' '
       << std::endl << "On it`s way: "
       << train.departure_date() << ' ' << train.departure_time() << " - "
       << train.arrival_date()   << ' ' << train.arrival_time()   << ' '
       << std::endl << "Popularity: "  << train.popularity_rate() << std::endl;
}

template<typename T>
std::istream & binary_read(std::istream& stream, T& value){
    return stream.read(reinterpret_cast<char*>(&value), sizeof(T));
}

void binary_read_string(std::ifstream& stream, std::string& s){
    int line_size;
    binary_read(stream, line_size);
    std::string new_line;
    for (int i = 0; i < line_size; ++i){
        char ch;
        binary_read(stream,ch);
        new_line += ch;
    }
    s = new_line;
}

template<typename T>
std::ostream& binary_write(std::ofstream& stream, const T value){
    return stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

std::ostream& binary_write_string(std::ofstream& stream, const std::string value){
    int size = value.size();
    binary_write(stream, size);
    return stream.write(value.c_str(), value.length());
}

void binary_read_train(std::ifstream& stream, Train& T){
    int Data_ID;
    binary_read(stream, Data_ID);

    std::string Name;
    binary_read_string(stream,Name);

    int Number;
    binary_read(stream,Number);

    std::string Type;
    binary_read_string(stream,Type);

    int d,m,y;
    binary_read(stream,d);
    binary_read(stream,m);
    binary_read(stream,y);
    Date Departure_Date(d,m,y);

    int h,mins;
    binary_read(stream,h);
    binary_read(stream,mins);
    Time Departure_Time(h,mins);

    binary_read(stream,d);
    binary_read(stream,m);
    binary_read(stream,y);
    Date Arrival_Date(d,m,y);

    binary_read(stream,h);
    binary_read(stream,mins);
    Time Arrival_Time(h,mins);

    double Popularity_Rate;
    binary_read(stream,Popularity_Rate);
    T = Train(Data_ID,Name,Number,Type,Departure_Date,Departure_Time,Arrival_Date,Arrival_Time,Popularity_Rate);
}

void binary_write_train(std::ofstream& stream, const Train& T){
    binary_write(stream,T.data_id());
    binary_write_string(stream,T.name());
    binary_write(stream,T.number());
    binary_write_string(stream,T.type());

    binary_write(stream,T.departure_date().day());
    binary_write(stream,T.departure_date().month());
    binary_write(stream,T.departure_date().year());

    binary_write(stream,T.departure_time().hours());
    binary_write(stream,T.departure_time().minutes());

    binary_write(stream,T.arrival_date().day());
    binary_write(stream,T.arrival_date().month());
    binary_write(stream,T.arrival_date().year());

    binary_write(stream,T.arrival_time().hours());
    binary_write(stream,T.arrival_time().minutes());

    binary_write(stream,T.popularity_rate());
}