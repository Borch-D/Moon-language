#include "lexer.h"

void text_split_by_words(const std::string &file_name, std::vector<std::string> &words) {
    std::vector<char> separators = {'=', '+', '-', '/', '*', '\n'/*, '?', ':'*/};
    std::ifstream file;
    file.open(file_name, std::ios::in);

    if (!(file.is_open())) {
        std::cout << "File not found!" << std::endl;
        return;
    }

    char symbol = 0;
    bool flag_begin_word = false;

    while ((symbol = file.get()) != EOF) {
        if (symbol == ' ') {
            flag_begin_word = false;
            continue;
        } else if (std::find(separators.begin(), separators.end(), symbol) != separators.end()) {
            words.emplace_back(1, symbol);
            flag_begin_word = false;
        } else if (!flag_begin_word) {
            words.emplace_back();
            *(words.end() - 1) += symbol;
            flag_begin_word = true;
        } else {
            *(words.end() - 1) += symbol;
        }
    }
    if (!words.empty()) {
        words.emplace_back(1, '\n');
    }
    file.close();
}

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
    sign.emplace("\n", ENDL_TOKEN);
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
        token current_token = get_token(word, valNameState, numberState);
        if (current_token == ERROR_TOKEN) {
            std::cout << "What is a " << word << " ?" << std::endl;
            return false;
        }
        token_table.push_back({current_token, &word});
    }
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
                std::cout << "ENDL" << std::endl;
                break;
            }
            default:
                break;
        }
    }
}
