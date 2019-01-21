/* WaveForm.h: Represents a sound wave's form
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

#ifndef SEIRINA_WAVE_FORM_H
#define SEIRINA_WAVE_FORM_H

#include "Phase.h"
#include "AudioSample.h"

namespace Seirina::Audio
{
	/*! Interface for wave forms. */
	class WaveForm
	{
	public:
		/*! Destroy WaveForm object. */
		virtual ~WaveForm() { };

		/*! Get the sample at a particular phase of the wave form. */
		virtual Sample GetSample(Phase) = 0;
	};
};

#endif // SEIRINA_WAVE_FORM_H
