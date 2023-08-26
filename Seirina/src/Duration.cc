/* Duration.cc: Musical duration
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

#include <Seirina/Duration.h>

namespace Seirina::Notation
{
	Duration::Duration(int newNumerator, int newDenominator)
		: Rational(newNumerator, newDenominator)
	{
	}

	Duration::Duration(const Duration& src)
		: Rational(src)
	{
	}
};
