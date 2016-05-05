/* mary.c: Generate Mary Had a Little Lamb in various wave forms
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

#define hstep 1.0594630943592951988208028

#define noteA 400.0
#define noteB (noteA * hstep * hstep)
#define noteG (noteA / hstep / hstep)
#define noteD (noteB * hstep * hstep * hstep)

#define BeatLength 18900 // 140 BPM: 44100*60/140

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

	OutputHeader(BeatLength*30);

	NoteOut(wave, noteB, BeatLength);
	NoteOut(wave, noteA, BeatLength);
	NoteOut(wave, noteG, BeatLength);
	NoteOut(wave, noteA, BeatLength);

	NoteOut(wave, noteB, BeatLength);
	NoteOut(wave, noteB, BeatLength);
	NoteOut(wave, noteB, BeatLength*2);

	NoteOut(wave, noteA, BeatLength);
	NoteOut(wave, noteA, BeatLength);
	NoteOut(wave, noteA, BeatLength*2);

	NoteOut(wave, noteB, BeatLength);
	NoteOut(wave, noteD, BeatLength);
	NoteOut(wave, noteD, BeatLength*2);

	NoteOut(wave, noteB, BeatLength);
	NoteOut(wave, noteA, BeatLength);
	NoteOut(wave, noteG, BeatLength);
	NoteOut(wave, noteA, BeatLength);

	NoteOut(wave, noteB, BeatLength);
	NoteOut(wave, noteB, BeatLength);
	NoteOut(wave, noteB, BeatLength);
	NoteOut(wave, noteB, BeatLength);

	NoteOut(wave, noteA, BeatLength);
	NoteOut(wave, noteA, BeatLength);
	NoteOut(wave, noteB, BeatLength);
	NoteOut(wave, noteA, BeatLength);

	NoteOut(wave, noteG, BeatLength*4);
}

