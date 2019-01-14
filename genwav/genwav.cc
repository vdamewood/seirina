/* genwav.cc: Generate music as a wav file
 *
 * Copyright 2016, 2018 Vincent Damewood
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

#include <cstring>
#include <string>
#include <iostream>

#include "InputParser.h"
#include "PlayedNote.h"
#include "Silence.h"
#include "WaveFile.h"
#include "Timbre.h"

int main(int argc, char *argv[])
{
	std::string WaveName("sine");
	std::string InFileName("input.txt");
	std::string OutFileName("output.wav");

	for (int arg = 1; arg < argc; arg++)
	{
		if (argv[arg][0] == '-')
		{
			switch (argv[arg][1])
			{
			case 'i':
				arg++;
				InFileName = argv[arg];
				break;
			case 'o':
				arg++;
				OutFileName = argv[arg];
				break;
			case 'w':
				arg++;
				WaveName = argv[arg];
				break;
			default:
				exit(1);
			}
		}
		else
		{
			exit(1);
		}
	}

	Timbre MyTimbre(WaveName.c_str());
	InputParser Input(InFileName.c_str());
	WaveFile myWaveFile(OutFileName.c_str());

	int i = 0;
	while (1)
	{
		ParserToken token = Input.Fetch();
		if (token.IsNote())
		{
			std::unique_ptr<Note> innote = token.ExtractNote();
			PlayedNote pNote(*innote, MyTimbre);
			while (pNote.IsActive())
				myWaveFile.WriteFrame(pNote.NextFrame());
		}
		else if (token.IsRest())
		{
			std::unique_ptr<Rest> inrest = token.ExtractRest();
			Silence s(inrest->Duration());
			while (s.IsActive())
				myWaveFile.WriteFrame(s.NextFrame());
		}
		else
			break;
	}
}
