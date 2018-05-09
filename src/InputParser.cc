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

enum class State
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
	char NoteLetter = ' ';
	char NoteAccidental = ' ';
	int NoteOctave = 4;
	int NoteDuration = 1;
	State St = State::Letter;
	while (St != State::End)
	{
		int inChar = d->File->get();
		if (inChar == EOF)
			break;
		switch (St)
		{
		case State::Letter:
			switch (inChar)
			{
				case '=':
					St = State::Comment;
					break;
				case 'A':
				case 'B':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
				case 'G':
					NoteLetter = inChar;
					break;
			}
			if (St != State::Comment) St = State::Octave; // FIXME: Accidental
			break;
		case State::Octave:
			NoteOctave = inChar - '0';
			St = State::Duration;
			break;
		case State::Duration:
			switch (inChar)
			{
				case ',':
					break;
				default:
					NoteDuration = inChar - '0';
					St = State::LineBreak;
			}
			break;
		case State::Comment:
			if (inChar == '\n')
				St = State::Letter;
			break;
		case State::LineBreak:
			if ((inChar) == '\n')
				St = State::End;
		}
	}

	return Note(
		Pitch(
			MakePitchClass(NoteLetter, NoteAccidental),
			NoteOctave),
		NoteDuration);
}
