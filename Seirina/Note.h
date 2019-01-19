/* Note.h: Types for a Musical Note
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

#if !defined SEIRINA_NOTE_H
#define SEIRINA_NOTE_H

#include "Octave.h"
#include "PitchClass.h"

class Pitch
{
public:
	Pitch(Seirina::Notation::PitchClass, Seirina::Notation::Octave);
	Pitch(const Pitch&);
	Seirina::Notation::PitchClass Class() const;
	~Pitch();

	Seirina::Notation::Octave Octave() const;
	double Frequency() const;
private:
	class Pimpl;
	Pimpl* p;
};


class Note
{
public:
	Note(class Pitch, int DurationNumerator=1,
		int DurationDenominator=1);
	Note(const Note&);
	~Note();
	const Pitch& Pitch() const;
	double Duration() const;
private:
	class Pimpl;
	Pimpl* p;
};

class Rest
{
public:
	Rest(int DurationNumerator=1,int DurationDenominator=1);
	Rest(const Rest&);
	~Rest();
	double Duration() const;
private:
	class Pimpl;
	Pimpl* p;
};

#endif // SEIRINA_NOTE_H
