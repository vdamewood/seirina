/* Tempo.cc: Tempo in music
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

#include <Seirina/Tempo.h>

namespace Seirina::Notation
{
	Tempo::Tempo(int newValue)
	{
		value = newValue;
	}

	Tempo::operator int() const
	{
		return value;
	}

	int Tempo::getBeatLength(Seirina::Audio::SampleRate rate) const
	{
		return (rate * 60) / value;
	}
};
