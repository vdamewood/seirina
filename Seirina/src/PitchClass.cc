/* PitchClass.cc: Pitch Class in Musical Notation
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

#include <Seirina/PitchClass.h>

namespace Seirina
{
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
};
