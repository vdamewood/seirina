/* AdsrTransformer.cc: Applicator of ADSR Transformations
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

#include <Seirina/AdsrTransformer.h>
#include <Seirina/SampleDuration.h>

using Seirina::Audio::AdsrTransform;;
using Seirina::Audio::SampleDuration;
using Seirina::Audio::SampleIndex;

namespace Seirina
{

	class AdsrTransformer::PImpl
	{
	public:
		PImpl(
			SampleDuration newAttack,
			SampleDuration newDecay,
			AdsrTransform newSustain,
			SampleDuration newRelease)
			: attack(newAttack)
			, decay(newDecay)
			, sustain(newSustain)
			, release(newRelease)
		{
		}

		PImpl(Audio::AdsrEnvelope envelope, Audio::SampleRate rate)
			: attack(envelope.getAttack()*rate/100)
			, decay(envelope.getDecay()*rate/100)
			, sustain(envelope.getSustain())
			, release(envelope.getRelease()*rate/100)
		{
		}
		SampleDuration attack;
		SampleDuration decay;
		AdsrTransform sustain;
		SampleDuration release;
	};

	AdsrTransformer::AdsrTransformer(Audio::AdsrEnvelope envelope, Audio::SampleRate rate)
		: p{std::make_unique<PImpl>(envelope, rate)}
	{
	}

	AdsrTransformer::AdsrTransformer(const AdsrTransformer& original)
		: p{std::make_unique<PImpl>(
			original.p->attack,
			original.p->decay,
			original.p->sustain,
			original.p->release)}
	{
	}

	AdsrTransformer::~AdsrTransformer()
	{
	}

	AdsrTransform AdsrTransformer::GetTransform(SampleIndex position, SampleDuration duration)
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
};
