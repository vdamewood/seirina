/* genwav.cc: Generate music as a wav file
 *
 * Copyright 2016, 2018, 2019 Vincent Damewood
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

#include <Seirina/SynthNote.h>
#include <Seirina/Silence.h>
#include <Seirina/SimpleWaves.h>
#include <Seirina/Tuning.h>

#include "InputParser.h"
#include "WaveFile.h"

// FIXME: these shouldn't be constants here
const int BeatLength = 18900; // 140 BPM: 44100*60/140
const int ReleaseLength = BeatLength/4;

using Seirina::Audio::Silence;
using Seirina::Audio::SynthNote;

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

	Seirina::Audio::WaveForm* MyWave =
		Seirina::Audio::GetWave(WaveName.c_str());
	InputParser Input(InFileName.c_str());
	WaveFile myWaveFile(OutFileName.c_str());

	Seirina::Notation::Tuning myTuning(Seirina::Notation::PitchClass::A, 440.0);
	int i = 0;
	while (1)
	{
		ParserToken token = Input.Fetch();
		if (token.IsNote())
		{
			std::unique_ptr<Note> innote = token.ExtractNote();
			SynthNote pNote(
				innote->Frequency(myTuning),
				BeatLength * innote->Duration(),
				Seirina::Audio::AdsrEnvelope(0, 0, 1.0, ReleaseLength),
				MyWave,
				Seirina::Audio::SampleRate::Cd);
			while (pNote.IsActive())
			{
				Seirina::Audio::Sample sample = pNote.NextSample();
				myWaveFile.WriteFrame(
					Seirina::Audio::Frame(sample, sample)
				);
			}
		}
		else if (token.IsRest())
		{
			std::unique_ptr<Rest> inrest = token.ExtractRest();
			Silence s(BeatLength * inrest->Duration());
			while (s.IsActive())
			{
				Seirina::Audio::Sample sample = s.NextSample();
				myWaveFile.WriteFrame(
					Seirina::Audio::Frame(sample, sample)
				);
			}
		}
		else
			break;
	}
}
