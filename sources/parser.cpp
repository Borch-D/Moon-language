#include "parser.h"

bool parse(const std::vector<token_t> &token_table, std::vector<byte_code_t> &byte_code) {
    if (token_table.empty()) {
        std::cout << "Token table is empty!" << std::endl;
        return false;
    }
    main_value_t mainValue = {&token_table, &byte_code};

    auto it = token_table.begin();
    while (it != token_table.end()) {
        if (it->token_key != ENDL_TOKEN) {
            if (!operations(it, &mainValue)) {
                std::cout << "Parse error!" << std::endl;
                return false;
            }
        }
        it++;
    }
    return true;
}

bool operations(std::vector<token_t>::const_iterator &begin_operation, main_value_t *mainValue) {
    if (begin_operation->token_key == VAL_NAME_TOKEN && (++begin_operation)->token_key == ASSIGN_TOKEN) {
        // если это присваивание
        begin_operation++;
        auto end_operation = std::find_if(begin_operation, mainValue->token_table->end(), isEndl);
        if (expression(begin_operation, end_operation, mainValue)) {
            mainValue->byte_code->push_back({IDENTIFIER, &*(begin_operation-2)});
            mainValue->byte_code->push_back({ASSIGMENT});
            mainValue->val_name.emplace(*((begin_operation-2)->token_value));
            begin_operation = end_operation;
            return true;
        }
    }
    return false;
}

void write_byte_code(std::vector<byte_code_t> &byte_code) {
    if (byte_code.empty()) {
        std::cout << "Byte code is empty!" << std::endl;
        return;
    }
    for (auto i : byte_code) {
        switch (i.command) {
            case 0: {
                std::cout << "PUSH_C " << *(i.value->token_value) << std::endl;
                break;
            }
            case 1: {
                std::cout << "PUSH_V" << std::endl;
                break;
            }
            case 2: {
                std::cout << "IDENTIFIER " << *(i.value->token_value) << std::endl;
                break;
            }
            case 3: {
                std::cout << "ASSIGMENT" << std::endl;
                break;
            }
            case 4: {
                std::cout << "SUM" << std::endl;
                break;
            }
            case 5: {
                std::cout << "SUB" << std::endl;
                break;
            }
            case 6: {
                std::cout << "MULTIPLY" << std::endl;
                break;
            }
            case 7: {
                std::cout << "DIV" << std::endl;
                break;
            }
        }
    }
}
