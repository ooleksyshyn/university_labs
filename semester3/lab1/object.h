//
// Created by oleksii on 19.09.19.
//

#include <vector>
#include <functional>

#ifndef LAB1SEM3_OBJECT_H
#define LAB1SEM3_OBJECT_H


class Shape {
public:
    [[nodiscard]] virtual double volume(int = 5'000) const = 0;
    [[nodiscard]] virtual double apply(std::vector<double>) const = 0;
    [[nodiscard]] virtual std::vector<double> borders() const = 0;
    virtual void print(std::ostream& os) const = 0;
};


std::ostream& operator<<(std::ostream& os, const Shape& S);


class Plain : public Shape {
public:
    explicit Plain (std::function<double(double, double)>, double = 0, double = 1, double = 0, double = 1);
    [[nodiscard]] double volume(int = 5'000) const override;
    [[nodiscard]] double apply(std::vector<double>) const override;
    [[nodiscard]] std::vector<double> borders() const override;
    void print(std::ostream& os) const override;

private:
    std::function<double(double, double)> characteristicFunction;

    double x1;
    double x2;
    double y1;
    double y2;
};


std::ostream& operator<<(std::ostream&, const Plain&);


class Rotating : public Shape {
public:
    explicit Rotating(std::function<double(double)>, double = 0, double = 1);
    [[nodiscard]] double volume(int = 5'000) const override;
    [[nodiscard]] double apply(std::vector<double>) const override;
    [[nodiscard]] std::vector<double> borders() const override;
    void print(std::ostream& os) const override;

private:
    std::function<double(double)> characteristicFunction;

    double x1;
    double x2;
};


std::ostream& operator<<(std::ostream&, const Rotating&);


/*
template<typename Strategy>
class Shape {
    //static_assert(std::is_same_v<Strategy, Plain> || std::is_same_v<Strategy, Rotating>,
      //            "Incorrect strategy requested");

public:

    explicit Shape(Strategy s) : object(s){}

    template<typename... Args>
    double volume(Args... args) const {
        return object.volume(args...);
    }

    template <typename... Args>
    double apply(Args... args){
        return object.apply(args...);
    }
    Strategy object;
};*/

#endif //LAB1SEM3_OBJECT_H
