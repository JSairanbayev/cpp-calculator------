#pragma once

#include <string>
#include <optional>
#include <cmath>
#include <type_traits>
#include "rational.h"
#include "pow.h"

using Error = std::string;

template <typename Number>
class Calculator {
public:
    Calculator() = default;

    std::optional<Error> Set(Number number) {
        current_ = number;
        return std::nullopt;
    }

    std::optional<Error> Add(Number number) {
        current_ += number;
        return std::nullopt;
    }

    std::optional<Error> Sub(Number number) {
        current_ -= number;
        return std::nullopt;
    }

    std::optional<Error> Mul(Number number) {
        current_ *= number;
        return std::nullopt;
    }

    std::optional<Error> Div(Number number) {
        if constexpr (std::is_integral_v<Number> || std::is_same_v<Number, Rational>) {
            if (number == Number{}) {
                return "Division by zero";
            }
        }
        current_ /= number;
        return std::nullopt;
    }

    std::optional<Error> Pow(Number number) {
        if constexpr (std::is_integral_v<Number> || std::is_same_v<Number, Rational>) {
            if (current_ == Number{} && number == Number{}) {
                return "Zero power to zero";
            }
        }

        if constexpr (std::is_same_v<Number, Rational>) {
            if (number.GetDenominator() != 1) {
                return "Fractional power is not supported";
            }
            current_ = ::Pow(current_, number);
            return std::nullopt;
        } else if constexpr (std::is_integral_v<Number>) {
            if (number < Number{}) {
                return "Integer negative power";
            }
            current_ = IntegerPow(current_, number);
            return std::nullopt;
        } else {
            current_ = std::pow(current_, number);
            return std::nullopt;
        }
    }

    Number GetNumber() const {
        return current_;
    }

    void Save() {
        mem_ = current_;
    }

    void Load() {
        if (mem_.has_value()) {
            current_ = mem_.value();
        }
    }

    void ClearMem() {
        mem_ = std::nullopt;
    }

    bool GetHasMem() const {
        return mem_.has_value();
    }

private:
    Number current_ = {};
    std::optional<Number> mem_ = {};
};