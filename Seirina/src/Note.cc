/* Note.cc: Musical note
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

#include <cmath>

#include <Seirina/Note.h>
#include <Seirina/PitchClass.h>


namespace Seirina
{
	class Note::PImpl
	{
	public:
		PImpl(
			enum PitchClass newPitchClass,
			class Octave newOctave,
			NoteDuration newDuration)
		: pitchClass(newPitchClass),
			octave(newOctave),
			duration(newDuration)
		{
		}

		enum PitchClass pitchClass;
		class Octave octave;
		NoteDuration duration;
	};

	Note::Note(
			enum PitchClass newPitchClass,
			class Octave newOctave,
			NoteDuration newDuration)
		: p(std::make_unique<PImpl>(
			newPitchClass,
			newOctave,
			newDuration))
	{
	}

	Note::Note(const Note& src)
		: p(std::make_unique<PImpl>(
			src.p->pitchClass,
			src.p->octave,
			src.p->duration))
	{
	}

	Note::~Note()
	{
	}

	const PitchClass& Note::PitchClass() const
	{
		return p->pitchClass;
	}

	const Octave& Note::Octave() const
	{
		return p->octave;
	}

	Frequency Note::Frequency(Tuning inTuning) const
	{
		return inTuning[p->pitchClass] * std::pow(2.0, p->octave - 4);
	}


	NoteDuration Note::Duration() const
	{
		return p->duration;
	}
};
