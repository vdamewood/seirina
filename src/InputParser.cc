/* InputParser.cc: Parser for music input files
 *
 * Copyright 2018 Vincent Damewood
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

#include <fstream>

#include "InputParser.h"

// Part of Note
#define hstep 1.0594630943592951988208028

#define noteA 440.0
#define noteG (noteA / hstep / hstep)
#define noteB (noteA * hstep * hstep)
#define noteC (noteB * hstep)
#define noteD (noteC * hstep * hstep)


class InputParserPrivate
{
public:
	std::ifstream* File;
};

InputParser::InputParser(const char* Filename)
{
	d = new InputParserPrivate();
	d->File = new std::ifstream(Filename);
}

InputParser::~InputParser()
{
	d->File->close();
	delete d->File;
	delete d;
}

enum State
{
	EndOfFile = 0,
	Letter = 1,
	Octave,
	Duration,
	LineBreak,
	Comment,
	End
};

Note InputParser::Fetch()
{
	Note rVal = {0.0, 0};

	State St = Letter;
	while (St != End)
	{
		int inChar = d->File->get();
		if (inChar == EOF)
			break;
		switch (St)
		{
		case Letter:
			switch (inChar)
			{
				case '=':
					St = Comment;
					break;
				case 'G':
					rVal.Pitch = noteG;
					break;
				case 'A':
					rVal.Pitch = noteA;
					break;
				case 'B':
					rVal.Pitch = noteB;
					break;
				case 'C':
					rVal.Pitch = noteC;
					break;
				case 'D':
					rVal.Pitch = noteD;
					break;
			}
			if (St != Comment) St = Octave;
			break;
		case Octave:
			// Ignore for now
			St = Duration;
			break;
		case Duration:
			switch (inChar)
			{
				case ',':
					break;
				default:
					rVal.Length = inChar - '0';
					St = LineBreak;
			}
			break;
		case Comment:
			if (inChar == '\n')
				St = Letter;
			break;
		case LineBreak:
			if ((inChar) == '\n')
				St = End;
		}
	}

	return rVal;
}
