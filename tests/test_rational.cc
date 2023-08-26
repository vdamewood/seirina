#include <cstdlib>
#include <iostream>
#include <Seirina/Rational.h>

using std::cout;
using std::endl;
using Seirina::Rational;

int main(int argc, char** argv)
{
    cout << "Beep" << endl;
    int a = std::atoi(argv[1]);
    int b = std::atoi(argv[2]);
    Rational x{a,b};
    double expected = static_cast<double>(a)/static_cast<double>(b);
    double actual = static_cast<double>(a)/static_cast<double>(b);
    cout << "Numerator In   " << a << endl;
    cout << "Denominator In " << b << endl;
    cout << "Numerator      " << x.getNumerator() << endl;
    cout << "Denominator    " << x.getDenominator() << endl;
    cout << "Expected       " << expected << endl;
    cout << "Actual         " << actual << endl;
    return static_cast<double>(x) != expected;
}
