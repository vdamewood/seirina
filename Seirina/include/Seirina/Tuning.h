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

#if !defined SEIRINA_TUNING_H
#define SEIRINA_TUNING_H

#include <memory>

#include <Seirina/Frequency.h>
//#include <Seirina/Octave.h>
#include <Seirina/PitchClass.h>
#include <Seirina/Note.h>

namespace Seirina
{
	/*! A tuning for a musical scale */
	class Tuning
	{
	public:
		/*! Construct a Tuning.
		 *
		 * Note: Currently, this always returns an A=440Hz tuning.
		 */
		Tuning(PitchClass, Frequency);
		/*! Copy constructor */
		Tuning(const Tuning&);

		/*! Destructor */
		~Tuning();

		/*! Get a particular frequency based on a pitch class */
		Frequency operator[](PitchClass) const;

		/*! Get a particular frequency based on a pitch class */
		Frequency operator[](Note) const;
	private:
		class PImpl;
		const std::unique_ptr<PImpl> p;
	};
};

#endif // SEIRINA_TUNING_H
