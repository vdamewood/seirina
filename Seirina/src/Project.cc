/* Project.cc: A song or compositional project
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

#include <unordered_map>

#include <Seirina/Project.h>

namespace Seirina
{
    class ProjectPrivate
    {
    public:
        ProjectPrivate(Notation::Tempo newTempo, Notation::Tuning newTuning)
            : tempo(newTempo), tuning(newTuning)
        {
        }

        Notation::Tempo tempo;
        Notation::Tuning tuning;
        std::unordered_map<std::string, std::unique_ptr<Seirina::SynthTimbre>> timbres;
    };

    Project::Project(Notation::Tempo newTempo, Notation::Tuning newTuning)
        : p(new ProjectPrivate{newTempo, newTuning})
    {
    }

    Project::Project(Notation::Tempo newTempo, Notation::PitchClass newPitchClass, Audio::Frequency newFrequency)
        : Project(newTempo, Notation::Tuning{newPitchClass, newFrequency})
    {
    }

    Project::~Project()
    {
        delete p;
    }

    void Project::realAddTimbre(std::string timbreName, SynthTimbre* newTimbre)
    {
        p->timbres[timbreName] = std::unique_ptr<SynthTimbre>(newTimbre);
    }


    const Notation::Tempo& Project::getTempo()
    {
        return p->tempo;
    }

    const Notation::Tuning& Project::getTuning()
    {
        return p->tuning;
    }
    SynthTimbre& Project::getTimbre(const std::string& timbreName)
    {
        return *p->timbres[timbreName];
    }
}
