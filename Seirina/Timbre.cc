/* Timbre.cc: Sound timbre handling
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

#include <cmath>
#include <map>
#include <string>

#include "Phase.h"
#include "SampleRate.h"
#include "Timbre.h"

using Seirina::Audio::Phase;

typedef double (*fpWave)(Phase);

static double square(Phase phase)
{
	return phase < 0.5 ? 1.0 : -1.0;
}

static double sine(Phase phase)
{
	return sin(phase * M_PI * 2);
}

static double absine(Phase phase)
{
	return fabs(sin((phase+1.0/6.0) * M_PI)) * 2.0 - 1.0;
}

static double saw(Phase phase)
{
	return fmod(phase + 0.5, 1.0) * 2.0 - 1.0;
}

static double triangle(Phase phase)
{
	double d = fmod(phase + 0.25, 1.0);
	return (d <= 0.5 ? d : 1.0 - d) * 4.0 - 1.0;
}

static std::map<std::string, fpWave> Waveforms
{
	{std::string("sine"), sine},
	{std::string("absine"), absine},
	{std::string("saw"), saw},
	{std::string("square"), square},
	{std::string("triangle"), triangle},
};

double phase(double frequency, int sample)
{
	using Seirina::Audio::SampleRate;
	double CycleLength = SampleRate::Cd/frequency;
	return std::fmod(sample, CycleLength)/CycleLength;
}

class Timbre::Pimpl
{
public:
	Pimpl(fpWave NewWaveForm)
	{
		Waveform = NewWaveForm;
	}

	fpWave Waveform;
};

Timbre::Timbre(const char* NewWaveFormName)
{
	fpWave NewWaveForm = Waveforms[std::string(NewWaveFormName)];
	p = new Pimpl(NewWaveForm);
}

Timbre::Timbre(const Timbre& src)
	: p(new Pimpl(src.p->Waveform))
{

}

Timbre::~Timbre()
{
	//delete p;
}

Seirina::Audio::Frame Timbre::GetFrame(Note note, int sequence)
{
	return Seirina::Audio::Frame(
		p->Waveform(phase(note.Pitch().Frequency(), sequence)));
}
