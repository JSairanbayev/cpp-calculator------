#include "calculator.h"

#include <cmath>
#include <string>

void Calculator::Set(Number n) {
    current_ = n;
}

Number Calculator::GetNumber() const {
    return current_;
}

void Calculator::Add(Number n) {
    current_ += n;
}

void Calculator::Sub(Number n) {
    current_ -= n;
}

void Calculator::Div(Number n) {
    current_ /= n;
}

void Calculator::Mul(Number n) {
    current_ *= n;
}

void Calculator::Pow(Number n) {
    current_ = std::pow(current_, n);
}

void Calculator::Save() {
    memory_ = current_;
    has_memory_ = true;
}

void Calculator::Load() {
    current_ = memory_;
}

bool Calculator::HasMem() const {
    return has_memory_;
}

std::string Calculator::GetNumberRepr() const {
    return std::to_string(current_);
}