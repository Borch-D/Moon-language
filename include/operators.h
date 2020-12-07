//
// Created by dmitriy on 07.12.2020.
//

#ifndef MOON_OPERATORS_H
#define MOON_OPERATORS_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <list>
#include "byte_code.h"

struct data_t {
    int val_int;
    float val_float;
    std::string val_string;
};

struct value_t {
    token type;
    data_t data;

    void operator+=(const value_t &);
    void operator-=(const value_t &);
    void operator*=(const value_t &);
    void operator/=(const value_t &);
};

#endif //MOON_OPERATORS_H
