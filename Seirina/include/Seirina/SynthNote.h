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

#if !defined SEIRINA_SYNTH_NOTE_H
#define SEIRINA_SYNTH_NOTE_H

#include <Seirina/AdsrEnvelope.h>
#include <Seirina/AudioEvent.h>
#include <Seirina/Frequency.h>
#include <Seirina/SampleIndex.h>
#include <Seirina/SampleRate.h>
#include <Seirina/SynthTimbre.h>
#include <Seirina/WaveForm.h>

namespace Seirina
{
	/*! A note generated with synthesis */
	class SynthNote : public AudioEvent
	{
	public:
		/*! Construct a SynthNote object */
		SynthNote(
			Frequency,
			SampleDuration,
			SynthTimbre,
			SampleRate);
		/*! Copy constructor */
		SynthNote(const SynthNote&);
		/*! Destroy SynthNote object */
		~SynthNote() override;

	public: // AudioEvent overrides
		Sample NextSample() override;
		bool IsActive() const override;

	private:
		class PImpl;
		const std::unique_ptr<PImpl> p;
	};
};

#endif // SEIRINA_SYNTH_NOTE_H
