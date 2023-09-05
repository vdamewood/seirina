/* Rational.h: A rational number
 *
 * Copyright 2016-2019, 2023 Vincent Damewood
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


#if !defined SEIRINA_RATIONAL_H
#define SEIRINA_RATIONAL_H

namespace Seirina
{
	/*! A rational number */
	class Rational
	{
	public:
		/*! Construct a duration */
		Rational(int numerator=0, int denominator=1);
		/*! Copy constructor */
		Rational(const Rational&);

		/*! Destructor */
		~Rational();

        int getNumerator() const;
        int getDenominator() const;

        Rational operator+(const Rational&) const;
        Rational operator-(const Rational&) const;
        Rational operator*(const Rational&) const;
        Rational operator/(const Rational&) const;

        Rational& operator+=(const Rational&);
        Rational& operator-=(const Rational&);
        Rational& operator*=(const Rational&);
        Rational& operator/=(const Rational&);

		/*! Get rational as a double */
		operator double() const;
	private:
        void normalize();
		int numerator;
		int denominator;
	};
};

#endif // SEIRINA_RATIONAL_H
