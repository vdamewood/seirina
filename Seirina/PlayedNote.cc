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

#include "Adsr.h"
#include "Note.h"
#include "Timbre.h"

#include "PlayedNote.h"

// FIXME: these shouldn't be constants here
const int BeatLength = 18900; // 140 BPM: 44100*60/140
const int ReleaseLength = BeatLength/4;

class PlayedNote::Pimpl
{
public:
	Pimpl(Note newNote, Timbre newTimbre)
		: note(newNote), timbre(newTimbre), adsr(0, 0, 1.0, ReleaseLength)
	{ }
	Note note;
	Timbre timbre;
	AdsrEnvelope adsr;
	int framePosition = 0;
	int frameLength = 0;
};

PlayedNote::PlayedNote(Note newNote, Timbre newTimbre)
	: p(new Pimpl(newNote, newTimbre))
{
	p->frameLength = BeatLength * p->note.Duration();
}

PlayedNote::PlayedNote(const PlayedNote& src)
	: p(new Pimpl(src.p->note, src.p->timbre))
{
	p->frameLength = src.p->frameLength;
	p->framePosition = src.p->framePosition;
}

PlayedNote::~PlayedNote()
{
	delete p;
}

AudioFrame PlayedNote::NextFrame()
{
	double framePosition = p->framePosition++;
	AudioFrame f = p->timbre.GetFrame(p->note, framePosition);
	double s = p->adsr.GetSample(framePosition, p->frameLength - ReleaseLength);
	return f.Transform(s);
}

bool PlayedNote::IsActive() const
{
	return p->framePosition < p->frameLength;

}
