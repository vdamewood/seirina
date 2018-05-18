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

#include "Note.h"
#include "Timbre.h"

#include "PlayedNote.h"

class PlayedNote::Pimpl
{
public:
	Pimpl(Note newNote, Timbre newTimbre)
		: note(newNote), timbre(newTimbre)
	{ }
	Note note;
	Timbre timbre;
	int framePosition = 0;
	int frameLength = 0;
};

// FIXME: this shouldn't be a constant here
const int BeatLength = 18900; // 140 BPM: 44100*60/140
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
	return p->timbre.GetFrame(p->note, p->framePosition++);
}

bool PlayedNote::IsActive() const
{
	return p->framePosition < p->frameLength;

}
