/* PlayedNote.h: A note with timbre
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

#if !defined PLAYED_NOTE_H
#define PLAYED_NOTE_H

#include "SonicEvent.h"
#include "Note.h"
#include "Timbre.h"

class PlayedNote : public SonicEvent
{
public:
	PlayedNote(Note, Timbre);
	PlayedNote(const PlayedNote&);
	~PlayedNote() override;

public: // SonicEvent
	AudioFrame NextFrame() override;
	bool IsActive() const override;
private:
	class Pimpl;
	Pimpl* p;
};

#endif // PLAYED_NOTE_H
