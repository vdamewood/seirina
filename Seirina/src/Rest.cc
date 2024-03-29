/* Rest.cc: Musical rest
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

#include <Seirina/Rest.h>

namespace Seirina
{
	class Rest::PImpl
	{
	public:
		PImpl(NoteDuration newDuration)
			: duration(newDuration)
		{
		}

		NoteDuration duration;
	};

	Rest::Rest(NoteDuration newDuration)
		: p{std::make_unique<PImpl>(newDuration)}
	{
	}

	Rest::Rest(const Rest& src)
		: p{std::make_unique<PImpl>(src.p->duration)}
	{
	}

	Rest::~Rest()
	{
	}

	NoteDuration Rest::Duration() const
	{
		return p->duration;
	}
};
