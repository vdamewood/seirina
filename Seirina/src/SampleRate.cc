/* SampleRate.cc: Sample rates
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

#include <Seirina/SampleRate.h>

namespace Seirina
{
	SampleRate::SampleRate(int newValue)
	{
		value = newValue;
	}

	SampleRate::operator int() const
	{
		return value;
	}

	const SampleRate SampleRate::Cd = SampleRate(44100);
	const SampleRate SampleRate::Dvd = SampleRate(48000);
}
