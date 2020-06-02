#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

const std::string alphabet = "abcdefghijklmnopqrstuvwxys";

enum class Train_type{international = 0, fast = 1, normal = 2, regional = 3};

const std::vector<Train_type> Train_Types = {Train_type ::international,
                                             Train_type ::fast,
                                             Train_type ::normal,
                                             Train_type ::regional};

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

    Time& operator=(const Time& rhs){
        Minutes = rhs.minutes();
        Hours = rhs.hours();
        return *this;
    }


    int minutes() const {
        return Minutes;
    }

    int hours() const {
        return Hours;
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

    Date& operator=(const Date& rhs){
        Day = rhs.day();
        Month = rhs.month();
        Year = rhs.year();
        return *this;
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

    explicit Train(
            const int data_id = 0,
            const std::string name = "No_Name",
            const int number = 0,
            const Train_type type = Train_type::normal,
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

    Train_type type() const {
        return Type;
    }

    std::string type_line() const{
        switch (type()){
            case Train_type::international : return "International";
            case Train_type::fast : return "Fast";
            case Train_type::regional : return "Regional";
        }
        return "Normal";
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

private:
    int Data_ID;
    std::string Name;
    int Number;
    Train_type Type;
    Date Departure_Date;
    Time Departure_Time;
    Date Arrival_Date;
    Time Arrival_Time;
    double Popularity_Rate;
};

std::ostream& operator<<(std::ostream& os, const Train& train){
    os << train.data_id() << ' ' << train.name() << ' ' << train.number() << ' ' << train.type_line() << ' '
       << train.departure_date() << ' ' << train.departure_time() << ' '
       << train.arrival_date()   << ' ' << train.arrival_time()   << ' '
       << train.popularity_rate();
    return os;
}

std::istream& operator>>(std::istream& is, Train& train){
    int Data_ID, Number;
    std::string Name;
    std::string Type;
    Date Departure_Date, Arrival_Date;
    Time Departure_Time, Arrival_Time;
    double Popularity_Rate;
    is >> Data_ID >> Name >> Number >> Type
       >> Departure_Date >> Departure_Time
       >> Arrival_Date >> Arrival_Time >> Popularity_Rate;

    Train_type type;

    if (Type == "International") type = Train_type::international; else
    if (Type == "Fast") type = Train_type::fast; else
    if (Type == "Regional") type = Train_type::regional; else
    if (Type == "Normal") type = Train_type::normal;


    train = Train(Data_ID,Name,Number,type,Departure_Date,Departure_Time,Arrival_Date,Arrival_Time,Popularity_Rate);
    return is;
}

template <class T>
T GetData(const std::string&& message, const T& DataType){
    T NewData;
    std::cout << message << ": ";
    std::cin >> NewData;
    return NewData;
}

void GetTrain(std::istream& is, Train& train){
    std::cout << "Insert ";
    int Data_ID = GetData("Data ID", int());
    std::string Name = GetData("Name", std::string());
    int Number = GetData("Number", int());
    std::string Type = GetData("Type", std::string());
    Date Departure_Date = GetData("Departure date", Date());
    Time Departure_Time = GetData("Departure time", Time());
    Date Arrival_Date = GetData("Arrival Date", Date());
    Time Arrival_Time = GetData("Arrival time", Time());
    double Popularity_Rate = GetData("Popularity rate", double());

    Train_type type;

    if (Type == "International") type = Train_type::international; else
    if (Type == "Fast") type = Train_type::fast; else
    if (Type == "Regional") type = Train_type::regional; else
    if (Type == "Normal") type = Train_type::normal;

    train = Train(Data_ID,Name,Number,type,Departure_Date,Departure_Time,Arrival_Date,Arrival_Time,Popularity_Rate);
}

void PrintTrain(std::ostream& os, const Train& train){
    os << train.data_id() << ' ' << train.name() << ' ' << train.number() << ' ' << train.type_line() << ' '
       << std::endl << "On it`s way: "
       << train.departure_date() << ' ' << train.departure_time() << " - "
       << train.arrival_date()   << ' ' << train.arrival_time()   << ' '
       << std::endl << "Popularity: "  << train.popularity_rate() << std::endl;
}


int RandomInt(int begin, int end) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}

std::string RandomString(int size){
    std::string s;
    for (int i = 0; i < size; ++i){
        s += alphabet[RandomInt(0, alphabet.size() - 1)];
    }
    return s;
}

Train RandomTrain(){
    int Data_ID = RandomInt(1,100000);
    std::string Name = RandomString(10);
    int Number = RandomInt(1,9999);
    Train_type Type = Train_Types[RandomInt(0,3)];
    Date Departure_Date(RandomInt(1,31),RandomInt(1,23),RandomInt(1,2019));
    Time Departure_Time(RandomInt(0,23),RandomInt(0,59));
    Date Arrival_Date(RandomInt(1,31),RandomInt(1,12),RandomInt(1,2019));
    Time Arrival_Time(RandomInt(0,23),RandomInt(0,59));
    double Popularity_Rate = RandomInt(1,2000)/1000.;

    return Train(Data_ID,Name,Number,Type,Departure_Date,Departure_Time,Arrival_Date,Arrival_Time,Popularity_Rate);
}