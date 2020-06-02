//
// Created by oleksii on 23.09.19.
//

#include "exceptions.h"


ConnectedError::ConnectedError(const char* error) : msg(error) {}


const char* ConnectedError::what() {
    return msg;
}


FunctionError::FunctionError(const char* error) : msg(error) {}


const char* FunctionError::what() {
    return msg;
}