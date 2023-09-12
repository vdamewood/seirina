/* adsr.cc: Attack/Decay/Sustain/Release Envelops
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

#include <Seirina/AdsrEnvelope.h>
#include <Seirina/SampleDuration.h>

namespace Seirina
{
	class AdsrEnvelope::PImpl
	{
	public:
		PImpl(TimeDuration a, TimeDuration d, AdsrTransform s, TimeDuration r)
			: attack(a), decay(d), sustain(s), release(r)
		{
		}
		TimeDuration attack;
		TimeDuration decay;
		AdsrTransform sustain;
		TimeDuration release;
	};

	AdsrEnvelope::AdsrEnvelope(
		TimeDuration newAttack,
		TimeDuration newDecay,
		AdsrTransform newSustain,
		TimeDuration newRelease)
		: p(new PImpl(newAttack, newDecay, newSustain, newRelease))
	{
	}

	AdsrEnvelope::AdsrEnvelope(const AdsrEnvelope& other)
		: p{std::make_unique<PImpl>(
			other.p->attack,
			other.p->decay,
			other.p->sustain,
			other.p->release)}
	{
	}

	AdsrEnvelope::~AdsrEnvelope()
	{
	}

	TimeDuration AdsrEnvelope::getAttack()
	{
		return p->attack;
	}

	TimeDuration AdsrEnvelope::getDecay()
	{
		return p->decay;
	}

	AdsrTransform AdsrEnvelope::getSustain()
	{
		return p->sustain;
	}

	TimeDuration AdsrEnvelope::getRelease()
	{
		return p->release;
	}


	/*
	AdsrTransform AdsrEnvelope::GetTransform(SampleIndex position, SampleDuration duration)
	{
		duration -= p->release;
		if (position < p->attack)
			return static_cast<double>(position)/static_cast<double>(p->attack);
		else if (position < (p->attack+p->decay))
			return 1.0
				- static_cast<double>(position - p->attack)
				* (1.0 - p->sustain)
				/ static_cast<double>(p->decay);
		else if (position <= duration)
			return p->sustain;
		else
			return p->sustain - (static_cast<double>(position-duration)
				/ static_cast<double>(p->release));
	}
	*/
};
