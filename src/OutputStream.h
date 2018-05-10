/* OutputStream.h: Interface for outputting audio data
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

#ifndef OUTPUT_STREAM_H
#define OUTPUT_STREAM_H

class OutputStream
{
public:
	virtual void WriteFrame(short) = 0;
	virtual void WriteFrame(short, short) = 0;
	virtual ~OutputStream();
};


#endif /* OUTPUT_STREAM_H */
