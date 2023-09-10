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

#if !defined SEIRINA_ADSR_ENVELOPE_H
#define SEIRINA_ADSR_ENVELOPE_H

#include <memory>

#include <Seirina/AdsrTransform.h>
#include <Seirina/SampleDuration.h>
#include <Seirina/SampleIndex.h>

typedef int TimeDuration;

namespace Seirina::Audio
{
	/*! Represents the attack, decay, sustain, and release of a note
	 *  played in music. */
	class AdsrEnvelope
	{
	public:
		/*! Constust a new ADSR Envelope. */
		AdsrEnvelope(TimeDuration Attack, TimeDuration Decay,
			AdsrTransform Sustain, TimeDuration Release);
		AdsrEnvelope(const AdsrEnvelope&);
		~AdsrEnvelope();

		TimeDuration getAttack();
		TimeDuration getDecay();
		AdsrTransform getSustain();
		TimeDuration getRelease();
	private:
		class PImpl;
		const std::unique_ptr<PImpl> p;
	};
}

#endif // SEIRINA_ADSR_ENVELOPE_H
