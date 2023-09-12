/* RollLine.cc: A line of notes on a Roll
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

#include <Seirina/RollLine.h>


namespace Seirina
{
    RollLine::RollLine(NoteDuration newDuration)
        : duration(newDuration)
    {
    }

    RollLine& RollLine::add(std::variant<Rest, Note> input)
    {
        items.push_back(input);
        return *this;
    }

    RollLine& RollLine::add(Note input)
    {
        items.push_back(input);
        return *this;
    }

    RollLine& RollLine::add(Rest input)
    {
        items.push_back(input);
        return *this;
    }

    const NoteDuration& RollLine::getDuration()
    {
        return duration;
    }

    const std::vector<std::variant<Rest, Note>>& RollLine::getItems()
    {
        return items;
    }
};
