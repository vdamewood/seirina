/* PitchClass.h: Pitch Class in Musical Notation
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

#if !defined SEIRINA_PITCH_CLASS_H
#define SEIRINA_PITCH_CLASS_H

namespace Seirina::Notation
{
	/*! Represents a pitch class, the 'letter' and accidental portion of
	 *  a notes name without regard for octave.
	 */
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

	/*! Make a new pitch class value */
	PitchClass MakePitchClass(char Letter, char Accidental);
}

#endif // SEIRINA_PITCH_CLASS_H
