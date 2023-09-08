/* genwav.cc: Generate music as a wav file
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

#include <cstring>
#include <iostream>
#include <string>
#include <memory>
#include <variant>

#include <Seirina/AdsrTransformer.h>
#include <Seirina/Project.h>
#include <Seirina/RollLine.h>
#include <Seirina/SynthNote.h>
#include <Seirina/Silence.h>
#include <Seirina/SimpleWaves.h>
#include <Seirina/Tempo.h>
#include <Seirina/Timbre.h>
#include <Seirina/Tuning.h>

#include "RollParser.h"
#include "WaveFile.h"

using Seirina::Project;
using Seirina::AdsrTransformer;
using Seirina::Audio::AdsrEnvelope;
using Seirina::Audio::Event;
using Seirina::Audio::Frame;
using Seirina::Audio::Frequency;
using Seirina::RollLine;
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


	WaveFile myWaveFile(OutFileName);

	Project myProject{140, PitchClass::A, Frequency{440}};
	AdsrEnvelope envelope(0, 0, 1.0, 100);
	myProject.addTimbre("Melody", WaveName, AdsrTransformer(envelope, myWaveFile.GetSampleRate()));

	RollParser Input(InFileName);
	std::vector<RollLine> lines;
	while (std::optional<RollLine> line = Input.FetchLine())
		lines.push_back(line.value());

	std::vector<std::unique_ptr<Event>> ActiveEvents;
	for (auto& line : lines)
	{
		for(const auto& item : line.getItems())
		{
			std::visit([&ActiveEvents, &myProject, &myWaveFile](auto&& itemValue)
			{
				using Alt = std::decay_t<decltype(itemValue)>;
				if constexpr (std::is_same_v<Alt, Rest>)
					ActiveEvents.push_back(std::make_unique<Silence>(
						myProject.getTempo().getBeatLength(myWaveFile.GetSampleRate()) * itemValue.Duration()));
				if constexpr (std::is_same_v<Alt, Note>)
					ActiveEvents.push_back(std::make_unique<SynthNote>(
						itemValue.Frequency(myProject.getTuning()),
						myProject.getTempo().getBeatLength(myWaveFile.GetSampleRate()) * itemValue.Duration(),
						myProject.getTimbre("Melody"),
						myWaveFile.GetSampleRate()));
			}, item);
		}

		for (int i = 0;
			i <= static_cast<double>(line.getDuration()) * myProject.getTempo().getBeatLength(myWaveFile.GetSampleRate());
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
