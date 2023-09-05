/* AdsrEnvelope.h: Attack/Decay/Sustain/Release Envelops
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

#if !defined SEIRINA_ADSR_H
#define SEIRINA_ADSR_H

#include <Seirina/AdsrTransform.h>
#include <Seirina/SampleDuration.h>
#include <Seirina/SampleIndex.h>

namespace Seirina::Audio
{
	class AdsrEnvelopePrivate;

	/*! Represents the attack, decay, sustain, and release of a note
	 *  played in music. */
	class AdsrEnvelope
	{
	public:
		/*! Constust a new ADSR Envelope. */
		AdsrEnvelope(SampleDuration Attack, SampleDuration Decay,
			AdsrTransform Sustain, SampleDuration Release);

		/*! Get the value to transform the sound wave by at a particular
			position in the playing. */
		AdsrTransform GetTransform(SampleIndex, SampleDuration);
	private:
		AdsrEnvelopePrivate* p;
	};
}

#endif // SEIRINA_ADSR_H
