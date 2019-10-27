/* WaveFile.cc: Output to .wav file
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

#include <fstream>

#include <Seirina/SampleRate.h>
#include "WaveFile.h"

using Seirina::Audio::SampleRate;

class WaveFilePrivate
{
public:
	void WriteSample(short output)
	{
		Output16(output);
		DataSize += 2;
	}

	void Output16(short output)
	{
		for (int i = 0; i < 16; i += 8)
			File->put((output >> i) & 0xFF);
	}

	void Output32(int output)
	{
		for (int i = 0; i < 32; i += 8)
			File->put((output >> i) & 0xFF);
	}

	void OutputHeader()
	{
		Output32(0x46464952);    // "RIFF"
		Output32(0);             // Size of remaining file (Placeholder)
		Output32(0x45564157);    // "WAVE"

		Output32(0x20746D66);    // "fmt "
		Output32(16);            // Size of remaining section
		Output16(1);             // PCM
		Output16(2);             // Count of Channles (2 = stereo)
		Output32(SampleRate::Cd); // Sample frequency
		Output32(176400);        // Bytes per second
		Output16(4);             // Bytes per sample for all channels
		Output16(16);            // Bits per sample

		Output32(0x61746164);    // "data"
		Output32(0);             // Size of the payload (placeholder)
	}

	std::ofstream* File;
	int DataSize = 0;
};

WaveFile::WaveFile(const char* filename)
{
	d = new WaveFilePrivate();
	d->File = new std::ofstream(filename);
	d->OutputHeader();
}

WaveFile::~WaveFile()
{
	d->File->seekp(4);
	d->Output32(36 + d->DataSize); // Size of remaining file
	d->File->seekp(40);
	d->Output32(d->DataSize);      // Size of the payload
	d->File->close();
	delete d;
}

#include <iostream>
using Seirina::Audio::Frame;
void WaveFile::WriteFrame(Frame frame)
{
	d->WriteSample(double(frame[0]) * 0x7FFF);
	d->WriteSample(double(frame[1]) * 0x7FFF);
}
