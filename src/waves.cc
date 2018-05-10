/* waves.cc: Various waveforms
 *
 * Copyright 2016 Vincent Damewood
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

#include "Waves.h"

#define SampleRate 44100
float phase(float frequency, int sample)
{
	float CycleLength = SampleRate/frequency;
	float p = std::fmod(sample, CycleLength)/CycleLength;
	return p;
}

double square(double phase)
{
	return phase < 0.5 ? 1.0 : -1.0;
}

double sine(double phase)
{
	return sin(phase * M_PI * 2);
}

double absine(double phase)
{
	return fabs(sin((phase+1.0/6.0) * M_PI)) * 2.0 - 1.0;
}

double saw(double phase)
{
	phase = fmod(phase + 0.5, 1.0);
	return phase * 2.0 - 1.0;
}

double triangle(double phase)
{
	phase = fmod(phase + 0.25, 1.0);
	return (phase <= 0.5 ? phase : 1.0 - phase) * 4.0 - 1.0;
}
