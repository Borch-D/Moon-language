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
                if (identifier == variable_table.end()) {
                    variable_table.emplace(*(instruction.value->token_value), value_table.end()); // поправить
                    identifier = variable_table.find(*(instruction.value->token_value));
                }
                break;
            }
            case ASSIGMENT: {
                if (identifier->second != value_table.end()) {
                    identifier->second->count_link--;
                    if (identifier->second->count_link == 0) {
                        value_table.erase(identifier->second);
                    }
                }
                auto last = value_table.end();
                last--;
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
                first->value += second->value;
                value_table.pop_back();
                break;
            }
            case SUB: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;
                first->value -= second->value;
                value_table.pop_back();
                break;
            }
            case MULTIPLY: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;
                first->value *= second->value;
                value_table.pop_back();
                break;
            }
            case DIV: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;
                first->value /= second->value;
                value_table.pop_back();
                break;
            }
            case LOGICAL_SUM: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;
                first->value | second->value;
                value_table.pop_back();
                break;
            }
            case LOGICAL_MULTIPLY: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;
                first->value & second->value;
                value_table.pop_back();
                break;
            }
            case COMPARE_LESS: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;
                if (!(first->value < second->value)) {
                    return false;
                }
                value_table.pop_back();
                break;
            }
            case COMPARE_LESS_EQUAL: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;
                if (!(first->value <= second->value)) {
                    return false;
                }
                value_table.pop_back();
                break;
            }
            case COMPARE_MORE: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;
                if (!(first->value > second->value)) {
                    return false;
                }
                value_table.pop_back();
                break;
            }
            case COMPARE_MORE_EQUAL: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;
                if (!(first->value >= second->value)) {
                    return false;
                }
                value_table.pop_back();
                break;
            }
            case COMPARE_EQUAL: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;
                if (!(first->value == second->value)) {
                    return false;
                }
                value_table.pop_back();
                break;
            }
            case COMPARE_NOT_EQUAL: {
                auto first = value_table.end();
                auto second = value_table.end();
                first--;
                first--;
                second--;
                if (!(first->value != second->value)) {
                    return false;
                }
                value_table.pop_back();
                break;
            }
            default:
                return false;
        }
    }
    return true;
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
        case STRING_TOKEN: {
            result_value.data.val_string = *(t.token_value);
            result_value.data.val_string.erase(0, 1);
            result_value.data.val_string.erase(result_value.data.val_string.size() - 1);
            result_value.type = STRING_TOKEN;
            return result_value;
        }
        case BOOL_TOKEN: {
            if (*(t.token_value) == "true") {
                result_value.data.val_bool = true;
            } else {
                result_value.data.val_bool = false;
            }
            result_value.type = BOOL_TOKEN;
            return result_value;
        }
        default:
            break;
    }
}
