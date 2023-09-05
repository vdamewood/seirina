/* Note.h: Musical note
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

#if !defined SEIRINA_NOTATION_TUNING_H
#define SEIRINA_NOTATION_TUNING_H

#include <Seirina/Frequency.h>
//#include <Seirina/Octave.h>
#include <Seirina/PitchClass.h>

namespace Seirina::Notation
{
	class TuningPrivate;

	/*! A tuning for a musical scale */
	class Tuning
	{
	public:
		/*! Construct a Tuning.
		 *
		 * Note: Currently, this always returns an A=440Hz tuning.
		 */
		Tuning(
			Seirina::Notation::PitchClass,
			Seirina::Audio::Frequency);
		/*! Copy constructor */
		Tuning(const Tuning&);

		/*! Destructor */
		~Tuning();

		/*! Get a particular frequency based on a pitch class */
		Seirina::Audio::Frequency operator[](PitchClass);
	private:
		TuningPrivate* p;
	};
};

#endif // SEIRINA_NOTATION_TUNING_H
