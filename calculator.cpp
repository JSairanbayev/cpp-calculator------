#include "calculator.h"
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

bool ReadNumber(Number& result) {
    if (!(std::cin >> result)) {
        return false;
    }
    return true;
}

bool RunCalculatorCycle() {
    Number accumulator = 0;
    Number memory = 0;
    bool has_memory = false;
    bool first_token = true;

    std::string token;
    while (std::cin >> token) {

        std::istringstream input_stream(token);
        Number parsed_number = 0;
        if (input_stream >> parsed_number && input_stream.eof()) {
            accumulator = parsed_number;
            first_token = false;
            continue;
        }

        if (first_token) {
            std::cerr << "Error: Numeric operand expected" << std::endl;
            return false;
        }

        if (token == "q") {
            return true;
        }

        if (token == "=") {
            std::cout << accumulator << std::endl;
            continue;
        }

        if (token == "c") {
            accumulator = 0;
            continue;
        }

        if (token == "s") {
            memory = accumulator;
            has_memory = true;
            continue;
        }

        if (token == "l") {
            if (!has_memory) {
                std::cerr << "Error: Memory is empty" << std::endl;
                return false;
            }
            accumulator = memory;
            continue;
        }

        if (token == "+" || token == "-" || token == "*" ||
            token == "/" || token == "**" || token == ":") {

            Number operand = 0;
            if (!ReadNumber(operand)) {
                std::cerr << "Error: Numeric operand expected" << std::endl;
                return false;
            }

            if (token == "+") {
                accumulator += operand;
            } else if (token == "-") {
                accumulator -= operand;
            } else if (token == "*") {
                accumulator *= operand;
            } else if (token == "/") {
                accumulator /= operand;
            } else if (token == "**") {
                accumulator = std::pow(accumulator, operand);
            } else if (token == ":") {
                accumulator = operand;
            }

            continue;
        }

        std::cerr << "Error: Unknown token " << token << std::endl;
        return false;
    }

    return true;
}
