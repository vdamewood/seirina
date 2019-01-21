/* AdsrTransform.cc: The transoform applied by and ADSR envelope
 *
 * Copyright 2019 Vincent Damewood
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

#include <cmath>

#include "AdsrTransform.h"

static inline double clip(double i)
{
	return
		i < 0.0 ? 0.0
		: i > 1.0 ? 1.0
		: i;
}

namespace Seirina::Audio
{
	AdsrTransform::AdsrTransform(double newValue)
		: value(clip(newValue))
	{
	}

	AdsrTransform::operator double() const
	{
		return value;
	}
};