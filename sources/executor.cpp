#include "executor.h"

bool executor(std::vector<byte_code_t> &byte_code) {
    if (byte_code.empty()) {
        std::cout << "Byte code is empty!" << std::endl;
        return false;
    }

    std::map<std::string, std::list<value_table_t>::iterator> variable_table;
    std::list<value_table_t> value_table;
    std::map<std::string, std::list<value_table_t>::iterator>::iterator identifier;

    for (auto instruction : byte_code) {
        switch (instruction.command) {
            case PUSH_C: {
                value_t val = cast_to_type(*(instruction.value));
                value_table.push_back({val, 0});
                break;
            }
            case PUSH_V: {
                value_table.push_back({identifier->second->value, 0});
                break;
            }
            case IDENTIFIER: {
                identifier = variable_table.find(*(instruction.value->token_value));
                break;
            }
            case ASSIGMENT: {
                identifier->second->count_link--;
                if (identifier->second->count_link == 0) {
                    value_table.erase(identifier->second);
                }
                identifier->second = value_table.end();
                identifier->second->count_link++;
                break;
            }
            case SUM: {
                auto res = value_table.end();
                res--;
                res->value += value_table.end()->value;
                value_table.pop_back();
                break;
            }
            case SUB: {
                auto res = value_table.end();
                res--;
                res->value -= value_table.end()->value;
                value_table.pop_back();
                break;
            }
            case MULTIPLY: {
                auto res = value_table.end();
                res--;
                res->value *= value_table.end()->value;
                value_table.pop_back();
                break;
            }
            case DIV: {
                auto res = value_table.end();
                res--;
                res->value /= value_table.end()->value;
                value_table.pop_back();
                break;
            }
        }
    }
}

value_t cast_to_type(token_t t) {
    value_t result_value{};
    switch (t.token_key) {
        case INT_TOKEN: {
            result_value.data.val_int = std::stoi(*(t.token_value));
            result_value.type = INT_TOKEN;
            return result_value;
        }
        case FLOAT_TOKEN: {
            result_value.data.val_float = std::stof(*(t.token_value));
            result_value.type = FLOAT_TOKEN;
            return result_value;
        }
    }
}

void value_t::operator+=(const value_t &rhs) {
    if (this->type == FLOAT_TOKEN || rhs.type == FLOAT_TOKEN) {
        this->data.val_float = static_cast<float>(this->data.val_int);
        this->data.val_float += static_cast<float>(rhs.data.val_int);
        this->type = FLOAT_TOKEN;
    } else {
        this->data.val_int += rhs.data.val_int;
    }
}

void value_t::operator-=(const value_t &rhs) {
    if (this->type == FLOAT_TOKEN || rhs.type == FLOAT_TOKEN) {
        this->data.val_float = static_cast<float>(this->data.val_int);
        this->data.val_float -= static_cast<float>(rhs.data.val_int);
        this->type = FLOAT_TOKEN;
    } else {
        this->data.val_int -= rhs.data.val_int;
    }
}

void value_t::operator*=(const value_t &rhs) {
    if (this->type == FLOAT_TOKEN || rhs.type == FLOAT_TOKEN) {
        this->data.val_float = static_cast<float>(this->data.val_int);
        this->data.val_float *= static_cast<float>(rhs.data.val_int);
        this->type = FLOAT_TOKEN;
    } else {
        this->data.val_int *= rhs.data.val_int;
    }
}

void value_t::operator/=(const value_t &rhs) {
    if (this->type == FLOAT_TOKEN || rhs.type == FLOAT_TOKEN) {
        this->data.val_float = static_cast<float>(this->data.val_int);
        this->data.val_float /= static_cast<float>(rhs.data.val_int);
        this->type = FLOAT_TOKEN;
    } else {
        this->data.val_int /= rhs.data.val_int;
    }
}
