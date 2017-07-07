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
#include <string>

#include "WaveFile.hh"
#include "waves.hh"
#include "adsr.h"

#define hstep 1.0594630943592951988208028

#define noteA 400.0
#define noteB (noteA * hstep * hstep)
#define noteG (noteA / hstep / hstep)
#define noteD (noteB * hstep * hstep * hstep)

#define BeatLength 18900 // 140 BPM: 44100*60/140

void NoteOut(fpWave wave, float note, int duration, OutputStream* stream)
{
	int release = 0;
	AdsrEnvelope e(2000, 14000, 0.0, release);
	for (int i = 0; i < duration; i++)
	{
		unsigned int total = (wave(phase(note, i)) * e.GetSample(i, duration-release) *0x7FFF);

		stream->WriteFrame(total);
	}
}

int main(int argc, char *argv[])
{
	fpWave wave = saw;
	std::string Filename = "mary-";

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

	WaveFile myWaveFile(Filename.c_str());

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

