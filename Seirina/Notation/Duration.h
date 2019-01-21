/* Duration.h: Musical duration
 *
 * Copyright 2018, 2019 Vincent Damewood
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

#if !defined SEIRINA_NOTATION_DURATION_H
#define SEIRINA_NOTATION_DURATION_H

namespace Seirina::Notation
{
	class DurationPrivate;

	/*! A note in musical notation */
	class Duration
	{
	public:
		/*! Construct a duration */
		Duration(int numerator, int denominator=1);
		/*! Copy constructor */
		Duration(const Duration&);

		/*! Destructor */
		~Duration();

		/*! Get duration as a double */
		operator double() const;
	private:
		int numerator;
		int denominator;
	};
};

#endif // SEIRINA_NOTATION_DURATION_H
