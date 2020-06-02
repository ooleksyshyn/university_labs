//
// Created by oleksii on 23.09.19.
//

#ifndef LAB1_EXCEPTIONS_H
#define LAB1_EXCEPTIONS_H

#include <string>

class ConnectedError : public std::exception{
public:
    explicit ConnectedError(const char* errorMessage);
    const char* what();
private:
    const char* msg;
};


class FunctionError : public std::exception{
public:
    explicit FunctionError(const char*);
    const char* what();

private:
    const char* msg;
};

#endif //LAB1_EXCEPTIONS_H
