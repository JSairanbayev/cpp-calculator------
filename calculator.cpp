#include "calculator.h"
#include <iostream>
#include <cmath>
#include <string>

bool ReadNumber(Number& result) {
    if (!(std::cin >> result)) {
        return false;
    }
    return true;
}

bool RunCalculatorCycle() {
    Number accumulator;
    
    if (!ReadNumber(accumulator)) {
        std::cerr << "Error: Numeric operand expected" << std::endl;
        return false;
    }
    
    Number memory = 0;
    bool has_memory = false;
    
    std::string command;
    while (std::cin >> command) {
        
        if (command == "q") {
            return true;
        }
        
        if (command == "=") {
            std::cout << accumulator << std::endl;
            continue;
        }
        
        if (command == "c") {
            accumulator = 0;
            continue;
        }
        
        if (command == "s") {
            memory = accumulator;
            has_memory = true;
            continue;
        }
        
        if (command == "l") {
            if (!has_memory) {
                std::cerr << "Error: Memory is empty" << std::endl;
                return false;
            }
            accumulator = memory;
            continue;
        }
        
        if (command == "+" || command == "-" || command == "*" || 
            command == "/" || command == "**" || command == ":") {
            
            Number operand;
            if (!ReadNumber(operand)) {
                std::cerr << "Error: Numeric operand expected" << std::endl;
                return false;
            }
            
            if (command == "+") {
                accumulator += operand;
            } else if (command == "-") {
                accumulator -= operand;
            } else if (command == "*") {
                accumulator *= operand;
            } else if (command == "/") {
                accumulator /= operand;
            } else if (command == "**") {
                accumulator = std::pow(accumulator, operand);
            } else if (command == ":") {
                accumulator = operand;
            }
            
            continue;
        }
        
        std::cerr << "Error: Unknown token " << command << std::endl;
        return false;
    }
    
    return true;
}