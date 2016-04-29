/* wave.c: Generate a C chord in various wave forms
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
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <math.h>

#include "waves.h"

#define peak (1<<15)

sample square(double phase)
{
	if (phase < 0.5)
		return peak;
	else
		return 0;
}

sample sine(double phase)
{
	double sine_value = sin(phase*M_PI*2);
	return (sample) ((sine_value+1)*(peak/2));
}

sample absine(double phase)
{
	double sine_value = sin(phase*M_PI);
	return (sample) (fabs(sine_value)*peak);
}

sample saw(double phase)
{
	return (sample) peak*phase;
}

sample triangle(double phase)
{
	return (phase <= 0.5)
		? peak * phase * 2
		: peak * (1.0-phase) * 2;
}
