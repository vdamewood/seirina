/* NoteDuration.h: The duration of a musical note
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

#if !defined SEIRINA_NOTE_DURATION_H
#define SEIRINA_NOTE_DURATION_H

#include <Seirina/Rational.h>

namespace Seirina
{
	/*! The duration of a note as a rational number of beats */
	class NoteDuration : public Rational
	{
	public:
		/*! Construct a duration */
		NoteDuration(int numerator, int denominator=1);

		/*! Copy constructor */
		NoteDuration(const NoteDuration&);
	};
};

#endif // SEIRINA_NOTE_DURATION_H
