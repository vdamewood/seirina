/* genwav.cc: Generate music as a wav file
 *
 * Copyright 2016, 2018, 2019, 2023 Vincent Damewood
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
#include <iostream>
#include <string>
#include <memory>

#include <Seirina/Project.h>
#include <Seirina/SynthNote.h>
#include <Seirina/Silence.h>
#include <Seirina/SimpleWaves.h>
#include <Seirina/Tempo.h>
#include <Seirina/Timbre.h>
#include <Seirina/Tuning.h>

#include "InputParser.h"
#include "WaveFile.h"

using Seirina::Project;
using Seirina::Audio::AdsrEnvelope;
using Seirina::Audio::Event;
using Seirina::Audio::Frame;
using Seirina::Audio::Frequency;
using Seirina::Audio::Silence;
using Seirina::Audio::SynthNote;
using Seirina::Audio::Timbre;
using Seirina::Notation::PitchClass;
using Seirina::Notation::Tempo;
using Seirina::Notation::Tuning;

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
				return 1;
			}
		}
		else
		{
			return 1;
		}
	}


	InputParser Input(InFileName.c_str());
	WaveFile myWaveFile(OutFileName.c_str());

	Project myProject{140, PitchClass::A, Frequency{440}};
	myProject.addTimbre("Melody", WaveName.c_str(), AdsrEnvelope(0, 0, 1.0, 4410));

	std::vector<std::unique_ptr<Event>> ActiveEvents;
	while (std::optional<ParserLine> line = Input.FetchLine())
	{
		for(ParserToken& token : line.value().Tokens)
		{
			if (token.IsNote())
			{
				ActiveEvents.push_back(std::make_unique<SynthNote>(
					token.note.value().Frequency(myProject.getTuning()),
					myProject.getTempo().getBeatLength(myWaveFile.GetSampleRate()) * token.note.value().Duration(),
					myProject.getTimbre("Melody"),
					myWaveFile.GetSampleRate()));
			}
			else if (token.IsRest())
			{
				ActiveEvents.push_back(std::make_unique<Silence>(
					myProject.getTempo().getBeatLength(myWaveFile.GetSampleRate()) * token.rest.value().Duration()));
			}
		}

		for (int i = 0;
			i <= static_cast<double>(line.value().duration) * myProject.getTempo().getBeatLength(myWaveFile.GetSampleRate());
			i++)
		{
			//std::vector<Seirina::Audio::Sample> samples;
			// FIXME: Need to remove inactive events from ActiveEvents

			// FIXME: Replace this with a real mix function.
			double MixSample = 0.0;
			for (std::unique_ptr<Event>& p : ActiveEvents)
			{
				if (p->IsActive())
					//samples.push_back(p->NextSample());
					MixSample += p->NextSample();
			}
			MixSample /= 4;
			myWaveFile.WriteFrame(Frame(MixSample, MixSample));
		}
	}
}
