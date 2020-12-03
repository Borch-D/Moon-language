#include "text_split_by_words.h"
#include "lexer.h"
#include "parser.h"

int main(int argc, char* argv[])
{

    if (argc != 2) {
        std::cout << "Input file name or path to file!" << std::endl;
        return 0;
    }

    std::vector<std::string> words;
    std::string file_name(argv[1]);
    text_split_by_words(file_name, words);
    for (auto w : words) {
        std::cout << w;
    }
    std::vector<token_t> token_table;
    if (!create_token_table(words, token_table)) {
        std::cout << "Error in creation token table!" << std::endl;
        return 0;
    }
    write_token_table(token_table);
    std::vector<byte_code_t> byte_code;
    if (!parse(token_table, byte_code)) {
        return 0;
    }
    write_byte_code(byte_code);
    return 0;
}
