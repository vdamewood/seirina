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

#include "InputParser.h"
#include "WaveFile.h"
#include "Timbre.h"

void NoteOut(Note note, Timbre timbre, OutputStream* stream)
{
	const int BeatLength = 18900; // 140 BPM: 44100*60/140
	for (int i = 0; i < BeatLength * note.Duration(); i++)
		stream->WriteFrame(timbre.GetFrame(note, i));
}

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

	while (1)
	{
		Note innote = Input.Fetch();
		if (innote.Pitch().Class() == PitchClass::None)
			break;
		else
			NoteOut(innote, MyTimbre, &myWaveFile);
	}
}
