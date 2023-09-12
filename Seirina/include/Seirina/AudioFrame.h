/* AudioFrame.h: Collection of audio samples
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

#if !defined SEIRINA_AUDIO_FRAME_H
#define SEIRINA_AUDIO_FRAME_H

#include <memory>

#include <Seirina/AudioSample.h>

namespace Seirina
{
	/*! Represent a frame of audio date. */
	class Frame
	{
	public:
		/*! Construct a monaural audio frame. */
		Frame(Sample);
		/*! Construct a binaural (stereo) audio frame. */
		Frame(
			Sample left,
			Sample right);
		~Frame();

		/*! Get number of channels in frame. */
		int FrameCount();

		/*! Access a specific channel value. */
		Sample operator[](int) const;
	private:
		class PImpl;
		const std::unique_ptr<PImpl> p;
	};
};

#endif // SEIRINA_AUDIO_FRAME_H
