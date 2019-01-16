/* WaveFile.h: Output to .wav file
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

#ifndef WAVE_FILE_H
#define WAVE_FILE_H

#include "OutputStream.h"

class WaveFilePrivate;

class WaveFile : public OutputStream
{
public:
	WaveFile(const char* Filename);
	virtual void WriteFrame(Seirina::Audio::Frame);
	virtual ~WaveFile();
private:
	WaveFilePrivate *d;
};

#endif /* WAVE_FILE_H */
