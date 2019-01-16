/* AudioFrame.cc: Representation of momentary audio sample
 *
 * Copyright 2016, 2018 Vincent Damewood
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

#if !defined AUDIO_FRAME_H
#define AUDIO_FRAME_H

namespace Seirina::Audio
{
	class FramePrivate;

	/*! Represent a frame of audio date. */
	class Frame
	{
	public:
		/*! Construct a monaural audio frame. */
		Frame(double mono);
		/*! Construct a binaural (stereo) audio frame. */
		Frame(double left, double right);
		~Frame();

		/*! Access the left-channel value. */
		double Left() const;

		/*! Access the right-channel value. */
		double Right() const;

		/*! Access the monaural value. */
		double Mono() const;

		/*! Multiply the Frame object by a particular double. */
		Frame operator*(double right_hand_side) const;
	private:
		FramePrivate* const p;
	};
};

#endif /* AUDIO_FRAME_H */
