/* RollLine.h: A line of notes on a Roll
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

#if !defined SEIRINA_ROLL_LINE_H
#define SEIRINA_ROLL_LINE_H

#include <vector>
#include <variant>

#include <Seirina/Note.h>
#include <Seirina/NoteDuration.h>
#include <Seirina/Rest.h>

namespace Seirina
{
    class RollLine
    {
    public:
        RollLine(Seirina::NoteDuration newDuration);

        RollLine& add(std::variant<Rest,Note>);
        RollLine& add(Seirina::Note);
        RollLine& add(Seirina::Rest);

        const Seirina::NoteDuration& getDuration();
        const std::vector<std::variant<
            Seirina::Rest,
            Seirina::Note>>& getItems();
    private:
        Seirina::NoteDuration duration;
        std::vector<std::variant<
            Seirina::Rest,
            Seirina::Note>> items;
    };
};

#endif // SEIRINA_ROLL_LINE_H