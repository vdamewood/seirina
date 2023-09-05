/* Note.h: Musical note
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

#if !defined SEIRINA_NOTATION_NOTE_H
#define SEIRINA_NOTATION_NOTE_H

#include <Seirina/Frequency.h>
#include <Seirina/NoteDuration.h>
#include <Seirina/Octave.h>
#include <Seirina/PitchClass.h>
#include <Seirina/Tuning.h>

namespace Seirina::Notation
{
	class NotePrivate;

	/*! A note in musical notation */
	class Note
	{
	public:
		/*! Construct a note */
		Note(
			PitchClass,
			Octave,
			NoteDuration);
		/*! Copy constructor */
		Note(const Note&);

		/*! Destructor */
		~Note();

		/*! Fetch the PitchClass of the note */
		const PitchClass& PitchClass() const;

		/*! Fetch the Octave of the note */
		const Octave& Octave() const;

		/*! Fetch the Frequency of the note */
		Seirina::Audio::Frequency Frequency(Tuning) const;

		/*! Fetch the Duration of the note */
		NoteDuration Duration() const;
	private:
		NotePrivate* p;
	};
};

#endif // SEIRINA_NOTATION_NOTE_H
