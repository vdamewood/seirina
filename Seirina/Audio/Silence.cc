/* Silence.cc: Play silence
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

#include "Silence.h"

namespace Seirina::Audio
{
	class SilencePrivate
	{
	public:
		SilencePrivate(double newDuration)
			: duration(newDuration)
		{ }
		double duration;
		int framePosition = 0;
		int frameLength = 0;
	};

	Silence::Silence(double newDuration)
		: p(new SilencePrivate(newDuration))
	{
		p->frameLength = p->duration;
	}

	Silence::Silence(const Silence& src)
		: p(new SilencePrivate(src.p->duration))
	{
	}

	Silence::~Silence()
	{
		delete p;
	}

	Seirina::Audio::Sample Silence::NextSample()
	{
		p->framePosition++;
		return 0.0;
	}

	bool Silence::IsActive() const
	{
		return p->framePosition < p->frameLength;
	}
};
