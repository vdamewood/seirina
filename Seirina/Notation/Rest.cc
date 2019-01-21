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

#include "Rest.h"

namespace Seirina::Notation
{
	class RestPrivate
	{
	public:
		RestPrivate(int newDurationNumerator, int newDurationDenominator)
		: DurationNumerator(newDurationNumerator),
			DurationDenominator(newDurationDenominator)
		{
		}

		int DurationNumerator;
		int DurationDenominator;
	};

	Rest::Rest(int DurationNumerator, int DurationDenominator)
		: p(new RestPrivate(DurationNumerator, DurationNumerator))
	{
	}

	Rest::Rest(const Rest& rhs)
		: p(new RestPrivate(rhs.p->DurationNumerator, rhs.p->DurationNumerator))
	{
	}

	Rest::~Rest()
	{
		delete p;
	}

	double Rest::Duration() const
	{
		return static_cast<double>(p->DurationNumerator)
			/ static_cast<double>(p->DurationDenominator);
	}
};
