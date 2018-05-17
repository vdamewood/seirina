/* Note.cc: Types for a Musical Note
 *
 * Copyright 2018 Vincent Damewood
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

#include <map>

#include "Note.h"

// This might be useful later
#define ROOT12_OF_2 1.0594630943592951988208028
#define CONCERT_A 440.0

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

PitchClass MakePitchClass(char Letter, char Accidental)
{
	if (Letter >= 'a' && Letter <= 'g')
		Letter -= 'a' - 'A';

	if (Letter < 'A' || Letter > 'G')
		return PitchClass::None;

	int Adjustment = 2;
	switch (Accidental)
	{
		case '-':
		case 'b':
			Adjustment = 1;
			break;
		case '+':
		case '#':
			Adjustment = 3;
			break;
		default:
			break;
	}
	return static_cast<PitchClass>((Letter - 'A')*3 + Adjustment);
}

class Pitch::Pimpl
{
public:
	inline Pimpl(PitchClass newClass, int newOctave)
	: PitchClass(newClass), Octave(newOctave)
	{
	}

	PitchClass PitchClass;
	int Octave;
};

Pitch::Pitch(PitchClass newClass, int newOctave)
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

int Pitch::Octave() const
{
	return p->Octave;
}

double  Pitch::Frequency() const
{
	return PitchMap[p->PitchClass] * (1<<(p->Octave-4));
}

class Note::Pimpl
{
public:
	inline Pimpl(class Pitch newPitch, int newDuration)
	: Pitch(newPitch), Duration(newDuration)
	{
	}

	class Pitch Pitch;
	int Duration;
};

Note::Note(class Pitch newPitch, int  newDuration)
	: p(new Pimpl(newPitch, newDuration))
{

}

Note::Note(const Note& src)
	: p(new Pimpl(src.p->Pitch, src.p->Duration))
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

int Note::Duration() const
{
	return p->Duration;
}
