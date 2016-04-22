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

void Output16(uint16_t output)
{
	for (int i = 0; i < 16; i += 8)
		putchar((output >> i) & 0xFF);
}

void Output32(const uint32_t output)
{
	for (int i = 0; i < 32; i += 8)
		putchar((output >> i) & 0xFF);
}

void OutputHeader(uint32_t SampleCount)
{
	uint32_t DataSize = 4 * SampleCount;

	Output32(0x46464952); // "RIFF"
	Output32(36 + DataSize); //Size of remaining file
	Output32(0x45564157); // "WAVE"

	Output32(0x20746D66); // "fmt "
	Output32(16); // Size of remaining section
	Output16(1); // PCM
	Output16(2); // Count of Channles (2 = stereo)
	Output32(44100); // Sample frequency
	Output32(176400); // Bytes per second
	Output16(4); // Bytes per sample for all channels
	Output16(16); // Bits per sample

	Output32(0x61746164); // "data"
	Output32(DataSize); // Size of the payload
}

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

	OutputHeader(3 * 44100);

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
		total ^= 0x8000; // Swich signed values to unsigned values

		Output16(total);
		Output16(total);
	}
}

