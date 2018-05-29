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

class AdsrEnvelope
{
public:
	AdsrEnvelope(int newAttack, int newDecay, double newSustain, int newRelease);
	double GetSample(int position, int duration);
private:
	int attack;
	int decay;
	double sustain;
	int release;
};
