/* OutputStream.h: Interface for outputting audio data
 *
 * Copyright 2016, 2019 Vincent Damewood
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

#ifndef SEIRINA_OUTPUT_STREAM_H
#define SEIRINA_OUTPUT_STREAM_H

#include "AudioFrame.h"

class OutputStream
{
public:
	virtual void WriteFrame(Seirina::Audio::Frame) = 0;
	virtual ~OutputStream();
};

inline OutputStream::~OutputStream() { }

#endif // SEIRINA_OUTPUT_STREAM_H
