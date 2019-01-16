/* SampleRate.h: Sample rates
 *
 * Copyright 2019 Vincent Damewood
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

#if !defined SAMPLE_RATE_H
#define SAMPLE_RATE_H

namespace Seirina::Audio
{
    /*! Represents the sampling rate of audio data.
     */
    class SampleRate
    {
    public:
        /*! Construct a SampleRate object */
        SampleRate(int);

        /*! Convert SampleRate to `int` */
        operator int() const;

        /*! CD-quality sampling rate (44100 Hz). */
        static const SampleRate Cd;
        /*! DVD-quality sampling rate (48000 Hz). */
        static const SampleRate Dvd;
    private:
        int value;
    };
};

#endif /* SAMPLE_RATE_H */
