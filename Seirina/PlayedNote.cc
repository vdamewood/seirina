/* PlayedNote.cc: A note with timbre
 *
 * Copyright 2018 Vincent Damewood
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

// FIXME: these shouldn't be constants here
const int BeatLength = 18900; // 140 BPM: 44100*60/140
const int ReleaseLength = BeatLength/4;

using Seirina::Audio::AdsrEnvelope;
using Seirina::Audio::SampleIndex;
using Seirina::Audio::SampleRate;

class PlayedNote::Pimpl
{
public:
	Pimpl(Note newNote, Seirina::Audio::WaveForm* newForm)
		: note(newNote), waveform(newForm), adsr(0, 0, 1.0, ReleaseLength)
	{ }
	Note note;
	Seirina::Audio::WaveForm* waveform;
	AdsrEnvelope adsr;
	int framePosition = 0;
	int frameLength = 0;
};

PlayedNote::PlayedNote(Note newNote, Seirina::Audio::WaveForm* newForm)
	: p(new Pimpl(newNote, newForm))
{
	p->frameLength = BeatLength * p->note.Duration();
}

PlayedNote::PlayedNote(const PlayedNote& src)
	: p(new Pimpl(src.p->note, src.p->waveform))
{
	p->frameLength = src.p->frameLength;
	p->framePosition = src.p->framePosition;
}

PlayedNote::~PlayedNote()
{
	delete p;
}

Seirina::Audio::Sample PlayedNote::NextSample()
{
	// FIXME: This needs to be cleaned up
	double framePosition = p->framePosition++;
	Seirina::Audio::Frequency frequency = p->note.Pitch().Frequency();
	double CycleLength = SampleRate::Cd/frequency;
	double phase = 	std::fmod(framePosition, CycleLength)/CycleLength;

	return
		p->waveform->GetSample(phase)
		* p->adsr.GetTransform(framePosition, p->frameLength - ReleaseLength);
}

bool PlayedNote::IsActive() const
{
	return p->framePosition < p->frameLength;

}
