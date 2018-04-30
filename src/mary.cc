/* mary.cc: Generate Mary Had a Little Lamb in various wave forms
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
#include <iostream>
#include <string>

#include "WaveFile.h"
#include "waves.h"

#define hstep 1.0594630943592951988208028

#define noteA 440.0
#define noteB (noteA * hstep * hstep)
#define noteG (noteA / hstep / hstep)
#define noteD (noteB * hstep * hstep * hstep)

#define BeatLength 18900 // 140 BPM: 44100*60/140

void NoteOut(fpWave wave, float note, int duration, OutputStream* stream)
{
	for (int i = 0; i < duration; i++)
	{
		unsigned int total = (wave(phase(note, i)) * 0x7FFF);

		stream->WriteFrame(total);
	}
}

int main(int argc, char *argv[])
{
	fpWave wave = sine;
	std::string WaveName = "sine";
	std::string InFileName = "input.txt";
	std::string OutFileName = "output.wav";


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
				if (std::strcmp(argv[arg], "sine") == 0)
				{
					wave = sine;
					WaveName = "sine";
				}
				else if (std::strcmp(argv[arg], "square") == 0)
				{
					wave = square;
					WaveName = "square";
				}
				else if (std::strcmp(argv[arg], "absine") == 0)
				{
					wave = absine;
					WaveName = "absine";
				}
				else if (std::strcmp(argv[arg], "saw") == 0)
				{
					wave = saw;
					WaveName = "saw";
				}
				else if (std::strcmp(argv[arg], "triangle") == 0)
				{
					wave = triangle;
					WaveName = "triangle";
				}
				else
				{
					std::cout << "Bad waveform\n";
					exit(1);
				}
				break;
			default:
				std::cout << "Bad flag\n";
				exit(1);
			}
		}
		else
		{
			std::cout << "Bad argument: " << argv[arg] << "\n";
			exit(1);
		}
	}

	WaveFile myWaveFile(OutFileName.c_str());

	NoteOut(wave, noteB, BeatLength, &myWaveFile);
	NoteOut(wave, noteA, BeatLength, &myWaveFile);
	NoteOut(wave, noteG, BeatLength, &myWaveFile);
	NoteOut(wave, noteA, BeatLength, &myWaveFile);

	NoteOut(wave, noteB, BeatLength, &myWaveFile);
	NoteOut(wave, noteB, BeatLength, &myWaveFile);
	NoteOut(wave, noteB, BeatLength*2, &myWaveFile);

	NoteOut(wave, noteA, BeatLength, &myWaveFile);
	NoteOut(wave, noteA, BeatLength, &myWaveFile);
	NoteOut(wave, noteA, BeatLength*2, &myWaveFile);

	NoteOut(wave, noteB, BeatLength, &myWaveFile);
	NoteOut(wave, noteD, BeatLength, &myWaveFile);
	NoteOut(wave, noteD, BeatLength*2, &myWaveFile);

	NoteOut(wave, noteB, BeatLength, &myWaveFile);
	NoteOut(wave, noteA, BeatLength, &myWaveFile);
	NoteOut(wave, noteG, BeatLength, &myWaveFile);
	NoteOut(wave, noteA, BeatLength, &myWaveFile);

	NoteOut(wave, noteB, BeatLength, &myWaveFile);
	NoteOut(wave, noteB, BeatLength, &myWaveFile);
	NoteOut(wave, noteB, BeatLength, &myWaveFile);
	NoteOut(wave, noteB, BeatLength, &myWaveFile);

	NoteOut(wave, noteA, BeatLength, &myWaveFile);
	NoteOut(wave, noteA, BeatLength, &myWaveFile);
	NoteOut(wave, noteB, BeatLength, &myWaveFile);
	NoteOut(wave, noteA, BeatLength, &myWaveFile);

	NoteOut(wave, noteG, BeatLength*4, &myWaveFile);
}
