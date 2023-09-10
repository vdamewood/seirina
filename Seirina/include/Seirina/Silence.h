/* Silence.h: Play silence
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

#if !defined SEIRINA_AUDIO_SILENCE_H
#define SEIRINA_AUDIO_SILENCE_H

#include <memory>

#include <Seirina/AudioEvent.h>
#include <Seirina/SampleDuration.h>

namespace Seirina::Audio
{
	/*! Represents a period of silence. */
	class Silence : public Seirina::Audio::Event
	{
	public:
		/*! Construct a Silence object. */
		Silence(SampleDuration);
		/*! Copyc onstructor. */
		Silence(const Silence&);
		/*! Destructor. */
		~Silence() override;

	public: // Event
		Seirina::Audio::Sample NextSample() override;
		bool IsActive() const override;
	private:
		class PImpl;
		const std::unique_ptr<PImpl> p;
	};
};

#endif // SEIRINA_AUDIO_SILENCE_H
