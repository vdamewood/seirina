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

#include <cmath>
#include <map>
#include <string>

#include <Seirina/SimpleWaves.h>

namespace Seirina::Audio
{
	Sample AbsineWave::GetSample(Phase phase)
	{
		return fabs(sin((phase+1.0/6.0) * M_PI)) * 2.0 - 1.0;
	}

	Sample SawtoothWave::GetSample(Phase phase)
	{
		return fmod(phase + 0.5, 1.0) * 2.0 - 1.0;
	}

	Sample SineWave::GetSample(Phase phase)
	{
		return sin(phase * M_PI * 2);
	}

	Sample SquareWave::GetSample(Phase phase)
	{
		return phase < 0.5 ? 1.0 : -1.0;
	}

	Sample TriangleWave::GetSample(Phase phase)
	{
		double d = fmod(phase + 0.25, 1.0);
		return (d <= 0.5 ? d : 1.0 - d) * 4.0 - 1.0;
	}

	static std::map<std::string, WaveForm*> Waveforms
	{
		{std::string("sine"), new SineWave()},
		{std::string("absine"), new AbsineWave()},
		{std::string("saw"), new SawtoothWave()},
		{std::string("square"), new SquareWave()},
		{std::string("triangle"), new TriangleWave()},
	};

	WaveForm* GetWave(const char *WaveName)
	{
		try
		{
			return Waveforms.at(std::string(WaveName));
		}
		catch(std::out_of_range&)
		{
			return nullptr;
		}
	}
};
