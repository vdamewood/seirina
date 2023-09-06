/* Timbre.cc: A Synthesizer timbre (waveform and adsr envelope)
 *
 * Copyright 2016-2019, 2023 Vincent Damewood
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

#include <Seirina/SimpleWaves.h>
#include <Seirina/Timbre.h>

namespace Seirina::Audio
{
    class TimbrePrivate
    {
    public:
        TimbrePrivate(WaveForm* newWaveForm, AdsrTransformer newAdsr)
            : waveForm(newWaveForm), adsrTransformer(newAdsr)
        {

        }
        WaveForm* waveForm;
        AdsrTransformer adsrTransformer;
    };

    Timbre::Timbre(const char* newWaveName, AdsrTransformer newAdsr)
        : p(new TimbrePrivate(GetWave(newWaveName), newAdsr))
    {

    }
    Timbre::Timbre(WaveForm* newWaveForm, AdsrTransformer newAdsr)
        : p(new TimbrePrivate(newWaveForm, newAdsr))
    {
    }

    Timbre::Timbre(const Timbre& src)
        : p(new TimbrePrivate(src.p->waveForm, src.p->adsrTransformer))
    {
    }

    Timbre::~Timbre()
    {
        delete p;
    }

    WaveForm* Timbre::getWaveForm() const
    {
        return p->waveForm;
    }
    AdsrTransformer& Timbre::GetAdsrTransformer()
    {
        return p->adsrTransformer;
    }
}
