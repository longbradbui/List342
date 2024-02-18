#ifndef RATIONAL_H_
#define RATIONAL_H_
#include <iostream>
using namespace std;
class Rational
{
public:
    // CONSTRUCTORS
    Rational();
    Rational(int numerator, int denominator);
    // GETTERS
    int numerator() const;
    int denominator() const;
    // SETTERS
    bool SetValue(int numerator, int denominator);
    // ACTIONS
    Rational Multiply(const Rational &rhs) const;
    Rational Divide(const Rational &rhs) const;
    Rational Add(const Rational &rhs) const;
    Rational Subtract(const Rational &rhs) const;
    Rational operator+(const Rational &rhs) const;
    Rational operator-(const Rational &rhs) const;
    Rational operator*(const Rational &rhs) const;
    Rational operator/(const Rational &rhs) const;
    Rational &operator+=(const Rational &rhs);
    Rational &operator-=(const Rational &rhs);
    Rational &operator*=(const Rational &rhs);
    Rational &operator/=(const Rational &rhs);
    friend ostream &operator<<(ostream &stream, const Rational &rhs);
    friend istream &operator>>(istream &stream, Rational &rhs);
    friend bool operator<(Rational const &lhs, Rational const &rhs);
    friend bool operator>(Rational const &lhs, Rational const &rhs);
    friend bool operator==(Rational const &lhs, Rational const &rhs);
    friend bool operator!=(Rational const &lhs, Rational const &rhs);
    friend bool operator<=(Rational const &lhs, Rational const &rhs);
    friend bool operator>=(Rational const &lhs, Rational const &rhs);

private:
    int numerator_;
    int denominator_;
    void reduce(); 
};
#endif
