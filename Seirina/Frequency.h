/* Frequency.h: The frequency, in Hertz, of a sound wave
 *
 * Copyright 2019 Vincent Damewood
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

#if !defined FREQUENCY_H
#define FREQUENCY_H

namespace Seirina::Audio
{
    /*! \brief Represents the frequency of a sound wave
     */
    class Frequency
    {
    public:
        Frequency(double);
        operator double() const;
    private:
        double value;
    };
};

#endif /* FREQUENCY_H */
