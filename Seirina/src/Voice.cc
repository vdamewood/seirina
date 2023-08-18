/* Voice.cc: A Synthesizer voice (waveform and adsr envelope)
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

#include <Seirina/SimpleWaves.h>
#include <Seirina/Voice.h>

namespace Seirina::Audio
{
    class VoicePrivate
    {
    public:
        VoicePrivate(WaveForm* newWaveForm, AdsrEnvelope newEnvelope)
            : waveForm(newWaveForm), adsrEnvelope(newEnvelope)
        {

        }
        WaveForm* waveForm;
        AdsrEnvelope adsrEnvelope;
    };

    Voice::Voice(const char* newWaveName, AdsrEnvelope newEnvelope)
        : p(new VoicePrivate(GetWave(newWaveName), newEnvelope))
    {

    }
    Voice::Voice(WaveForm* newWaveForm, AdsrEnvelope newEnvelope)
        : p(new VoicePrivate(newWaveForm, newEnvelope))
    {
    }

    Voice::Voice(const Voice& src)
        : p(new VoicePrivate(src.p->waveForm, src.p->adsrEnvelope))
    {
    }

    Voice::~Voice()
    {
        delete p;
    }

    WaveForm* Voice::getWaveForm() const
    {
        return p->waveForm;
    }
    AdsrEnvelope& Voice::GetAdsrEnvelope()
    {
        return p->adsrEnvelope;
    }
}
