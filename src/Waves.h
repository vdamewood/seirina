/* waves.h: Various waveforms
 *
 * Copyright 2016 Vincent Damewood
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef WAVES_H
#define WAVES_H

typedef double (*fpWave)(double);

float phase(float frequency, int sample);

double square(double phase);
double sine(double phase);
double absine(double phase);
double saw(double phase);
double triangle(double phase);

#endif /* WAVES_H */
