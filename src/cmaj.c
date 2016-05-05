/* cmaj.c: Generate a C chord in various wave forms
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

#include <string.h>

#include "output.h"
#include "waves.h"

#define noteC 261.6
#define noteE 329.6
#define noteG 392.0

#define SampleRate 44100

int main(int argc, char *argv[])
{
	fpWave wave = saw;

	if (argc == 2)
	{
		if (strcmp(argv[1], "sine") == 0)
			wave = sine;
		else if (strcmp(argv[1], "square") == 0)
			wave = square;
		else if (strcmp(argv[1], "absine") == 0)
			wave = absine;
		else if (strcmp(argv[1], "triangle") == 0)
			wave = triangle;
	}

	OutputHeader(3 * 44100);

	for (int i = 0; i < SampleRate*3; i++)
	{
		int total = 0
			+ wave(phase(noteC, i))
			+ ((i > SampleRate)
				? wave(phase(noteE, i-SampleRate))
				: 0)
			+ ((i > SampleRate * 2)
				? wave(phase(noteG, i-SampleRate*2))
				: 0);
		total /= 3;

		Output16(total);
		Output16(total);
	}
}

