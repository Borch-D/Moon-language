//
// Created by dmitriy on 03.12.2020.
//

#ifndef MOON_BYTE_CODE_H
#define MOON_BYTE_CODE_H

#endif //MOON_BYTE_CODE_H

#include "command.h"
#include "token.h"

struct byte_code_t {
    command_t command;
    const token_t *value;
};
