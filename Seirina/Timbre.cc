/* Timbre.cc: Sound timbre handling
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

#include <cmath>
#include <map>
#include <string>

#include "Phase.h"
#include "SampleRate.h"
#include "SimpleWaves.h"
#include "Timbre.h"

using Seirina::Audio::WaveForm;


class Timbre::Pimpl
{
public:
	Pimpl(WaveForm* NewWaveForm)
		: waveform(NewWaveForm)
	{
	}

	WaveForm* waveform;
};

Timbre::Timbre(const char* NewWaveFormName)
	: p(new Pimpl(Seirina::Audio::GetWave(NewWaveFormName)))
{
}

Timbre::Timbre(const Timbre& src)
	: p(new Pimpl(src.p->waveform))
{

}

Timbre::~Timbre()
{
	//delete p;
}

double phase(double frequency, int sample)
{
	using Seirina::Audio::SampleRate;
	double CycleLength = SampleRate::Cd/frequency;
	return std::fmod(sample, CycleLength)/CycleLength;
}

Seirina::Audio::Sample Timbre::GetSample(Note note, int sequence)
{
	return Seirina::Audio::Sample(
		p->waveform->GetSample(phase(note.Pitch().Frequency(), sequence)));
}
