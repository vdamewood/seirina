/* Project.h: A song or compositional project
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

#if !defined SEIRINA_PROJECT_H
#define SEIRINA_PROJECT_H

#include <string>

#include <Seirina/Frequency.h>
#include <Seirina/Tempo.h>
#include <Seirina/Tuning.h>
#include <Seirina/PitchClass.h>
#include <Seirina/Voice.h>

namespace Seirina
{
    class ProjectPrivate;
    class Project
    {
    public:
        Project(Notation::Tempo, Notation::Tuning);
        Project(Notation::Tempo, Notation::PitchClass, Audio::Frequency);
        ~Project();

        template<class... Args>
        void addVoice(std::string voiceName, Args&&... args)
        {
            realAddVoice(voiceName, new Audio::Voice(std::forward<Args>(args)...));
        }

        const Notation::Tempo& getTempo();
        const Notation::Tuning& getTuning();
        Audio::Voice& getVoice(const std::string& voiceName);
    private:
        void realAddVoice(std::string, Audio::Voice*);
        ProjectPrivate* p;
    };
}

#endif // SEIRINA_PROJECT_H
