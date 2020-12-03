//
// Created by dmitriy on 03.12.2020.
//

#include "text_split_by_words.h"

void text_split_by_words(const std::string &file_name, std::vector<std::string> &words) {
    std::vector<char> separators = {'=', '+', '-', '/', '*', '(', ')', '\n'/*, '?', ':'*/};
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
