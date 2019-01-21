/* Note.cc: Types for a Musical Note
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

#include "Notation/PitchClass.h"
#include "Note.h"

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

class Pitch::Pimpl
{
public:
	inline Pimpl(PitchClass newClass, class Octave newOctave)
	: PitchClass(newClass), Octave(newOctave)
	{
	}

	PitchClass PitchClass;
	class Octave Octave;
};

Pitch::Pitch(PitchClass newClass, class Octave newOctave)
	: p(new Pimpl(newClass, newOctave))
{
}

Pitch::Pitch(const Pitch& src)
	: p(new Pimpl(src.p->PitchClass, src.p->Octave))
{

}

Pitch::~Pitch()
{
	//delete p;
}

PitchClass Pitch::Class() const
{
	return p->PitchClass;
}

Octave Pitch::Octave() const
{
	return p->Octave;
}

double  Pitch::Frequency() const
{
	return PitchMap[p->PitchClass] * std::pow(2.0, p->Octave - 4);
}

class Note::Pimpl
{
public:
	inline Pimpl(class Pitch newPitch,
		int newDurationNumerator, int newDurationDenominator)
	: Pitch(newPitch), DurationNumerator(newDurationNumerator),
		DurationDenominator(newDurationDenominator)
	{
	}

	class Pitch Pitch;
	int DurationNumerator;
	int DurationDenominator;
};

Note::Note(class Pitch newPitch, int  newDurationNumerator,
		int newDurationDenominator)
	: p(new Pimpl(newPitch, newDurationNumerator,
		newDurationDenominator))
{
}

Note::Note(const Note& src)
	: p(new Pimpl(src.p->Pitch,
		src.p->DurationNumerator, src.p->DurationDenominator))
{
}

Note::~Note()
{
	//delete p;
}

const Pitch& Note::Pitch() const
{
	return p->Pitch;
}

double Note::Duration() const
{
	return static_cast<double>(p->DurationNumerator)
		/ static_cast<double>(p->DurationDenominator);
}

class Rest::Pimpl
{
public:
	inline Pimpl(int newDurationNumerator, int newDurationDenominator)
	: DurationNumerator(newDurationNumerator),
		DurationDenominator(newDurationDenominator)
	{
	}

	int DurationNumerator;
	int DurationDenominator;
};

Rest::Rest(int DurationNumerator, int DurationDenominator)
	: p(new Pimpl(DurationNumerator, DurationNumerator))
{
}

Rest::Rest(const Rest& rhs)
	: p(new Pimpl(rhs.p->DurationNumerator, rhs.p->DurationNumerator))
{
}

Rest::~Rest()
{
	delete p;
}

double Rest::Duration() const
{
	return static_cast<double>(p->DurationNumerator)
		/ static_cast<double>(p->DurationDenominator);
}
