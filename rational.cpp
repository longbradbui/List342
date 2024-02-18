#include <iostream>
#include <cmath>
#include "rational.h"
using namespace std;

Rational::Rational() : numerator_(0), denominator_(1)
{
}

Rational::Rational(int numerator, int denominator) : numerator_(numerator), denominator_(denominator)
{
    if (denominator == 0)
    {
        numerator_ = 0;
        denominator = 1;
    }
    reduce();
}

int Rational::numerator() const
{
    return numerator_;
}

int Rational::denominator() const
{
    return denominator_;
}

bool Rational::SetValue(int numerator, int denominator)
{
    if (denominator == 0)
    {
        return false;
    }
    numerator_ = numerator;
    denominator_ = denominator;
    reduce();
    return true;
}

void Rational::reduce()
{
    int gcd = 1;
    int minimum = min(numerator_, denominator_);
    for (int i = 2; i <= minimum; i++)
    {
        if (((numerator_ % i) == 0) && ((denominator_ % i) == 0))
        {
            gcd = i;
        }
    }
    if (gcd > 1)
    {
        numerator_ /= gcd;
        denominator_ /= gcd;
    }
}

Rational Rational::Add(const Rational &rhs) const
{
    Rational temp;
    temp.numerator_ = (this->numerator() * rhs.denominator()) + (this->denominator() * rhs.numerator());
    temp.denominator_ = (this->denominator() * rhs.denominator());
    temp.reduce();
    return temp;
}

Rational Rational::Subtract(const Rational &rhs) const
{
    return Rational();
}

Rational Rational::Multiply(const Rational &rhs) const
{
    Rational temp;
    int numerator = this->numerator() * rhs.numerator();
    int denominator = this->denominator() * rhs.denominator();
    temp.SetValue(numerator, denominator);
    temp.reduce();
    return temp;
}

Rational Rational::Divide(const Rational &rhs) const
{
    Rational temp;
    int numerator = this->numerator() * rhs.denominator();
    int denominator = this->denominator() * rhs.numerator();
    temp.SetValue(numerator, denominator);
    temp.reduce();
    return temp;
}

Rational Rational::operator+(const Rational &rhs) const
{
    Rational result = *this;
    result += rhs;
    return result;
}

Rational Rational::operator-(const Rational &rhs) const
{
    Rational result = *this;
    result -= rhs;
    return result;
}

Rational Rational::operator*(const Rational &rhs) const
{
    Rational result = *this;
    result *= rhs;
    return result;
}

Rational Rational::operator/(const Rational &rhs) const
{
    Rational result = *this;
    result /= rhs;
    return result;
}

Rational &Rational::operator+=(const Rational &rhs)
{
    int numerator = (this->numerator() * rhs.denominator()) + (this->denominator() * rhs.numerator());
    int denominator = this->denominator() * rhs.denominator();
    SetValue(numerator, denominator);
    reduce();
    return *this;
}

Rational &Rational::operator-=(const Rational &rhs)
{
    int numerator = (this->numerator() * rhs.denominator()) - (this->denominator() * rhs.numerator());
    int denominator = this->denominator() * rhs.denominator();
    SetValue(numerator, denominator);
    reduce();
    return *this;
}

Rational &Rational::operator*=(const Rational &rhs)
{
    int numerator = this->numerator() * rhs.numerator();
    int denominator = this->denominator() * rhs.denominator();
    reduce();
    return *this;
}

Rational &Rational::operator/=(const Rational &rhs)
{
    int numerator = this->numerator() * rhs.denominator();
    int denominator = this->denominator() * rhs.numerator();
    reduce();
    return *this;
}

bool operator<(Rational const &lhs, Rational const &rhs)
{
    return ((lhs.numerator() * rhs.denominator()) < (lhs.denominator() * rhs.numerator()));
}

bool operator>(Rational const &lhs, Rational const &rhs)
{
    return ((lhs.numerator() * rhs.denominator()) > (lhs.denominator() * rhs.numerator()));
}

bool operator==(Rational const &lhs, Rational const &rhs)
{
    return ((lhs.numerator() == rhs.numerator()) && (lhs.denominator() == rhs.denominator()));
}

bool operator!=(Rational const &lhs, Rational const &rhs)
{
    return !(lhs == rhs);
}

bool operator<=(Rational const &lhs, Rational const &rhs)
{
    return ((lhs.numerator() * rhs.denominator()) <= (lhs.denominator() * rhs.numerator()));
}

bool operator>=(Rational const &lhs, Rational const &rhs)
{
    return ((lhs.numerator() * rhs.denominator()) >= (lhs.denominator() * rhs.numerator()));
}

ostream &operator<<(ostream &stream, const Rational &rhs)
{
    stream << rhs.numerator_ << "/" << rhs.denominator_ << " -> ";
    return stream;
}

istream &operator>>(istream &stream, Rational &rhs)
{
    stream >> rhs.numerator_ >> rhs.denominator_;
    if (rhs.denominator_ == 0)
    {
        rhs.numerator_ = 0;
        rhs.denominator_ = 1;
    }
    else
    {
        rhs.reduce();
    }
    return stream;
}