/* Note.h: Types for a Musical Note
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

#if !defined NOTE_H
#define NOTE_H

enum class PitchClass
{
	None,
	A_Flat,
	A,
	A_Sharp,
	B_Flat,
	B,
	B_Sharp,
	C_Flat,
	C,
	C_Sharp,
	D_Flat,
	D,
	D_Sharp,
	E_Flat,
	E,
	E_Sharp,
	F_Flat,
	F,
	F_Sharp,
	G_Flat,
	G,
	G_Sharp,
};

PitchClass MakePitchClass(char Letter, char Accidental);

class Pitch
{
public:
	Pitch(PitchClass, int Octave);
	PitchClass Class() const;
	~Pitch();

	int Octave() const;
	double Frequency() const;
private:
	class Pimpl;
	Pimpl* p;
};


class Note
{
public:
	// FIXME: Duration should probably be a rational
	Note(class Pitch, int Duration);
	~Note();
	const Pitch& Pitch() const;
	int Duration() const;
private:
	class Pimpl;
	Pimpl* p;
};

#endif // NOTE_H
