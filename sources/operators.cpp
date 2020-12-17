//
// Created by dmitriy on 07.12.2020.
//

#include "operators.h"

uint8_t learn_variable(std::pair<token, token> tokens) {
    std::vector<std::pair<token, token>> variable;
    variable.emplace_back(INT_TOKEN, INT_TOKEN);
    variable.emplace_back(FLOAT_TOKEN, FLOAT_TOKEN);
    variable.emplace_back(INT_TOKEN, FLOAT_TOKEN);
    variable.emplace_back(FLOAT_TOKEN, INT_TOKEN);
    variable.emplace_back(STRING_TOKEN, STRING_TOKEN);
    variable.emplace_back(INT_TOKEN, STRING_TOKEN);
    variable.emplace_back(STRING_TOKEN, INT_TOKEN);
    variable.emplace_back(FLOAT_TOKEN, STRING_TOKEN);
    variable.emplace_back(STRING_TOKEN, FLOAT_TOKEN);
    auto it = std::find(variable.begin(), variable.end(), tokens);
    if (it == variable.end()) {
        std::cout << "Error!" << std::endl;
        return 10;
    }
    return std::distance(variable.begin(), it);
}

bool value_t::operator+=(const value_t &rhs) {
    std::pair<token, token> tokens = {this->type, rhs.type};
    uint8_t rule_number = learn_variable(tokens);
    switch (rule_number) {
        // int + int
        case 0: {
            this->data.val_int += rhs.data.val_int;
            break;
        }
            // float + float
        case 1: {
            this->data.val_float += rhs.data.val_float;
            break;
        }
            // int + float
        case 2: {
            this->data.val_float = static_cast<float>(this->data.val_int);
            this->type = FLOAT_TOKEN;
            this->data.val_float += rhs.data.val_float;
            break;
        }
            // float + int
        case 3: {
            this->data.val_float += static_cast<float>(rhs.data.val_int);
            break;
        }
            // string + string
        case 4: {
            this->data.val_string += rhs.data.val_string;
            break;
        }
            // int + string
        case 5: {
            this->data.val_string = std::to_string(this->data.val_int);
            this->type = STRING_TOKEN;
            this->data.val_string += rhs.data.val_string;
            break;
        }
            // string + int
        case 6: {
            this->data.val_string += std::to_string(rhs.data.val_int);
            break;
        }
            // float + string
        case 7: {
            this->data.val_string = std::to_string(this->data.val_float);
            this->type = STRING_TOKEN;
            this->data.val_string += rhs.data.val_string;
            break;
        }
            // string + float
        case 8: {
            this->data.val_string += std::to_string(rhs.data.val_float);
            break;
        }
        default:
            return false;
    }
    return true;
}

bool value_t::operator-=(const value_t &rhs) {
    std::pair<token, token> tokens = {this->type, rhs.type};
    uint8_t rule_number = learn_variable(tokens);
    switch (rule_number) {
        // int - int
        case 0: {
            this->data.val_int -= rhs.data.val_int;
            break;
        }
            // float - float
        case 1: {
            this->data.val_float -= rhs.data.val_float;
            break;
        }
            // int - float
        case 2: {
            this->data.val_float = static_cast<float>(this->data.val_int);
            this->type = FLOAT_TOKEN;
            this->data.val_float -= rhs.data.val_float;
            break;
        }
            // float - int
        case 3: {
            this->data.val_float -= static_cast<float>(rhs.data.val_int);
            break;
        }
            // string - string
        case 4: {
            size_t it = this->data.val_string.find(rhs.data.val_string);
            while (it != std::string::npos) {
                this->data.val_string.erase(it, rhs.data.val_string.size());
                it = this->data.val_string.find(rhs.data.val_string);
            }
            break;
        }
            // int - string
        case 5: {
            this->data.val_string = std::to_string(this->data.val_int);
            this->type = STRING_TOKEN;
            size_t it = this->data.val_string.find(rhs.data.val_string);
            while (it != std::string::npos) {
                this->data.val_string.erase(it, rhs.data.val_string.size());
                it = this->data.val_string.find(rhs.data.val_string);
            }
            break;
        }
            // string - int
        case 6: {
            size_t it = this->data.val_string.find(std::to_string(rhs.data.val_int));
            while (it != std::string::npos) {
                this->data.val_string.erase(it, std::to_string(rhs.data.val_int).size());
                it = this->data.val_string.find(std::to_string(rhs.data.val_int));
            }
            break;
        }
            // float - string
        case 7: {
            this->data.val_string = std::to_string(this->data.val_float);
            this->type = STRING_TOKEN;
            size_t it = this->data.val_string.find(rhs.data.val_string);
            while (it != std::string::npos) {
                this->data.val_string.erase(it, rhs.data.val_string.size());
                it = this->data.val_string.find(rhs.data.val_string);
            }
            break;
        }
            // string - float
        case 8: {
            size_t it = this->data.val_string.find(std::to_string(rhs.data.val_float));
            while (it != std::string::npos) {
                this->data.val_string.erase(it, std::to_string(rhs.data.val_float).size());
                it = this->data.val_string.find(std::to_string(rhs.data.val_float));
            }
            break;
        }
        default:
            return false;
    }
    return true;
}

bool value_t::operator*=(const value_t &rhs) {
    std::pair<token, token> tokens = {this->type, rhs.type};
    uint8_t rule_number = learn_variable(tokens);
    switch (rule_number) {
        // int * int
        case 0: {
            this->data.val_int *= rhs.data.val_int;
            break;
        }
            // float * float
        case 1: {
            this->data.val_float *= rhs.data.val_float;
            break;
        }
            // int * float
        case 2: {
            this->data.val_float = static_cast<float>(this->data.val_int);
            this->type = FLOAT_TOKEN;
            this->data.val_float *= rhs.data.val_float;
            break;
        }
            // float * int
        case 3: {
            this->data.val_float *= static_cast<float>(rhs.data.val_int);
            break;
        }
            // string * string
        case 4: {
            size_t size = this->data.val_string.size();
            if (rhs.data.val_string.size() < size) {
                size = rhs.data.val_string.size();
            }
            std::string result;
            for (size_t i = 0; i < size; i++) {
                if (this->data.val_string[i] == rhs.data.val_string[i]) {
                    result += this->data.val_string[i];
                }
            }
            this->data.val_string = result;
            break;
        }
            // int * string
        case 5: {
            std::string result;
            for (int i = 0; i < this->data.val_int; i++) {
                result += rhs.data.val_string;
            }
            this->data.val_string = result;
            this->type = STRING_TOKEN;
            break;
        }
            // string * int
        case 6: {
            std::string result;
            for (int i = 0; i < rhs.data.val_int; i++) {
                result += this->data.val_string;
            }
            this->data.val_string = result;
            break;
        }
            // float * string
        case 7: {
            std::string result;
            int count = static_cast<int>(this->data.val_float);
            for (int i = 0; i < count; i++) {
                result += rhs.data.val_string;
            }
            this->data.val_string = result;
            this->type = STRING_TOKEN;
            break;
        }
            // string * float
        case 8: {
            std::string result;
            for (int i = 0; i < static_cast<int>(rhs.data.val_float); i++) {
                result += this->data.val_string;
            }
            this->data.val_string = result;
            break;
        }
        default:
            return false;
    }
    return true;
}

bool value_t::operator/=(const value_t &rhs) {
    std::pair<token, token> tokens = {this->type, rhs.type};
    uint8_t rule_number = learn_variable(tokens);
    switch (rule_number) {
        // int / int
        case 0: {
            this->data.val_int /= rhs.data.val_int;
            break;
        }
            // float / float
        case 1: {
            this->data.val_float /= rhs.data.val_float;
            break;
        }
            // int / float
        case 2: {
            this->data.val_float = static_cast<float>(this->data.val_int);
            this->type = FLOAT_TOKEN;
            this->data.val_float /= rhs.data.val_float;
            break;
        }
            // float / int
        case 3: {
            this->data.val_float /= static_cast<float>(rhs.data.val_int);
            break;
        }
            // string / string
        case 4: {
            int count = 0;
            size_t it = this->data.val_string.find(rhs.data.val_string);
            while (it != std::string::npos) {
                this->data.val_string.erase(it, rhs.data.val_string.size());
                it = this->data.val_string.find(rhs.data.val_string);
                count++;
            }
            this->data.val_int = count;
            this->type = INT_TOKEN;
            break;
        }
            // int / string
        case 5: {
            int count = 0;
            std::string str = std::to_string(this->data.val_int);
            size_t it = str.find(rhs.data.val_string);
            while (it != std::string::npos) {
                str.erase(it, rhs.data.val_string.size());
                it = str.find(rhs.data.val_string);
                count++;
            }
            this->data.val_int = count;
            break;
        }
            // string / int
        case 6: {
            int count = 0;
            std::string str = std::to_string(rhs.data.val_int);
            size_t it = this->data.val_string.find(str);
            while (it != std::string::npos) {
                this->data.val_string.erase(it, str.size());
                it = this->data.val_string.find(str);
                count++;
            }
            this->data.val_int = count;
            this->type = INT_TOKEN;
            break;
        }
            // float / string
        case 7: {
            int count = 0;
            std::string str = std::to_string(this->data.val_float);
            size_t it = str.find(rhs.data.val_string);
            while (it != std::string::npos) {
                str.erase(it, rhs.data.val_string.size());
                it = str.find(rhs.data.val_string);
                count++;
            }
            this->data.val_int = count;
            this->type = INT_TOKEN;
            break;
        }
            // string / float
        case 8: {
            int count = 0;
            std::string str = std::to_string(rhs.data.val_float);
            size_t it = this->data.val_string.find(str);
            while (it != std::string::npos) {
                this->data.val_string.erase(it, str.size());
                it = this->data.val_string.find(str);
                count++;
            }
            this->data.val_int = count;
            this->type = INT_TOKEN;
            break;
        }
        default:
            return false;
    }
    return true;
}

bool value_t::operator|(const value_t & rhs) {
    if (this->type != BOOL_TOKEN || rhs.type != BOOL_TOKEN) {
        std::cout << "Error: You can't logic sum this!" << std::endl;
        return false;
    }
    this->data.val_bool = this->data.val_bool || rhs.data.val_bool;
    return true;
}

bool value_t::operator&(const value_t & rhs) {
    if (this->type != BOOL_TOKEN || rhs.type != BOOL_TOKEN) {
        std::cout << "Error: You can't logic multiply this!" << std::endl;
        return false;
    }
    this->data.val_bool = this->data.val_bool && rhs.data.val_bool;
    return true;
}

bool value_t::operator<(const value_t & rhs) {
    std::pair<token, token> tokens = {this->type, rhs.type};
    uint8_t rule_number = learn_variable(tokens);
    switch (rule_number) {
        // int < int
        case 0: {
            this->data.val_bool = this->data.val_int < rhs.data.val_int;
            this->type = BOOL_TOKEN;
            break;
        }
            // float < float
        case 1: {
            this->data.val_bool = this->data.val_float < rhs.data.val_float;
            this->type = BOOL_TOKEN;
            break;
        }
            // int < float
        case 2: {
            this->data.val_bool = static_cast<float>(this->data.val_int) < rhs.data.val_float;
            this->type = BOOL_TOKEN;
            break;
        }
            // float < int
        case 3: {
            this->data.val_bool = this->data.val_float < static_cast<float>(rhs.data.val_int);
            this->type = BOOL_TOKEN;
            break;
        }
            // string / string
        case 4: {
            this->data.val_bool = this->data.val_string < rhs.data.val_string;
            this->type = BOOL_TOKEN;
            break;
        }
            // int < string
        case 5: {
            this->data.val_bool = std::to_string(this->data.val_int) < rhs.data.val_string;
            this->type = BOOL_TOKEN;
            break;
        }
            // string < int
        case 6: {
            this->data.val_bool = this->data.val_string < std::to_string(rhs.data.val_int);
            this->type = BOOL_TOKEN;
            break;
        }
            // float < string
        case 7: {
            this->data.val_bool = std::to_string(this->data.val_float) < rhs.data.val_string;
            this->type = BOOL_TOKEN;
            break;
        }
            // string < float
        case 8: {
            this->data.val_bool = this->data.val_string < std::to_string(rhs.data.val_float);
            this->type = BOOL_TOKEN;
            break;
        }
        default:
            return false;
    }
    return true;
}

bool value_t::operator<=(const value_t & rhs) {
    std::pair<token, token> tokens = {this->type, rhs.type};
    uint8_t rule_number = learn_variable(tokens);
    switch (rule_number) {
        // int < int
        case 0: {
            this->data.val_bool = this->data.val_int <= rhs.data.val_int;
            this->type = BOOL_TOKEN;
            break;
        }
            // float < float
        case 1: {
            this->data.val_bool = this->data.val_float <= rhs.data.val_float;
            this->type = BOOL_TOKEN;
            break;
        }
            // int < float
        case 2: {
            this->data.val_bool = static_cast<float>(this->data.val_int) <= rhs.data.val_float;
            this->type = BOOL_TOKEN;
            break;
        }
            // float < int
        case 3: {
            this->data.val_bool = this->data.val_float <= static_cast<float>(rhs.data.val_int);
            this->type = BOOL_TOKEN;
            break;
        }
            // string / string
        case 4: {
            this->data.val_bool = this->data.val_string <= rhs.data.val_string;
            this->type = BOOL_TOKEN;
            break;
        }
            // int < string
        case 5: {
            this->data.val_bool = std::to_string(this->data.val_int) <= rhs.data.val_string;
            this->type = BOOL_TOKEN;
            break;
        }
            // string < int
        case 6: {
            this->data.val_bool = this->data.val_string <= std::to_string(rhs.data.val_int);
            this->type = BOOL_TOKEN;
            break;
        }
            // float < string
        case 7: {
            this->data.val_bool = std::to_string(this->data.val_float) <= rhs.data.val_string;
            this->type = BOOL_TOKEN;
            break;
        }
            // string < float
        case 8: {
            this->data.val_bool = this->data.val_string <= std::to_string(rhs.data.val_float);
            this->type = BOOL_TOKEN;
            break;
        }
        default:
            return false;
    }
    return true;
}

bool value_t::operator>(const value_t & rhs) {
    std::pair<token, token> tokens = {this->type, rhs.type};
    uint8_t rule_number = learn_variable(tokens);
    switch (rule_number) {
        // int < int
        case 0: {
            this->data.val_bool = this->data.val_int > rhs.data.val_int;
            this->type = BOOL_TOKEN;
            break;
        }
            // float < float
        case 1: {
            this->data.val_bool = this->data.val_float > rhs.data.val_float;
            this->type = BOOL_TOKEN;
            break;
        }
            // int < float
        case 2: {
            this->data.val_bool = static_cast<float>(this->data.val_int) > rhs.data.val_float;
            this->type = BOOL_TOKEN;
            break;
        }
            // float < int
        case 3: {
            this->data.val_bool = this->data.val_float > static_cast<float>(rhs.data.val_int);
            this->type = BOOL_TOKEN;
            break;
        }
            // string / string
        case 4: {
            this->data.val_bool = this->data.val_string > rhs.data.val_string;
            this->type = BOOL_TOKEN;
            break;
        }
            // int < string
        case 5: {
            this->data.val_bool = std::to_string(this->data.val_int) > rhs.data.val_string;
            this->type = BOOL_TOKEN;
            break;
        }
            // string < int
        case 6: {
            this->data.val_bool = this->data.val_string > std::to_string(rhs.data.val_int);
            this->type = BOOL_TOKEN;
            break;
        }
            // float < string
        case 7: {
            this->data.val_bool = std::to_string(this->data.val_float) > rhs.data.val_string;
            this->type = BOOL_TOKEN;
            break;
        }
            // string < float
        case 8: {
            this->data.val_bool = this->data.val_string > std::to_string(rhs.data.val_float);
            this->type = BOOL_TOKEN;
            break;
        }
        default:
            return false;
    }
    return true;
}

bool value_t::operator>=(const value_t & rhs) {
    std::pair<token, token> tokens = {this->type, rhs.type};
    uint8_t rule_number = learn_variable(tokens);
    switch (rule_number) {
        // int < int
        case 0: {
            this->data.val_bool = this->data.val_int >= rhs.data.val_int;
            this->type = BOOL_TOKEN;
            break;
        }
            // float < float
        case 1: {
            this->data.val_bool = this->data.val_float >= rhs.data.val_float;
            this->type = BOOL_TOKEN;
            break;
        }
            // int < float
        case 2: {
            this->data.val_bool = static_cast<float>(this->data.val_int) >= rhs.data.val_float;
            this->type = BOOL_TOKEN;
            break;
        }
            // float < int
        case 3: {
            this->data.val_bool = this->data.val_float >= static_cast<float>(rhs.data.val_int);
            this->type = BOOL_TOKEN;
            break;
        }
            // string / string
        case 4: {
            this->data.val_bool = this->data.val_string >= rhs.data.val_string;
            this->type = BOOL_TOKEN;
            break;
        }
            // int < string
        case 5: {
            this->data.val_bool = std::to_string(this->data.val_int) >= rhs.data.val_string;
            this->type = BOOL_TOKEN;
            break;
        }
            // string < int
        case 6: {
            this->data.val_bool = this->data.val_string >= std::to_string(rhs.data.val_int);
            this->type = BOOL_TOKEN;
            break;
        }
            // float < string
        case 7: {
            this->data.val_bool = std::to_string(this->data.val_float) >= rhs.data.val_string;
            this->type = BOOL_TOKEN;
            break;
        }
            // string < float
        case 8: {
            this->data.val_bool = this->data.val_string >= std::to_string(rhs.data.val_float);
            this->type = BOOL_TOKEN;
            break;
        }
        default:
            return false;
    }
    return true;
}

bool value_t::operator==(const value_t & rhs) {
    std::pair<token, token> tokens = {this->type, rhs.type};
    uint8_t rule_number = learn_variable(tokens);
    switch (rule_number) {
        // int < int
        case 0: {
            this->data.val_bool = this->data.val_int == rhs.data.val_int;
            this->type = BOOL_TOKEN;
            break;
        }
            // float < float
        case 1: {
            this->data.val_bool = this->data.val_float == rhs.data.val_float;
            this->type = BOOL_TOKEN;
            break;
        }
            // int < float
        case 2: {
            this->data.val_bool = static_cast<float>(this->data.val_int) == rhs.data.val_float;
            this->type = BOOL_TOKEN;
            break;
        }
            // float < int
        case 3: {
            this->data.val_bool = this->data.val_float == static_cast<float>(rhs.data.val_int);
            this->type = BOOL_TOKEN;
            break;
        }
            // string / string
        case 4: {
            this->data.val_bool = this->data.val_string == rhs.data.val_string;
            this->type = BOOL_TOKEN;
            break;
        }
            // int < string
        case 5: {
            this->data.val_bool = std::to_string(this->data.val_int) == rhs.data.val_string;
            this->type = BOOL_TOKEN;
            break;
        }
            // string < int
        case 6: {
            this->data.val_bool = this->data.val_string == std::to_string(rhs.data.val_int);
            this->type = BOOL_TOKEN;
            break;
        }
            // float < string
        case 7: {
            this->data.val_bool = std::to_string(this->data.val_float) == rhs.data.val_string;
            this->type = BOOL_TOKEN;
            break;
        }
            // string < float
        case 8: {
            this->data.val_bool = this->data.val_string == std::to_string(rhs.data.val_float);
            this->type = BOOL_TOKEN;
            break;
        }
        default:
            return false;
    }
    return true;
}

bool value_t::operator!=(const value_t & rhs) {
    std::pair<token, token> tokens = {this->type, rhs.type};
    uint8_t rule_number = learn_variable(tokens);
    switch (rule_number) {
        // int < int
        case 0: {
            this->data.val_bool = this->data.val_int != rhs.data.val_int;
            this->type = BOOL_TOKEN;
            break;
        }
            // float < float
        case 1: {
            this->data.val_bool = this->data.val_float != rhs.data.val_float;
            this->type = BOOL_TOKEN;
            break;
        }
            // int < float
        case 2: {
            this->data.val_bool = static_cast<float>(this->data.val_int) != rhs.data.val_float;
            this->type = BOOL_TOKEN;
            break;
        }
            // float < int
        case 3: {
            this->data.val_bool = this->data.val_float != static_cast<float>(rhs.data.val_int);
            this->type = BOOL_TOKEN;
            break;
        }
            // string / string
        case 4: {
            this->data.val_bool = this->data.val_string != rhs.data.val_string;
            this->type = BOOL_TOKEN;
            break;
        }
            // int < string
        case 5: {
            this->data.val_bool = std::to_string(this->data.val_int) != rhs.data.val_string;
            this->type = BOOL_TOKEN;
            break;
        }
            // string < int
        case 6: {
            this->data.val_bool = this->data.val_string != std::to_string(rhs.data.val_int);
            this->type = BOOL_TOKEN;
            break;
        }
            // float < string
        case 7: {
            this->data.val_bool = std::to_string(this->data.val_float) != rhs.data.val_string;
            this->type = BOOL_TOKEN;
            break;
        }
            // string < float
        case 8: {
            this->data.val_bool = this->data.val_string != std::to_string(rhs.data.val_float);
            this->type = BOOL_TOKEN;
            break;
        }
        default:
            return false;
    }
    return true;
}
