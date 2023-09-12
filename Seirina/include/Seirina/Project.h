/* Project.h: A song or compositional project
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

#if !defined SEIRINA_PROJECT_H
#define SEIRINA_PROJECT_H

#include <string>

#include <Seirina/Frequency.h>
#include <Seirina/SynthTimbre.h>
#include <Seirina/Tempo.h>
#include <Seirina/Tuning.h>
#include <Seirina/PitchClass.h>

namespace Seirina
{
    class Project
    {
    public:
        Project(Tempo, Tuning);
        Project(Tempo, PitchClass, Frequency);
        Project(const Project&);
        ~Project();

        template<class... Args>
        void addTimbre(std::string timbreName, Args&&... args)
        {
            realAddTimbre(timbreName, new SynthTimbre(std::forward<Args>(args)...));
        }

        const Tempo& getTempo();
        const Tuning& getTuning();
        SynthTimbre& getTimbre(const std::string& timbreName);
    private:
        void realAddTimbre(std::string, SynthTimbre*);
	private:
		class PImpl;
		const std::unique_ptr<PImpl> p;
    };
}

#endif // SEIRINA_PROJECT_H
