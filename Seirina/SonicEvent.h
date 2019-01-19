/* SonicEvent.h: Interface for things that make sound
 *
 * Copyright 2018 Vincent Damewood
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

#include "AudioFrame.h"

#if !defined SONIC_EVENT_H
#define SONIC_EVENT_H

class SonicEvent
{
public:
	virtual ~SonicEvent();
	virtual Seirina::Audio::Sample NextSample() = 0;
	virtual bool IsActive() const = 0;
};

inline SonicEvent::~SonicEvent() { }

#endif /* SONIC_EVENT_H */
