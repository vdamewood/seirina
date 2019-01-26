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

#include "Tuning.h"

// This might be useful later
#define ROOT12_OF_2 1.0594630943592951988208028
#define CONCERT_A 440.0

using Seirina::Notation::PitchClass;
using Seirina::Audio::Frequency;

namespace Seirina::Notation
{
	class TuningPrivate
	{
	public:
		TuningPrivate(
			PitchClass newPitchClass,
			Frequency newFrequency)
		{
			// FIXME: Take newPitchClass and newFrequency and calculate
			//   PitchMap for Octave 0.
		}

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
	};

	Tuning::Tuning(
			enum PitchClass newPitchClass,
			class Frequency newFrequency)
		: p(new TuningPrivate(
			newPitchClass,
			newFrequency))
	{
	}

	Tuning::Tuning(const Tuning& src)
		: p(new TuningPrivate(PitchClass::A, 440.0))
	{
	}

	Tuning::~Tuning()
	{
		//delete p;
	}

	Seirina::Audio::Frequency Tuning::operator[](PitchClass inClass)
	{
		return p->PitchMap[inClass];
	}
	/*Seirina::Audio::Frequency  Tuning::Frequency(Note inNote) const
	{
		return p->PitchMap[inNote.PitchClass()] * std::pow(2.0, inNote.Octave() - 4);
	}*/
};
