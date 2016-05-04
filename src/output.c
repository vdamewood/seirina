/* output.c: Output data
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
//#include <string.h>
#include <stdint.h>

#include "waves.h"

#define SampleRate 44100

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

	Output32(0x46464952);    // "RIFF"
	Output32(36 + DataSize); // Size of remaining file
	Output32(0x45564157);    // "WAVE"

	Output32(0x20746D66);    // "fmt "
	Output32(16);            // Size of remaining section
	Output16(1);             // PCM
	Output16(2);             // Count of Channles (2 = stereo)
	Output32(44100);         // Sample frequency
	Output32(176400);        // Bytes per second
	Output16(4);             // Bytes per sample for all channels
	Output16(16);            // Bits per sample

	Output32(0x61746164);    // "data"
	Output32(DataSize);      // Size of the payload
}

void NoteOut(fpWave wave, float note, int duration)
{
	for (int i = 0; i < duration; i++)
	{
		unsigned int total = wave(phase(note, i))
			^ 0x8000; // Swich signed values to unsigned values

		Output16(total);
		Output16(total);
	}
}
