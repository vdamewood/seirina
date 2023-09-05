/* InputParser.cc: Parser for music input files
 *
 * Copyright 2016-2019, 2023 Vincent Damewood
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
#include <cctype>

#include <Seirina/PitchClass.h>

#include "InputParser.h"

using Seirina::Notation::PitchClass;
using Seirina::Notation::MakePitchClass;
using Seirina::Notation::Note;
using Seirina::Notation::Rest;
using Seirina::Notation::NoteDuration;


ParserToken::ParserToken ()
{
}

ParserToken::ParserToken (const ParserToken& original)
{
	if (original.note.has_value())
		note = original.note.value();

	if (original.rest.has_value())
		rest = original.rest.value();

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

ParserLine::ParserLine(NoteDuration newDuration)
	: duration(newDuration)
{
}

ParserLine& ParserLine::AddToken(ParserToken newToken)
{
	Tokens.push_back(newToken);
	return *this;
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

int InputParser::FetchInteger()
{
	std::string inLexeme;
	while(std::isdigit(static_cast<unsigned char>(File->peek())))
		inLexeme.push_back(File->get());
	return std::atoi(inLexeme.c_str());
}

NoteDuration InputParser::FetchDuration()
{
	int numerator;
	if (std::isdigit(static_cast<unsigned char>(File->peek())))
		numerator = FetchInteger();
	else
		throw SyntaxError();

	if (File->peek() != '/')
		return NoteDuration(numerator, 1);
	File->get();

	int denominator;
	if (std::isdigit(static_cast<unsigned char>(File->peek())))
		denominator = FetchInteger();
	else
		throw SyntaxError();
	return NoteDuration{numerator, denominator};
}

NoteDuration InputParser::FetchLineDuration()
{
	NoteDuration rVal = FetchDuration();
	if (File->peek() == ':')
		File->get();
	else
		throw SyntaxError();
	return rVal;
}

PitchClass InputParser::FetchPitchClass()
{
	char inChar;
	char NoteLetter;
	switch (inChar = File->get())
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
		throw SyntaxError();
	}

	char NoteAccidental = ' ';
	switch (inChar = File->peek())
	{
	case '-':
	case '+':
	case 'b':
	case '#':
	case ' ':
		File->get();
		NoteAccidental = inChar;
	}

	return MakePitchClass(NoteLetter, NoteAccidental);
}

Octave InputParser::FetchOctave()
{
	return Octave(FetchInteger());
}

Note InputParser::FetchNote()
{
		PitchClass myClass = FetchPitchClass();
		Octave myOctave = FetchOctave();
		if (File->peek() == '-')
			File->get();
		else
			throw SyntaxError();

		NoteDuration myDuration = FetchDuration();
		return Note(myClass, myOctave, myDuration);
}

Rest InputParser::FetchRest()
{
	int inChar = File->peek();

	if (inChar == 'R'
		|| inChar == 'r')
	{
		File->get();
	}
	else
	{
		throw SyntaxError();
	}

	if (File->peek() == '-')
		File->get();
	else
		throw SyntaxError();

	return Rest(FetchDuration());
}

ParserToken InputParser::FetchToken()
{
	ParserToken rVal;

	int nextChar = File->peek();
	if ((nextChar >= 'A' && nextChar <= 'G')
		|| (nextChar >= 'a' && nextChar <= 'g'))
	{
		rVal.note = FetchNote();
	}
	else if (nextChar == 'R'
		|| nextChar == 'r')
	{
		rVal.rest = FetchRest();
	}

	return rVal;
	/*



	if (NoteLetter != 'R')
	{

	}



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

	/ *
	if (inChar == '\r')
		inChar = File->get();
	if (inChar != '\n')
		return ParserToken();
	*/
	/*
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
				*/
}

void InputParser::FetchEndOfLine()
{
	int inChar = File->get();
	if (inChar == '\r')
		inChar = File->get();
	if (inChar != '\n')
		throw SyntaxError();
}


ParserToken InputParser::Fetch()
{
	return FetchToken();
}

inline bool isNoteLetterOrRest(int input)
{
	return input - 'A' < 7
		|| input - 'a' < 7
		|| input == 'R'
		|| input == 'r';
}

std::optional<ParserLine> InputParser::FetchLine()
{
	while (File->peek() == '=')
		while(File->get() != '\n');

	if (File->eof())
	{
		return std::nullopt;
	}

	ParserLine rVal(FetchLineDuration());
	ParserToken inToken;
	while (isNoteLetterOrRest(File->peek()))
	{
		rVal.AddToken(FetchToken());
		int nextChar = File->peek();
		if (nextChar == ':')
			File->get();
		else if (nextChar == '\r' || nextChar == '\n')
			break;
	}

	FetchEndOfLine();
	return rVal;
}
