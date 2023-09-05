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

#if !defined SEIRINA_TEMPO_H
#define SEIRINA_TEMPO_H

#include <Seirina/SampleRate.h>

namespace Seirina::Notation
{
	/*! Represents the tempo of a song in beats per minute. */
	class Tempo
	{
	public:
		/*! Construct a Tempo object. */
		Tempo(int);

		/*! Return the length of a beat in audio frames. */
		int getBeatLength(Seirina::Audio::SampleRate atThisSampleRate) const;

		/*! Convert to an `int`. */
		operator int() const;
	private:
		int value;
	};
};

#endif // SEIRINA_TEMPO_H
