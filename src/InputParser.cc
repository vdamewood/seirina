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
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * permissions and limitations under the License.
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

Note InputParser::Fetch()
{
	char NoteLetter = ' ';
	char NoteAccidental = ' ';
	int NoteOctave = 4;
	int DurationDenominator = 1;
	int DurationNumerator = 1;

	int inChar = d->File->get();

	if (inChar == EOF)
		return Note(Pitch(MakePitchClass(' ', ' '), 4), 1);


	if (inChar == '=')
	{
		while((inChar = d->File->get()) != '\n');
		return Fetch();
	}


	switch (inChar)
	{
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
		NoteLetter = inChar;
		break;
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
		NoteLetter = inChar - ('a' - 'A');
		break;
	default:
		return Note(Pitch(MakePitchClass(' ', ' '), 4), 1);
	}


	switch (inChar = d->File->get())
	{
		case '-':
		case '+':
		case 'b':
		case '#':
		case ' ':
			NoteAccidental = inChar;
			inChar = d->File->get();
	}


	NoteOctave = inChar - '0';
	if (inChar < '0' || inChar > '9')
		return Note(Pitch(MakePitchClass(' ', ' '), 4), 1);
	NoteOctave = inChar - '0';


	inChar = d->File->get();
	if (inChar != '-')
		return Note(Pitch(MakePitchClass(' ', ' '), 4), 1);


	inChar = d->File->get();
	if (inChar < '0' || inChar > '9')
		return Note(Pitch(MakePitchClass(' ', ' '), 4), 1);
	DurationNumerator = inChar - '0';


	inChar = d->File->get();
	if (inChar == '/')
	{
		inChar = d->File->get();
		if (inChar < '1' || inChar > '9')
			return Note(Pitch(MakePitchClass(' ', ' '), 4), 1);
		DurationDenominator = inChar - '0';
		inChar = d->File->get();
	}


	if (inChar == '\r')
		inChar = d->File->get();
	if (inChar != '\n')
		return Note(Pitch(MakePitchClass(' ', ' '), 4), 1);


	return Note(
		Pitch(
			MakePitchClass(NoteLetter, NoteAccidental),
			NoteOctave),
		DurationNumerator,
		DurationDenominator);
}
