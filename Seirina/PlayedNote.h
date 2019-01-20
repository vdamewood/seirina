/* PlayedNote.h: A note with timbre
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

#if !defined SEIRINA_PLAYED_NOTE_H
#define SEIRINA_PLAYED_NOTE_H

#include "SonicEvent.h"
#include "Note.h"
#include "WaveForm.h"

class PlayedNote : public SonicEvent
{
public:
	PlayedNote(Note, Seirina::Audio::WaveForm*);
	PlayedNote(const PlayedNote&);
	~PlayedNote() override;

public: // SonicEvent
	Seirina::Audio::Sample NextSample() override;
	bool IsActive() const override;
private:
	class Pimpl;
	Pimpl* p;
};

#endif // SEIRINA_PLAYED_NOTE_H
