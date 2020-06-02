//
// Created by oleksii on 19.09.19.
//

#include "object.h"
#include "exceptions.h"
#include <algorithm>
#include <iostream>
#include <iomanip>


const double pi = 3.141592653589;


std::ostream& operator<<(std::ostream& os, const Shape& S){
    S.print(os);
    return os;
}


Plain::Plain(std::function<double(double, double)> func,
        double x1, double x2, double y1, double y2) : characteristicFunction(std::move(func)),
        x1(x1), x2(x2), y1(y1), y2(y2){}


double Plain::volume(int amountOfParts) const {
    double volume = 0;

    if (x1 > x2 || y1 > y2) throw FunctionError("Invalid borders");

    for (int i = 1; i <= amountOfParts; ++i){
        double y_i = y1 + i*(y2-y1)/amountOfParts;
        for (int j = 1; j <= amountOfParts; ++j){
            double temp = characteristicFunction(x1 + (x2-x1) * j/amountOfParts, y_i);
            if (temp < 0) throw FunctionError("Characteristic function cannot be negative");
            volume += temp * (x2-x1)/amountOfParts;
        }
    }
    volume *= (y2 - y1)/amountOfParts;

    return volume;
}


double Plain::apply(std::vector<double> args) const {
    if (args.size() != 2) throw FunctionError("Invalid amount of arguments");
    return characteristicFunction(args[0], args[1]);
}


std::vector<double> Plain::borders() const {
    return {x1, x2, y1, y2};
}


void Plain::print(std::ostream &os) const {
    os << *this;
}


std::ostream& operator<<(std::ostream& os, const Plain& P){
    std::vector<double> borders(P.borders());
    os << "Borders : x from " << borders[0] << " to " << borders[1]
     << "\n          y from " << borders[2] << " to " << borders[3];
    os <<  "\nPoints:\n";


    for (int i = 0; i <= 10; ++i){
        for (int j = 0; j <= 10; ++j){
            os << "(" << std::setw(3) << borders[0] + i * (borders[1] - borders[0])/10 <<  ", ";
            os << std::setw(3) << borders[2] + j * (borders[3] - borders[2])/10 << ", ";
            os << std::setw(3) << P.apply(
                    {borders[0] + i * (borders[1] - borders[0])/10, borders[2] + j * (borders[3] - borders[2])/10
                    })<<  ") ";
        }
        os << std::endl;
    }

    os << "Volume: " << std::setprecision(3) << P.volume();

    return os;
}


//-------------------------------------------------------------------------------------//


Rotating::Rotating(std::function<double(double)> func, double x1, double x2) :characteristicFunction(std::move(func)),
                        x1(x1), x2(x2){}


double Rotating::volume(int amountOfParts) const {
    double volume = 0;

    if (x2 < x1) throw FunctionError("Invalid borders");

    for (int i = 1; i <= amountOfParts; ++i){
        double temp = characteristicFunction(x1 + i*(x2 - x1)/amountOfParts);
        if (temp < 0) throw FunctionError("Characteristic function cannot be negative");
        volume += temp * temp;
    }
    volume *= pi*(x2 - x1)/amountOfParts;

    return volume;
}


double Rotating::apply(std::vector<double> args) const {
    if (args.size() != 1) throw FunctionError("Invalid amount of arguments");
    return characteristicFunction(args[0]);
}


std::vector<double> Rotating::borders() const {
    return {x1, x2};
}


void Rotating::print(std::ostream &os) const {
    os << *this;
}


std::ostream& operator<<(std::ostream& os, const Rotating& R){
    std::vector<double> borders(R.borders());
    std::string line;
    os << "Borders : x from " << borders[0] << " to " << borders[1];
    os <<  "\nPoints:\n";

    for (int i = 0; i <= 10; ++i){
            os << "(" << borders[0] + i * (borders[1] - borders[0])/10 <<  ", ";
            os << R.apply({borders[0] + i * (borders[1] - borders[0])/10 })<<  ") ";
    }

    os << std::endl << "Volume: " << std::setprecision(3) << R.volume();

    return os;
}