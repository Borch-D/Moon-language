//
// Created by dmitriy on 03.12.2020.
//

#ifndef MOON_COMMAND_H
#define MOON_COMMAND_H

enum command_t {
    PUSH_C = 0,
    PUSH_V,
    IDENTIFIER,
    ASSIGMENT,
    SUM,
    SUB,
    MULTIPLY,
    DIV,
    LOGICAL_SUM,
    LOGICAL_MULTIPLY,
    COMPARE_LESS,
    COMPARE_LESS_EQUAL,
    COMPARE_MORE,
    COMPARE_MORE_EQUAL,
    COMPARE_EQUAL,
    COMPARE_NOT_EQUAL,
    OPEN_ARR,
    CLOSE_ARR
};

#endif //MOON_COMMAND_H
