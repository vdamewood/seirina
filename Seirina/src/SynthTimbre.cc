/* SynthTimbre.cc: A Synthesizer timbre (waveform and adsr envelope)
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
#include <Seirina/SynthTimbre.h>

using Seirina::Audio::WaveForm;

namespace Seirina
{
    class SynthTimbre::PImpl
    {
    public:
        PImpl(WaveForm* newWaveForm, AdsrTransformer newAdsr)
            : waveForm(newWaveForm), adsrTransformer(newAdsr)
        {

        }
        WaveForm* waveForm;
        AdsrTransformer adsrTransformer;
    };

    SynthTimbre::SynthTimbre(const std::string& newWaveName, AdsrTransformer newAdsr)
        : p(std::make_unique<PImpl>(Audio::GetWave(newWaveName), newAdsr))
    {

    }
    SynthTimbre::SynthTimbre(WaveForm* newWaveForm, AdsrTransformer newAdsr)
        : p(std::make_unique<PImpl>(newWaveForm, newAdsr))
    {
    }

    SynthTimbre::SynthTimbre(const SynthTimbre& src)
        : p(std::make_unique<PImpl>(src.p->waveForm, src.p->adsrTransformer))
    {
    }

    SynthTimbre::~SynthTimbre()
    {
    }

    WaveForm* SynthTimbre::getWaveForm() const
    {
        return p->waveForm;
    }
    AdsrTransformer& SynthTimbre::GetAdsrTransformer()
    {
        return p->adsrTransformer;
    }
}
