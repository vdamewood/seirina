/* Octave.cc: Class to represent an octave in music notation
 *
 * Copyright 2019 Vincent Damewood
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

#include "Octave.h"

static inline int clip(int i)
{
	return
		i < 0 ? 0
		: i > 9 ? 9
		: i;
}

namespace Seirina::Notation
{
	Octave::Octave(int newValue)
	{
		value = clip(newValue);
	}

	Octave::operator int() const
	{
		return value;
	}
}
