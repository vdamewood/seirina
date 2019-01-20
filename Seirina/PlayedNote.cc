/* PlayedNote.cc: A note with timbre
 *
 * Copyright 2018, 2019 Vincent Damewood
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

#include "Adsr.h"
#include "Frequency.h"
#include "Note.h"
#include "SampleIndex.h"
#include "SampleRate.h"
#include "PlayedNote.h"

using Seirina::Audio::AdsrEnvelope;
using Seirina::Audio::Frequency;
using Seirina::Audio::SampleIndex;
using Seirina::Audio::SampleRate;
using Seirina::Audio::WaveForm;

class PlayedNote::Pimpl
{
public:
	Pimpl(
		Frequency new_frequency,
		int new_duration,
		AdsrEnvelope new_adsr,
		WaveForm* new_waveform,
		SampleRate new_sample_rate,
		SampleIndex new_idx=0)
		: frequency(new_frequency),
		frameLength(new_duration),
		adsr(new_adsr),
		waveform(new_waveform),
		sampleRate(new_sample_rate),
		CycleLength(new_sample_rate/new_frequency),
		framePosition(new_idx)
	{ }

	// Note: frequency and sampleRate are only used to calculate
	//  CycleLength at the moment, but might be useful later.
	AdsrEnvelope adsr;
	float CycleLength;
	WaveForm* waveform;
	SampleRate sampleRate;
	int frameLength;
	Frequency frequency;
	SampleIndex framePosition;
};

PlayedNote::PlayedNote(
	Frequency new_frequency,
	int new_duration,
	AdsrEnvelope new_adsr,
	WaveForm* new_waveform,
	SampleRate new_sample_rate)
	: p(new Pimpl(
		new_frequency,
		new_duration,
		new_adsr,
		new_waveform,
		new_sample_rate))
{
}

PlayedNote::PlayedNote(const PlayedNote& src)
	: p(new Pimpl(
		src.p->frequency,
		src.p->frameLength,
		src.p->adsr,
		src.p->waveform,
		src.p->sampleRate,
		src.p->framePosition))
{
}

PlayedNote::~PlayedNote()
{
	delete p;
}

Seirina::Audio::Sample PlayedNote::NextSample()
{
	SampleIndex idx = p->framePosition++;
	return
		p->waveform->GetSample(std::fmod(idx, p->CycleLength)/p->CycleLength)
		* p->adsr.GetTransform(idx, p->frameLength);
}

bool PlayedNote::IsActive() const
{
	return p->framePosition < p->frameLength;
}
