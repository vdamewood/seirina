/* Rest.cc: Musical rest
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

#include <Seirina/Rest.h>

namespace Seirina::Notation
{
	class RestPrivate
	{
	public:
		RestPrivate(Duration newDuration)
			: duration(newDuration)
		{
		}

		Duration duration;
	};

	Rest::Rest(class Duration newDuration)
		: p(new RestPrivate(newDuration))
	{
	}

	Rest::Rest(const Rest& src)
		: p(new RestPrivate(src.p->duration))
	{
	}

	Rest::~Rest()
	{
		delete p;
	}

	Duration Rest::Duration() const
	{
		return p->duration;
	}
};
