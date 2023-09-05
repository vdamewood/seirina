/* SimpleWaves.cc: Simple functional wave forms
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

#ifndef SEIRINA_SIMPLE_WAVES_H
#define SEIRINA_SIMPLE_WAVES_H

#include <Seirina/WaveForm.h>

namespace Seirina::Audio
{
	/*! Represents an absolute-value-of-sine wave. */
	class AbsineWave : public WaveForm
	{
	public:
		/*! Get the sample at a particular phase of the absine wave. */
		virtual Sample GetSample(Phase) override;
	};

	/*! Represents a sawtooth wave. */
	class SawtoothWave : public WaveForm
	{
	public:
		/*! Get the sample at a particular phase of the sawtooth wave. */
		virtual Sample GetSample(Phase) override;
	};

	/*! Represents a sine wave. */
	class SineWave : public WaveForm
	{
	public:
		/*! Get the sample at a particular phase of the sine wave. */
		virtual Sample GetSample(Phase) override;
	};

	/*! Represents a square wave. */
	class SquareWave : public WaveForm
	{
	public:
		/*! Get the sample at a particular phase of the square wave. */
		virtual Sample GetSample(Phase) override;
	};

	/*! Represents a triangle wave. */
	class TriangleWave : public WaveForm
	{
	public:
		/*! Get the sample at a particular phase of the triangle wave. */
		virtual Sample GetSample(Phase) override;
	};

	/*! Look up simple waveform by name */
	WaveForm* GetWave(const char *WaveName);
};

#endif // SEIRINA_SIMPLE_WAVES_H
