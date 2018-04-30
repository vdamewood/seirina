/* cmaj.cc: Generate a C chord in various wave forms
 *
 * Copyright 2016 Vincent Damewood
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

#include <cstring>
#include <string>

#include "WaveFile.h"
#include "Waves.h"

#define noteC 261.6
#define noteE 329.6
#define noteG 392.0

#define SampleRate 44100

int main(int argc, char *argv[])
{
	fpWave wave = saw;
	std::string Filename = "cmaj-";

	if (argc == 2)
	{
		if (std::strcmp(argv[1], "sine") == 0)
		{
			wave = sine;
			Filename += "sine";
		}
		else if (std::strcmp(argv[1], "square") == 0)
		{
			wave = square;
			Filename += "square";
		}
		else if (std::strcmp(argv[1], "absine") == 0)
		{
			wave = absine;
			Filename += "absine";
		}
		else if (std::strcmp(argv[1], "triangle") == 0)
		{
			wave = triangle;
			Filename += "triangle";
		}
		else
		{
			Filename += "saw";
		}
	}
	else
	{
		Filename += "saw";
	}

	Filename += ".wav";

	WaveFile myFile(Filename.c_str());

	for (int i = 0; i < SampleRate*3; i++)
	{
		short total = (0
			+ wave(phase(noteC, i))
			+ ((i > SampleRate)
				? wave(phase(noteE, i-SampleRate))
				: 0)
			+ ((i > SampleRate * 2)
				? wave(phase(noteG, i-SampleRate*2))
				: 0))/3*0x7FFF;

		myFile.WriteFrame(total);
	}
}
