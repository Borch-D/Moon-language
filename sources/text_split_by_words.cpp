//
// Created by dmitriy on 03.12.2020.
//

#include "text_split_by_words.h"

void text_split_by_words(const std::string &file_name, std::vector<std::string> &words) {
    std::vector<char> separators = {'=', '+', '-', '/', '*', '(', ')', '&', '|', '[', ']', ',', '{', '}',
                                    '\n'/*, '?', ':'*/};
    std::vector<char> double_separators_first = {'<', '>', '=', '!'};
    char double_separators_second = '=';

    std::ifstream file;
    file.open(file_name, std::ios::in);

    if (!(file.is_open())) {
        std::cout << "File not found!" << std::endl;
        return;
    }

    char symbol = 0;
    bool flag_begin_word = false;
    bool flag_double_separators = false;

    while ((symbol = file.get()) != EOF) {
        if (symbol == ' ') {
            flag_begin_word = false;
            flag_double_separators = false;
            continue;
        } else if (symbol == '"') {
            words.emplace_back();
            *(words.end() - 1) += '"';
            while (((symbol = file.get()) != '"') && symbol != EOF) {
                *(words.end() - 1) += symbol;
            }
            *(words.end() - 1) += '"';
            flag_begin_word = false;
            flag_double_separators = false;
        } else if (flag_double_separators && symbol == double_separators_second) {
            *(words.end() - 1) += symbol;
            flag_double_separators = false;
        } else if (std::find(double_separators_first.begin(), double_separators_first.end(), symbol) !=
                   double_separators_first.end()) {
            words.emplace_back(1, symbol);
            flag_double_separators = true;
        } else if (std::find(separators.begin(), separators.end(), symbol) != separators.end()) {
            words.emplace_back(1, symbol);
            flag_begin_word = false;
            flag_double_separators = false;
        } else if (!flag_begin_word) {
            words.emplace_back();
            *(words.end() - 1) += symbol;
            flag_begin_word = true;
            flag_double_separators = false;
        } else {
            *(words.end() - 1) += symbol;
            flag_double_separators = false;
        }
    }
    if (!words.empty()) {
        words.emplace_back(1, '\n');
    }
    file.close();
}
