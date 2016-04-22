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

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

#define hstep 1.05946309436 // pow(2, 1/12)
#define noteC 261.6
#define noteE 329.6
#define noteG 392.0
#define SampleRate 44100

typedef uint16_t sample;
typedef sample (*fpWave)(double);

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
	//return (sample)(sine_value*peak);
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

float phase(float frequency, int sample)
{
	float CycleLength = SampleRate/frequency;
	float p = fmod(sample, CycleLength)/CycleLength;
	return p;
}

#include <stdint.h>

int main(int argc, char *argv[])
{
	fpWave wave = saw;

	if (argc == 2)
	{
		if (strcmp(argv[1], "sine") == 0)
			wave = sine;
		else if (strcmp(argv[1], "square") == 0)
			wave = square;
		else if (strcmp(argv[1], "absine") == 0)
			wave = absine;
		else if (strcmp(argv[1], "triangle") == 0)
			wave = triangle;
	}


	for (int i = 0; i < SampleRate*3; i++)
	{
		unsigned int total = 0
			+ wave(phase(noteC, i))
			+ ((i > SampleRate)
				? wave(phase(noteE, i-SampleRate))
				: 0)
			+ ((i > SampleRate * 2)
				? wave(phase(noteG, i-SampleRate*2))
				: 0);
		total /= 3;

		putchar(total & 0xFF);
		putchar(((total >> 8) & 0xFF)^0x80);
		putchar(total & 0xFF);
		putchar(((total >> 8) & 0xFF)^0x80);
	}
}

