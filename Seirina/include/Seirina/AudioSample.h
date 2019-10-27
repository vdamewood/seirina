/* AudioSample.h: Momentary audio amplitude
 *
 * Copyright 2016, 2018, 2019 Vincent Damewood
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

#if !defined SEIRINA_AUDIO_SAMPLE_H
#define SEIRINA_AUDIO_SAMPLE_H

#include <Seirina/AdsrTransform.h>

namespace Seirina::Audio
{
	/*! Represent a sample of audio date. */
	class Sample
	{
	public:
		/*! Construct a sample. */
		Sample(double);

		/*! Convert to double. */
		operator double() const;
		/*! Transform the sample with an ADSR value. */
		Sample operator*(AdsrTransform) const;
	private:
		double value;
	};
};

#endif // SEIRINA_AUDIO_SAMPLE_H
