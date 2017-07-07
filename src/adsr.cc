/* adsr.cc: Attack/Decay/Sustain/Release Envelops
 *
 * Copyright 2017 Vincent Damewood
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

#include "adsr.h"

AdsrEnvelope::AdsrEnvelope(
	int newAttack,
	int newDecay,
	double newSustain,
	int newRelease):
	attack(newAttack),
	decay(newDecay),
	sustain(newSustain),
	release(newRelease)
{
}

double AdsrEnvelope::GetSample(int position, int duration)
{
	if (position <= attack)
		return static_cast<double>(position)/static_cast<double>(attack);
	else if (position <= (attack+decay))
		return 1.0
			- static_cast<double>(position - attack)
			* (1.0 - sustain)
			/ static_cast<double>(decay);
	else if (position <= duration)
		return sustain;
	else
		return sustain * static_cast<double>(position-duration)
			/ static_cast<double>(release);
}








