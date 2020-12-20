#include "lexer.h"

bool create_token_table(const std::vector<std::string> &words, std::vector<token_t> &token_table) {
    if (words.empty()) {
        std::cout << "File is empty!" << std::endl;
        return false;
    }

    std::map<std::string, token> sign;
    sign.emplace("+", PLUS_TOKEN);
    sign.emplace("-", MINUS_TOKEN);
    sign.emplace("*", MULTIPLY_TOKEN);
    sign.emplace("/", DIV_TOKEN);
    sign.emplace("=", ASSIGN_TOKEN);
    sign.emplace("(", L_BRACKET_TOKEN);
    sign.emplace(")", R_BRACKET_TOKEN);
    sign.emplace("\n", ENDL_TOKEN);
    sign.emplace("<", LESS_TOKEN);
    sign.emplace("<=", LESS_EQUAL_TOKEN);
    sign.emplace(">", MORE_TOKEN);
    sign.emplace(">=", MORE_EQUAL_TOKEN);
    sign.emplace("==", EQUAL_TOKEN);
    sign.emplace("!=", NOT_EQUAL_TOKEN);
    sign.emplace("&", LOGICAL_AND_TOKEN);
    sign.emplace("|", LOGICAL_OR_TOKEN);
    sign.emplace("true", BOOL_TOKEN);
    sign.emplace("false", BOOL_TOKEN);
    sign.emplace("[", L_S_BRACKET_TOKEN);
    sign.emplace("]", R_S_BRACKET_TOKEN);
    sign.emplace(",", COMMA_TOKEN);
    sign.emplace("if", IF_TOKEN);
    sign.emplace("else", ELSE_TOKEN);
    sign.emplace("{", L_F_BRACKET_TOKEN);
    sign.emplace("}", R_F_BRACKET_TOKEN);
    sign.emplace("while", WHILE_TOKEN);
    // sign.emplace("?", QUESTION_TOKEN);
    // sign.emplace(":", COLON_TOKEN);
    const val_name_state_t valNameState[3][5] = {
            //               LETTER            ZERO            NUMERAL           UNDERSCORE           DOT

            /* LETTER */     {LETTER_VAL_NAME, ERROR_VAL_NAME, ERROR_VAL_NAME,   UNDERSCORE_VAL_NAME, ERROR_VAL_NAME,},

            /* NUMERAL */
                             {ERROR_VAL_NAME,  ERROR_VAL_NAME, NUMERAL_VAL_NAME, UNDERSCORE_VAL_NAME, ERROR_VAL_NAME,},

            /* UNDERSCORE */
                             {LETTER_VAL_NAME, ERROR_VAL_NAME, NUMERAL_VAL_NAME, UNDERSCORE_VAL_NAME, ERROR_VAL_NAME,}
    };
    const number_state_t numberState[5][5] = {
            //              LETTER        ZERO                       NUMERAL                    UNDERSCORE    DOT

            /* BEGIN */    {ERROR_NUMBER, ZERO_BEGIN,                NUMERAL_BASIC_NUMBER,      ERROR_NUMBER, ERROR_NUMBER},

            /*ZERO_BEGIN*/
                           {ERROR_NUMBER, ERROR_NUMBER,              ERROR_NUMBER,              ERROR_NUMBER, DOT_NUMBER},

            /*NUMERAL_B*/
                           {ERROR_NUMBER, NUMERAL_BASIC_NUMBER,      NUMERAL_BASIC_NUMBER,      ERROR_NUMBER, DOT_NUMBER},

            /* DOT */
                           {ERROR_NUMBER, NUMERAL_FRACTIONAL_NUMBER, NUMERAL_FRACTIONAL_NUMBER, ERROR_NUMBER, ERROR_NUMBER},

            /*NUMERAL_F*/
                           {ERROR_NUMBER, NUMERAL_FRACTIONAL_NUMBER, NUMERAL_FRACTIONAL_NUMBER, ERROR_NUMBER, ERROR_NUMBER}
    };

    for (const std::string &word : words) {
        auto find_token = sign.find(word);
        if (find_token != sign.end()) {
            token_table.push_back({find_token->second, &word});
            continue;
        }
        if (word[0] == '"' && word[word.size() - 1] == '"') {
            token_table.push_back({STRING_TOKEN, &word});
            continue;
        }
        token current_token = get_token(word, valNameState, numberState);
        if (current_token == ERROR_TOKEN) {
            std::cout << "What is a " << word << " ?" << std::endl;
            return false;
        }
        token_table.push_back({current_token, &word});
    }
    delete_extra_bracket(token_table);
    return true;
}

token get_token(const std::string &word, const val_name_state_t valNameState[3][5],
                const number_state_t numberState[5][5]) {
    if (word.empty()) {
        return ERROR_TOKEN;
    }
    lexeme_t lexeme = get_lexeme(word[0]);

    if (lexeme == LETTER_LEXEME) {
        val_name_state_t val_name_state = LETTER_VAL_NAME;
        int i = 1;
        while (i < word.size() && val_name_state != ERROR_VAL_NAME) {
            lexeme = get_lexeme(word[i]);
            if (lexeme == ERROR_LEXEME) {
                return ERROR_TOKEN;
            }
            val_name_state = valNameState[val_name_state][lexeme];
            i++;
        }
        if (val_name_state == ERROR_VAL_NAME) {
            return ERROR_TOKEN;
        } else {
            return VAL_NAME_TOKEN;
        }
    } else if (lexeme == ZERO_LEXEME || lexeme == NUMERAL_LEXEME) {
        number_state_t number_state = BEGIN_NUMBER;
        bool flag_float = false;
        int i = 0;
        while (i < word.size() && number_state != ERROR_NUMBER) {
            lexeme = get_lexeme(word[i]);
            if (lexeme == ERROR_LEXEME) {
                return ERROR_TOKEN;
            }
            number_state = numberState[number_state][lexeme];
            if (number_state == DOT_NUMBER) {
                flag_float = true;
            }
            i++;
        }
        if (number_state == ERROR_NUMBER || number_state == DOT_NUMBER) {
            return ERROR_TOKEN;
        } else if (flag_float) {
            return FLOAT_TOKEN;
        } else {
            return INT_TOKEN;
        }
    } else {
        return ERROR_TOKEN;
    }
}

lexeme_t get_lexeme(char symbol) {
    if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z')) {
        return LETTER_LEXEME;
    } else if (symbol == '0') {
        return ZERO_LEXEME;
    } else if (symbol >= '1' && symbol <= '9') {
        return NUMERAL_LEXEME;
    } else if (symbol == '_') {
        return UNDERSCORE_LEXEME;
    } else if (symbol == '.') {
        return DOT_LEXEME;
    } else {
        return ERROR_LEXEME;
    }
}

void delete_extra_bracket(std::vector<token_t> &token_table) {
    auto it = token_table.begin();
    int start = 0;
    int end = 0;
    while (it != token_table.end()) {
        if (it->token_key == L_S_BRACKET_TOKEN) {
            start++;
            if (start - end >= 2) {
                token_table.erase(it);
                continue;
            }
        } else if (it->token_key == R_S_BRACKET_TOKEN) {
            end++;
            if (start > end) {
                token_table.erase(it);
                continue;
            }
        }
        it++;
    }
}

void write_token_table(const std::vector<token_t> &token_table) {
    if (token_table.empty()) {
        std::cout << "Token table is empty!" << std::endl;
        return;
    }
    for (token_t t : token_table) {
        switch (t.token_key) {
            case 0: {
                std::cout << "PLUS" << ' ';
                break;
            }
            case 1: {
                std::cout << "MINUS" << ' ';
                break;
            }
            case 2: {
                std::cout << "MULTIPLY" << ' ';
                break;
            }
            case 3: {
                std::cout << "DIV" << ' ';
                break;
            }
            case 4: {
                std::cout << "ASSIGN" << ' ';
                break;
            }
            case 5: {
                std::cout << "VAL_NAME" << ' ';
                break;
            }
            case 6: {
                std::cout << "INT" << ' ';
                break;
            }
            case 7: {
                std::cout << "FLOAT" << ' ';
                break;
            }
            case 8: {
                std::cout << "L_BRACKET" << ' ';
                break;
            }
            case 9: {
                std::cout << "R_BRACKET" << ' ';
                break;
            }
            case 10: {
                std::cout << "ENDL" << std::endl;
                break;
            }
            case 11: {
                std::cout << "STRING" << ' ';
                break;
            }
            case 12: {
                std::cout << "LESS" << ' ';
                break;
            }
            case 13: {
                std::cout << "LESS_EQUAL" << ' ';
                break;
            }
            case 14: {
                std::cout << "MORE" << ' ';
                break;
            }
            case 15: {
                std::cout << "MORE_EQUAL" << ' ';
                break;
            }
            case 16: {
                std::cout << "EQUAL" << ' ';
                break;
            }
            case 17: {
                std::cout << "NOT_EQUAL" << ' ';
                break;
            }
            case 18: {
                std::cout << "LOGICAL_AND" << ' ';
                break;
            }
            case 19: {
                std::cout << "LOGICAL_OR" << ' ';
                break;
            }
            case 20: {
                std::cout << "BOOL" << ' ';
                break;
            }
            case 21: {
                std::cout << "L_S_BRACKET" << ' ';
                break;
            }
            case 22: {
                std::cout << "R_S_BRACKET" << ' ';
                break;
            }
            case 23: {
                std::cout << "COMMA" << ' ';
                break;
            }
            case 24: {
                std::cout << "IF" << ' ';
                break;
            }
            case 25: {
                std::cout << "ELSE" << ' ';
                break;
            }
            case 26: {
                std::cout << "L_F_BRACKET" << ' ';
                break;
            }
            case 27: {
                std::cout << "R_F_BRACKET" << ' ';
                break;
            }
            case 28: {
                std::cout << "WHILE" << ' ';
                break;
            }
            default:
                break;
        }
    }
}
