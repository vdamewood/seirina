/* Output.h: Interface for outputting audio data
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

#ifndef SEIRINA_OUTPUT_H
#define SEIRINA_OUTPUT_H

#include <Seirina/AudioFrame.h>

namespace Seirina
{
	/*! Interface for audio output */
	class Output
	{
	public:
		/*! Output a frame of audio data to the output */
		virtual void WriteFrame(Frame) = 0;

		/*! Get output device sample rate */
		virtual SampleRate GetSampleRate() = 0;

		/* destroy the output object */
		virtual ~Output() {};
	};
};

#endif // SEIRINA_OUTPUT_H
