/* Mph.cc: MakePitchClass function
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
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Note.h"

PitchClass MakePitchClass(char Letter, char Accidental)
{
	switch (Letter)
	{
	case 'A':
	case 'a':
		switch (Accidental)
		{
		case '+':
		case '#':
			return PitchClass::A_Sharp;
		case '-':
		case 'b':
			return PitchClass::A_Flat;
		default:
			return PitchClass::A;
		}
	case 'B':
	case 'b':
		switch (Accidental)
		{
		case '+':
		case '#':
			return PitchClass::B_Sharp;
		case '-':
		case 'b':
			return PitchClass::B_Flat;
		default:
			return PitchClass::B;
		}
	case 'C':
	case 'c':
		switch (Accidental)
		{
		case '+':
		case '#':
			return PitchClass::C_Sharp;
		case '-':
		case 'b':
			return PitchClass::C_Flat;
		default:
			return PitchClass::C;
		}
	case 'D':
	case 'd':
		switch (Accidental)
		{
		case '+':
		case '#':
			return PitchClass::D_Sharp;
		case '-':
		case 'b':
			return PitchClass::D_Flat;
		default:
			return PitchClass::D;
		}
	case 'E':
	case 'e':
		switch (Accidental)
		{
		case '+':
		case '#':
			return PitchClass::E_Sharp;
		case '-':
		case 'b':
			return PitchClass::E_Flat;
		default:
			return PitchClass::E;
		}
	case 'F':
	case 'f':
		switch (Accidental)
		{
		case '+':
		case '#':
			return PitchClass::F_Sharp;
		case '-':
		case 'b':
			return PitchClass::F_Flat;
		default:
			return PitchClass::F;
		}
	case 'G':
	case 'g':
		switch (Accidental)
		{
		case '+':
		case '#':
			return PitchClass::G_Sharp;
		case '-':
		case 'b':
			return PitchClass::G_Flat;
		default:
			return PitchClass::G;
		}
	default:
		return PitchClass::None;
	}
}
