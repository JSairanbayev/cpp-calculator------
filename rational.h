#pragma once

#include <iostream>
#include <numeric>
#include <compare>
#include <cstdlib>

class Rational {
public:
    Rational() = default;

    Rational(int numerator)
        : numerator_(numerator)
        , denominator_(1) {
    }

    Rational(int numerator, int denominator)
        : numerator_(numerator)
        , denominator_(denominator) {
        if (denominator_ == 0) {
            std::abort();
        }
        Reduction();
    }

    Rational(const Rational& other) = default;

    int GetNumerator() const {
        return numerator_;
    }

    int GetDenominator() const {
        return denominator_;
    }

    Rational Inv() const {
        return Rational(denominator_, numerator_);
    }

    Rational& operator=(const Rational& other) = default;

    Rational operator+() const {
        return *this;
    }

    Rational operator-() const {
        return Rational(-numerator_, denominator_);
    }

    Rational& operator+=(const Rational& r) {
        numerator_ = numerator_ * r.denominator_ + r.numerator_ * denominator_;
        denominator_ = denominator_ * r.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator-=(const Rational& r) {
        numerator_ = numerator_ * r.denominator_ - r.numerator_ * denominator_;
        denominator_ = denominator_ * r.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator*=(const Rational& r) {
        numerator_ *= r.numerator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator/=(const Rational& r) {
        numerator_ *= r.denominator_;
        denominator_ *= r.numerator_;
        if (denominator_ == 0) {
            std::abort();
        }
        Reduction();
        return *this;
    }

private:
    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

    int numerator_ = 0;
    int denominator_ = 1;
};

inline Rational operator+(Rational a, const Rational& b) {
    a += b;
    return a;
}

inline Rational operator-(Rational a, const Rational& b) {
    a -= b;
    return a;
}

inline Rational operator*(Rational a, const Rational& b) {
    a *= b;
    return a;
}

inline Rational operator/(Rational a, const Rational& b) {
    a /= b;
    return a;
}

inline bool operator==(const Rational& a, const Rational& b) {
    return a.GetNumerator() == b.GetNumerator()
    && a.GetDenominator() == b.GetDenominator();
}

inline auto operator<=>(const Rational& a, const Rational& b) {
    return static_cast<long long>(a.GetNumerator()) * b.GetDenominator()
    <=> static_cast<long long>(b.GetNumerator()) * a.GetDenominator();
}

inline std::ostream& operator<<(std::ostream& out, const Rational& r) {
    if (r.GetDenominator() == 1) {
        out << r.GetNumerator();
    } else {
        out << r.GetNumerator() << " / " << r.GetDenominator();
    }
    return out;
}

inline std::istream& operator>>(std::istream& in, Rational& r) {
    int num = 0;
    int den = 1;

    if (!(in >> num)) {
        return in;
    }

    char c;
    if (!(in >> c)) {
        in.clear();
        r = Rational(num);
        return in;
    }

    if (c != '/') {
        in.unget();
        r = Rational(num);
        return in;
    }

    if (!(in >> den)) {
        return in;
    }

    if (den == 0) {
        in.setstate(std::ios::failbit);
        return in;
    }

    r = Rational(num, den);
    return in;
}