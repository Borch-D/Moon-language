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
                if (identifier->second->value.data.arr.first) { // если это массив
                    auto it = identifier->second;
                    it++;
                    for (int i = 1; i < identifier->second->value.data.size_arr; i++) {
                        value_table.push_back({it->value, 0});
                        it++;
                    }
                }
                break;
            }
            case IDENTIFIER: {
                identifier = variable_table.find(*(instruction.value->token_value));
                if (identifier == variable_table.end()) {
                    variable_table.emplace(*(instruction.value->token_value), value_table.end());
                    identifier = variable_table.find(*(instruction.value->token_value));
                }
                break;
            }
            case ASSIGMENT: {
                if (identifier->second != value_table.end()) {
                    identifier->second->count_link--;
                    if (identifier->second->count_link == 0) {
                        auto it = identifier->second;
                        if (identifier->second->value.data.arr.first) { // если массив
                            for (int i = 0; i < it->value.data.size_arr - 1; i++) {
                                auto prev = it;
                                it++;
                                value_table.erase(prev);
                            }
                        }
                        value_table.erase(it);
                    }
                }
                auto last = value_table.end();
                last--;
                if (last->value.data.arr.second) {
                    for (int i = last->value.data.size_arr; i > 1; i--) {
                        last--;
                    }
                }
                identifier->second = last;
                identifier->second->count_link++;
                break;
            }
            case SUM: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;

                if (first->value.data.arr.second) { // если массив первый
                    first--;
                    for (int i = 0; i < first->value.data.size_arr - 2; i++) {
                        first->value += second->value;
                        first--;
                    }
                    value_table.pop_back();
                } else if (second->value.data.arr.second) { // если массив второй
                    for (int i = 0; i < second->value.data.size_arr - 1; i++) {
                        first--;
                    }
                    second--;
                    for (int i = 0; i < second->value.data.size_arr - 2; i++) {
                        first->value += second->value;
                        second--;
                        value_table.pop_back();
                    }
                    value_table.pop_back();
                    value_table.pop_back();
                } else {
                    first->value += second->value;
                    value_table.pop_back();
                }
                break;
            }
            case SUB: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;

                if (first->value.data.arr.second) { // если массив первый
                    first--;
                    for (int i = 0; i < first->value.data.size_arr - 2; i++) {
                        first->value -= second->value;
                        first--;
                    }
                    value_table.pop_back();
                } else if (second->value.data.arr.second) { // если массив второй
                    for (int i = 0; i < second->value.data.size_arr - 1; i++) {
                        first--;
                    }
                    second--;
                    for (int i = 0; i < second->value.data.size_arr - 2; i++) {
                        first->value -= second->value;
                        second--;
                        value_table.pop_back();
                    }
                    value_table.pop_back();
                    value_table.pop_back();
                } else {
                    first->value -= second->value;
                    value_table.pop_back();
                }
                break;
            }
            case MULTIPLY: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;

                if (first->value.data.arr.second) { // если массив первый
                    first--;
                    for (int i = 0; i < first->value.data.size_arr - 2; i++) {
                        first->value *= second->value;
                        first--;
                    }
                    value_table.pop_back();
                } else if (second->value.data.arr.second) { // если массив второй
                    for (int i = 0; i < second->value.data.size_arr - 1; i++) {
                        first--;
                    }
                    second--;
                    for (int i = 0; i < second->value.data.size_arr - 2; i++) {
                        first->value *= second->value;
                        second--;
                        value_table.pop_back();
                    }
                    value_table.pop_back();
                    value_table.pop_back();
                } else {
                    first->value *= second->value;
                    value_table.pop_back();
                }
                break;
            }
            case DIV: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;

                if (first->value.data.arr.second) { // если массив первый
                    first--;
                    for (int i = 0; i < first->value.data.size_arr - 2; i++) {
                        first->value /= second->value;
                        first--;
                    }
                    value_table.pop_back();
                } else if (second->value.data.arr.second) { // если массив второй
                    for (int i = 0; i < second->value.data.size_arr - 1; i++) {
                        first--;
                    }
                    second--;
                    for (int i = 0; i < second->value.data.size_arr - 2; i++) {
                        first->value /= second->value;
                        second--;
                        value_table.pop_back();
                    }
                    value_table.pop_back();
                    value_table.pop_back();
                } else {
                    first->value /= second->value;
                    value_table.pop_back();
                }
                break;
            }
            case LOGICAL_SUM: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;

                if (first->value.data.arr.second) { // если массив первый
                    first--;
                    for (int i = 0; i < first->value.data.size_arr - 2; i++) {
                        first->value | second->value;
                        first--;
                    }
                    value_table.pop_back();
                } else if (second->value.data.arr.second) { // если массив второй
                    for (int i = 0; i < second->value.data.size_arr - 1; i++) {
                        first--;
                    }
                    second--;
                    for (int i = 0; i < second->value.data.size_arr - 2; i++) {
                        first->value | second->value;
                        second--;
                        value_table.pop_back();
                    }
                    value_table.pop_back();
                    value_table.pop_back();
                } else {
                    first->value | second->value;
                    value_table.pop_back();
                }
                break;
            }
            case LOGICAL_MULTIPLY: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;

                if (first->value.data.arr.second) { // если массив первый
                    first--;
                    for (int i = 0; i < first->value.data.size_arr - 2; i++) {
                        first->value & second->value;
                        first--;
                    }
                    value_table.pop_back();
                } else if (second->value.data.arr.second) { // если массив второй
                    for (int i = 0; i < second->value.data.size_arr - 1; i++) {
                        first--;
                    }
                    second--;
                    for (int i = 0; i < second->value.data.size_arr - 2; i++) {
                        first->value & second->value;
                        second--;
                        value_table.pop_back();
                    }
                    value_table.pop_back();
                    value_table.pop_back();
                } else {
                    first->value & second->value;
                    value_table.pop_back();
                }
                break;
            }
            case COMPARE_LESS: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;

                if (first->value.data.arr.second) { // если массив первый
                    first--;
                    for (int i = 0; i < first->value.data.size_arr - 2; i++) {
                        if (!(first->value < second->value)) {
                            return false;
                        }
                        first--;
                    }
                    value_table.pop_back();
                } else if (second->value.data.arr.second) { // если массив второй
                    for (int i = 0; i < second->value.data.size_arr - 1; i++) {
                        first--;
                    }
                    second--;
                    for (int i = 0; i < second->value.data.size_arr - 2; i++) {
                        if (!(first->value < second->value)) {
                            return false;
                        }
                        second--;
                        value_table.pop_back();
                    }
                    value_table.pop_back();
                    value_table.pop_back();
                } else {
                    if (!(first->value < second->value)) {
                        return false;
                    }
                    value_table.pop_back();
                }
                break;
            }
            case COMPARE_LESS_EQUAL: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;

                if (first->value.data.arr.second) { // если массив первый
                    first--;
                    for (int i = 0; i < first->value.data.size_arr - 2; i++) {
                        if (!(first->value <= second->value)) {
                            return false;
                        }
                        first--;
                    }
                    value_table.pop_back();
                } else if (second->value.data.arr.second) { // если массив второй
                    for (int i = 0; i < second->value.data.size_arr - 1; i++) {
                        first--;
                    }
                    second--;
                    for (int i = 0; i < second->value.data.size_arr - 2; i++) {
                        if (!(first->value <= second->value)) {
                            return false;
                        }
                        second--;
                        value_table.pop_back();
                    }
                    value_table.pop_back();
                    value_table.pop_back();
                } else {
                    if (!(first->value <= second->value)) {
                        return false;
                    }
                    value_table.pop_back();
                }
                break;
            }
            case COMPARE_MORE: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;

                if (first->value.data.arr.second) { // если массив первый
                    first--;
                    for (int i = 0; i < first->value.data.size_arr - 2; i++) {
                        if (!(first->value > second->value)) {
                            return false;
                        }
                        first--;
                    }
                    value_table.pop_back();
                } else if (second->value.data.arr.second) { // если массив второй
                    for (int i = 0; i < second->value.data.size_arr - 1; i++) {
                        first--;
                    }
                    second--;
                    for (int i = 0; i < second->value.data.size_arr - 2; i++) {
                        if (!(first->value > second->value)) {
                            return false;
                        }
                        second--;
                        value_table.pop_back();
                    }
                    value_table.pop_back();
                    value_table.pop_back();
                } else {
                    if (!(first->value > second->value)) {
                        return false;
                    }
                    value_table.pop_back();
                }
                break;
            }
            case COMPARE_MORE_EQUAL: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;

                if (first->value.data.arr.second) { // если массив первый
                    first--;
                    for (int i = 0; i < first->value.data.size_arr - 2; i++) {
                        if (!(first->value >= second->value)) {
                            return false;
                        }
                        first--;
                    }
                    value_table.pop_back();
                } else if (second->value.data.arr.second) { // если массив второй
                    for (int i = 0; i < second->value.data.size_arr - 1; i++) {
                        first--;
                    }
                    second--;
                    for (int i = 0; i < second->value.data.size_arr - 2; i++) {
                        if (!(first->value >= second->value)) {
                            return false;
                        }
                        second--;
                        value_table.pop_back();
                    }
                    value_table.pop_back();
                    value_table.pop_back();
                } else {
                    if (!(first->value >= second->value)) {
                        return false;
                    }
                    value_table.pop_back();
                }
                break;
            }
            case COMPARE_EQUAL: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;

                if (first->value.data.arr.second) { // если массив первый
                    first--;
                    for (int i = 0; i < first->value.data.size_arr - 2; i++) {
                        if (!(first->value == second->value)) {
                            return false;
                        }
                        first--;
                    }
                    value_table.pop_back();
                } else if (second->value.data.arr.second) { // если массив второй
                    for (int i = 0; i < second->value.data.size_arr - 1; i++) {
                        first--;
                    }
                    second--;
                    for (int i = 0; i < second->value.data.size_arr - 2; i++) {
                        if (!(first->value == second->value)) {
                            return false;
                        }
                        second--;
                        value_table.pop_back();
                    }
                    value_table.pop_back();
                    value_table.pop_back();
                } else {
                    if (!(first->value == second->value)) {
                        return false;
                    }
                    value_table.pop_back();
                }
                break;
            }
            case COMPARE_NOT_EQUAL: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;

                if (first->value.data.arr.second) { // если массив первый
                    first--;
                    for (int i = 0; i < first->value.data.size_arr - 2; i++) {
                        if (!(first->value != second->value)) {
                            return false;
                        }
                        first--;
                    }
                    value_table.pop_back();
                } else if (second->value.data.arr.second) { // если массив второй
                    for (int i = 0; i < second->value.data.size_arr - 1; i++) {
                        first--;
                    }
                    second--;
                    for (int i = 0; i < second->value.data.size_arr - 2; i++) {
                        if (!(first->value != second->value)) {
                            return false;
                        }
                        second--;
                        value_table.pop_back();
                    }
                    value_table.pop_back();
                    value_table.pop_back();
                } else {
                    if (!(first->value != second->value)) {
                        return false;
                    }
                    value_table.pop_back();
                }
                break;
            }
            case OPEN_ARR: {
                value_table_t val;
                val.value.data.arr.first = true;
                val.count_link = 0;
                value_table.push_back(val);
                break;
            }
            case CLOSE_ARR: {
                auto it = value_table.end();
                int count = 1;
                while (!(it->value.data.arr.first)) {
                    count++;
                    it--;
                }
                it->value.data.size_arr = count;
                value_table_t val;
                val.value.data.arr.second = true;
                val.value.data.size_arr = count;
                value_table.push_back(val);
                break;
            }
            default:
                return false;
        }
    }
    for (auto a : value_table) {
        std::cout << a.value.data.val_int << std::endl;
    }
    return true;
}

value_t cast_to_type(token_t t) {
    value_t result_value{};
    switch (t.token_key) {
        case INT_TOKEN: {
            result_value.data.val_int = std::stoi(*(t.token_value));
            result_value.data.size_arr = 0;
            result_value.type = INT_TOKEN;
            return result_value;
        }
        case FLOAT_TOKEN: {
            result_value.data.val_float = std::stof(*(t.token_value));
            result_value.data.size_arr = 0;
            result_value.type = FLOAT_TOKEN;
            return result_value;
        }
        case STRING_TOKEN: {
            result_value.data.val_string = *(t.token_value);
            result_value.data.val_string.erase(0, 1);
            result_value.data.val_string.erase(result_value.data.val_string.size() - 1);
            result_value.data.size_arr = 0;
            result_value.type = STRING_TOKEN;
            return result_value;
        }
        case BOOL_TOKEN: {
            if (*(t.token_value) == "true") {
                result_value.data.val_bool = true;
            } else {
                result_value.data.val_bool = false;
            }
            result_value.data.size_arr = 0;
            result_value.type = BOOL_TOKEN;
            return result_value;
        }
        default:
            break;
    }
}
