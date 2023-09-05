/* PlayedNote.h: A note with timbre
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

#if !defined SEIRINA_PLAYED_NOTE_H
#define SEIRINA_PLAYED_NOTE_H

#include <Seirina/AdsrEnvelope.h>
#include <Seirina/AudioEvent.h>
#include <Seirina/Frequency.h>
#include <Seirina/SampleIndex.h>
#include <Seirina/SampleRate.h>
#include <Seirina/Timbre.h>
#include <Seirina/WaveForm.h>

namespace Seirina::Audio
{
	class SynthNotePrivate;
	/*! A note generated with synthesis */
	class SynthNote : public Event
	{
	public:
		/*! Construct a SynthNote object */
		SynthNote(
			Frequency,
			SampleDuration,
			Timbre,
			SampleRate);
		/*! Copy constructor */
		SynthNote(const SynthNote&);
		/*! Destroy SynthNote object */
		~SynthNote() override;

	public: // Event
		Sample NextSample() override;
		bool IsActive() const override;
	private:
		SynthNotePrivate* p;
	};
};

#endif // SEIRINA_PLAYED_NOTE_H
