/* Voice.h: A Synthesizer voice (waveform and adsr envelope)
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

#if !defined SEIRINA_VOICE_H
#define SEIRINA_VOICE_H

#include <Seirina/Adsr.h>
#include <Seirina/WaveForm.h>

namespace Seirina::Audio
{
    class VoicePrivate;
    class Voice
    {
        public:
            Voice(const char* newWaveName, AdsrEnvelope newAdsr);
            Voice(WaveForm* newWaveForm, AdsrEnvelope newAdsr);
            Voice(const Voice&);
            ~Voice();

            WaveForm* getWaveForm() const;
            AdsrEnvelope& GetAdsrEnvelope(); // FIXME: Constify this
        private:
            VoicePrivate* p;
    };
}

#endif // SEIRINA_VOICE_H