/* SampleDuration.h: Span of time in samples
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

#if !defined SEIRINA_SAMPLE_DURATION_H
#define SEIRINA_SAMPLE_DURATION_H

namespace Seirina::Audio
{
	/*! Represent an span of time in samples of audio date. */
	class SampleDuration
	{
	public:
		/*! Construct a sample duration. */
		SampleDuration(int);

		/*! Convert to integer. */
		operator int() const;

		/*! Subtract one duration for amother */
		SampleDuration operator-=(SampleDuration);
	private:
		int value;
	};
};

#endif // SEIRINA_SAMPLE_DURATION_H
