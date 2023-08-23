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

#include <Seirina/Adsr.h>
#include <Seirina/Frequency.h>
#include <Seirina/SampleIndex.h>
#include <Seirina/SampleRate.h>
#include <Seirina/SynthNote.h>

namespace Seirina::Audio
{
	class SynthNotePrivate
	{
	public:
		SynthNotePrivate(
			Frequency new_frequency,
			SampleDuration new_duration,
			AdsrEnvelope new_adsr,
			WaveForm* new_waveform,
			SampleRate new_sample_rate,
			SampleIndex new_position=0)
			: frequency(new_frequency),
			duration(new_duration),
			adsr(new_adsr),
			waveform(new_waveform),
			sampleRate(new_sample_rate),
			cycleLength(new_sample_rate/new_frequency),
			position(new_position)
		{ }

		// Note: frequency and sampleRate are only used to calculate
		//  CycleLength at the moment, but might be useful later.
		AdsrEnvelope adsr;
		double cycleLength;
		WaveForm* waveform;
		SampleRate sampleRate;
		SampleDuration duration;
		Frequency frequency;
		SampleIndex position;
	};

	SynthNote::SynthNote(
		Frequency new_frequency,
		SampleDuration new_duration,
		Timbre new_timbre,
		SampleRate new_sample_rate)
		: p(new SynthNotePrivate(
			new_frequency,
			new_duration,
			new_timbre.GetAdsrEnvelope(),
			new_timbre.getWaveForm(),
			new_sample_rate))
	{
	}

	SynthNote::SynthNote(const SynthNote& src)
		: p(new SynthNotePrivate(
			src.p->frequency,
			src.p->duration,
			src.p->adsr,
			src.p->waveform,
			src.p->sampleRate,
			src.p->position))
	{
	}

	SynthNote::~SynthNote()
	{
		delete p;
	}

	Seirina::Audio::Sample SynthNote::NextSample()
	{
		SampleIndex idx = p->position++;
		return
			p->waveform->GetSample(std::fmod(idx, p->cycleLength)/p->cycleLength)
			* p->adsr.GetTransform(idx, p->duration);
	}

	bool SynthNote::IsActive() const
	{
		return p->position < p->duration;
	}
};
