/* AudioEvent.h: Interface for things that make sound
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

#if !defined SEIRINA_AUDIO_EVENT_H
#define SEIRINA_AUDIO_EVENT_H

#include <Seirina/AudioSample.h>

namespace Seirina::Audio
{
	/*! Represents some occurance of sound */
	class Event
	{
	public:
		/*! Destroy Event object */
		virtual ~Event() { };

		/*! Get the current sample from the event, and advance to the
			next sample. */
		virtual Seirina::Audio::Sample NextSample() = 0;

		/*! Indicate if the event still has samples to return. */
		virtual bool IsActive() const = 0;
	};
};

#endif // SEIRINA_AUDIO_EVENT_H
