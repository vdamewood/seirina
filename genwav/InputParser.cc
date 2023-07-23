/* InputParser.cc: Parser for music input files
 *
 * Copyright 2018, 2019, 2023 Vincent Damewood
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

#include <Seirina/PitchClass.h>

#include "InputParser.h"

using Seirina::Notation::PitchClass;
using Seirina::Notation::MakePitchClass;
using Seirina::Notation::Note;
using Seirina::Notation::Rest;
using Seirina::Notation::Duration;


ParserToken::ParserToken ()
{
}


ParserToken::ParserToken (const Note& newNote)
	: note(newNote)
{
}

ParserToken::ParserToken (const Rest& newRest)
	: rest(newRest)
{
}

ParserToken::~ParserToken()
{
}

bool ParserToken::IsNote()
{
	return note.has_value();
}

bool ParserToken::IsRest()
{
	return rest.has_value();
}

InputParser::InputParser(const char* Filename)
{
	File = new std::ifstream(Filename);
}

InputParser::~InputParser()
{
	File->close();
	delete File;
}

ParserToken InputParser::Fetch()
{
	char NoteLetter = ' ';
	char NoteAccidental = ' ';
	int NoteOctave = 4;
	int DurationDenominator = 1;
	int DurationNumerator = 1;

	int inChar = File->get();

	if (inChar == EOF)
		return ParserToken();


	if (inChar == '=')
	{
		while((inChar = File->get()) != '\n');
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
	case 'R':
		NoteLetter = inChar;
		break;
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'r':
		NoteLetter = inChar - ('a' - 'A');
		break;
	default:
		return ParserToken();
	}

	if (NoteLetter != 'R')
	{
		switch (inChar = File->get())
		{
			case '-':
			case '+':
			case 'b':
			case '#':
			case ' ':
				NoteAccidental = inChar;
				inChar = File->get();
		}


		NoteOctave = inChar - '0';
		if (inChar < '0' || inChar > '9')
			return ParserToken();
		NoteOctave = inChar - '0';
	}

	inChar = File->get();
	if (inChar != '-')
		return ParserToken();


	inChar = File->get();
	if (inChar < '0' || inChar > '9')
		return ParserToken();
	DurationNumerator = inChar - '0';


	inChar = File->get();
	if (inChar == '/')
	{
		inChar = File->get();
		if (inChar < '1' || inChar > '9')
			return ParserToken();
		DurationDenominator = inChar - '0';
		inChar = File->get();
	}


	if (inChar == '\r')
		inChar = File->get();
	if (inChar != '\n')
		return ParserToken();

	if (NoteLetter != 'R')
		return ParserToken(Note(
			MakePitchClass(NoteLetter, NoteAccidental),
			NoteOctave, Duration(
			DurationNumerator,
			DurationDenominator)));
	else
		return ParserToken(Rest(
			Duration(
				DurationNumerator,
				DurationDenominator)));
}
