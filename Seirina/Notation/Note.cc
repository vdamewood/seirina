/* Note.cc: Musical note
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

#include <cmath>
#include <map>

#include "Note.h"
#include "PitchClass.h"

// This might be useful later
#define ROOT12_OF_2 1.0594630943592951988208028
#define CONCERT_A 440.0

using Seirina::Notation::Octave;
using Seirina::Notation::PitchClass;

std::map<PitchClass, double> PitchMap
{
	{PitchClass::C_Flat,  246.94},
	{PitchClass::C,       261.63},
	{PitchClass::C_Sharp, 277.18},
	{PitchClass::D_Flat,  277.18},
	{PitchClass::D,       293.66},
	{PitchClass::D_Sharp, 311.13},
	{PitchClass::E_Flat,  311.13},
	{PitchClass::E,       329.63},
	{PitchClass::E_Sharp, 349.23},
	{PitchClass::F_Flat,  329.63},
	{PitchClass::F,       349.23},
	{PitchClass::F_Sharp, 369.99},
	{PitchClass::G_Flat,  369.99},
	{PitchClass::G,       392.00},
	{PitchClass::G_Sharp, 415.30},
	{PitchClass::A_Flat,  415.30},
	{PitchClass::A,       440.00},
	{PitchClass::A_Sharp, 466.16},
	{PitchClass::B_Flat,  466.16},
	{PitchClass::B,       493.88},
	{PitchClass::B_Sharp, 523.25},
};

namespace Seirina::Notation
{
	class NotePrivate
	{
	public:
		NotePrivate(
			PitchClass newPitchClass,
			Octave newOctave,
			Duration newDuration)
		: pitchClass(newPitchClass),
			octave(newOctave),
			duration(newDuration)
		{
		}

		PitchClass pitchClass;
		Octave octave;
		Duration duration;
	};

	Note::Note(
			enum PitchClass newPitchClass,
			class Octave newOctave,
			class Duration newDuration)
		: p(new NotePrivate(
			newPitchClass,
			newOctave,
			newDuration))
	{
	}

	Note::Note(const Note& src)
		: p(new NotePrivate(
			src.p->pitchClass,
			src.p->octave,
			src.p->duration))
	{
	}

	Note::~Note()
	{
		//delete p;
	}

	const PitchClass& Note::PitchClass() const
	{
		return p->pitchClass;
	}

	const Octave& Note::Octave() const
	{
		return p->octave;
	}

	Seirina::Audio::Frequency  Note::Frequency() const
	{
		return PitchMap[p->pitchClass] * std::pow(2.0, p->octave - 4);
	}


	Duration Note::Duration() const
	{
		return p->duration;
	}
};
