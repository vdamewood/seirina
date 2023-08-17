/* Rational.cc: A rational number
 *
 * Copyright 2018, 2023 Vincent Damewood
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include <Seirina/Rational.h>

namespace Seirina
{
	Rational::Rational(int newNumerator, int newDenominator)
		: numerator(newNumerator),
			denominator(newDenominator)
	{
        normalize();
	}

	Rational::Rational(const Rational& src)
		: numerator(src.numerator),
			denominator(src.denominator)
	{
	}

	Rational::~Rational()
	{
	}

    int Rational::getNumerator() const
    {
        return numerator;
    }

    int Rational::getDenominator() const
    {
        return denominator;
    }

    Rational Rational::operator+(const Rational& rhs) const
    {
        return Rational(
            numerator*rhs.denominator + rhs.numerator*denominator,
            denominator*rhs.denominator
        );
    }

    Rational Rational::operator-(const Rational& rhs) const
    {
        return Rational(
            numerator*rhs.denominator - rhs.numerator*denominator,
            denominator*rhs.denominator
        );
    }

    Rational Rational::operator*(const Rational& rhs) const
    {
        return Rational(
            numerator*rhs.numerator,
            denominator*rhs.denominator
        );
    }

    Rational Rational::operator/(const Rational& rhs) const
    {
        return Rational(
            numerator*rhs.denominator,
            denominator*rhs.numerator
        );
    }

    Rational& Rational::operator+=(const Rational& rhs)
    {
        int new_numerator = numerator*rhs.denominator + rhs.numerator*denominator;
        int new_denominator = denominator*rhs.denominator;
        numerator = new_numerator;
        denominator = new_denominator;
        normalize();

        return *this;
    }

    Rational& Rational::operator-=(const Rational& rhs)
    {
        int new_numerator = numerator*rhs.denominator - rhs.numerator*denominator;
        int new_denominator = denominator*rhs.denominator;
        numerator = new_numerator;
        denominator = new_denominator;
        normalize();

        return *this;
    }

    Rational& Rational::operator*=(const Rational& rhs)
    {
        int new_numerator = numerator*rhs.numerator;
        int new_denominator = denominator*rhs.denominator;
        numerator = new_numerator;
        denominator = new_denominator;
        normalize();

        return *this;
    }

    Rational& Rational::operator/=(const Rational& rhs)
    {
        int new_numerator = numerator*rhs.denominator;
        int new_denominator = denominator*rhs.numerator;
        numerator = new_numerator;
        denominator = new_denominator;
        normalize();

        return *this;
    }

    Rational::operator double() const
    {
		return static_cast<double>(numerator)
			/ static_cast<double>(denominator);
	}

    void Rational::normalize()
    {
        if (numerator < 0)
            denominator = -denominator;

        bool denominator_is_negative{denominator < 0 ? true : false};
        if (denominator_is_negative)
            denominator = -denominator;

        int new_numerator = numerator;
        int new_denominator = denominator;

        while (1)
        {
            int temp_modulus = new_numerator % new_denominator;
            if (temp_modulus)
            {
                new_numerator = new_denominator;
                new_denominator = temp_modulus;
            }
            else
            {
                break;
            }
        }

        numerator /= new_denominator;
        denominator /= new_denominator;

        if (denominator_is_negative)
            denominator *= -denominator;
    }
};
