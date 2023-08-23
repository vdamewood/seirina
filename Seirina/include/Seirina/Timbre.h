/* Timbre.h: A Synthesizer timbre (waveform and adsr envelope)
 *
 * Copyright 2023 Vincent Damewood
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

#if !defined SEIRINA_TIMBRE_H
#define SEIRINA_TIMBRE_H

#include <Seirina/Adsr.h>
#include <Seirina/WaveForm.h>

namespace Seirina::Audio
{
    class TimbrePrivate;
    class Timbre
    {
        public:
            Timbre(const char* newWaveName, AdsrEnvelope newAdsr);
            Timbre(WaveForm* newWaveForm, AdsrEnvelope newAdsr);
            Timbre(const Timbre&);
            ~Timbre();

            WaveForm* getWaveForm() const;
            AdsrEnvelope& GetAdsrEnvelope(); // FIXME: Constify this
        private:
            TimbrePrivate* p;
    };
}

#endif // SEIRINA_TIMBRE_H