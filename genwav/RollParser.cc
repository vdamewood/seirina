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

#include "RollParser.h"

using Seirina::Notation::PitchClass;
using Seirina::Notation::MakePitchClass;
using Seirina::Notation::Note;
using Seirina::Notation::Rest;
using Seirina::Notation::NoteDuration;


RollParserToken::RollParserToken (const RollParserToken& original)
	: item(original.item)
{
}


RollParserToken::RollParserToken (const Note& newNote)
	: item(newNote)
{
}

RollParserToken::RollParserToken (const Rest& newRest)
	: item(newRest)
{
}

RollParserToken::~RollParserToken()
{
}

bool RollParserToken::IsNote()
{
	return std::holds_alternative<Note>(item);
}

bool RollParserToken::IsRest()
{
	return std::holds_alternative<Rest>(item);
}

const Note& RollParserToken::GetNote()
{
	return std::get<Note>(item);
}

const Rest& RollParserToken::GetRest()
{
	return std::get<Rest>(item);
}

RollParserLine::RollParserLine(NoteDuration newDuration)
	: duration(newDuration)
{
}

RollParserLine& RollParserLine::AddToken(RollParserToken newToken)
{
	Tokens.push_back(newToken);
	return *this;
}

RollParser::RollParser(const std::string& Filename)
{
	File = new std::ifstream(Filename);
}

RollParser::~RollParser()
{
	File->close();
	delete File;
}

int RollParser::FetchInteger()
{
	std::string inLexeme;
	while(std::isdigit(static_cast<unsigned char>(File->peek())))
		inLexeme.push_back(File->get());
	return std::atoi(inLexeme.c_str());
}

NoteDuration RollParser::FetchDuration()
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

NoteDuration RollParser::FetchLineDuration()
{
	NoteDuration rVal = FetchDuration();
	if (File->peek() == ':')
		File->get();
	else
		throw SyntaxError();
	return rVal;
}

PitchClass RollParser::FetchPitchClass()
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

Octave RollParser::FetchOctave()
{
	return Octave(FetchInteger());
}

Note RollParser::FetchNote()
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

Rest RollParser::FetchRest()
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

RollParserToken RollParser::FetchToken()
{
	int nextChar = File->peek();
	if ((nextChar >= 'A' && nextChar <= 'G')
		|| (nextChar >= 'a' && nextChar <= 'g'))
	{
		return RollParserToken(FetchNote());
	}
	else if (nextChar == 'R'
		|| nextChar == 'r')
	{
		return RollParserToken(FetchRest());
	}
	else
	{
		throw SyntaxError();
	}
}

void RollParser::FetchEndOfLine()
{
	int inChar = File->get();
	if (inChar == '\r')
		inChar = File->get();
	if (inChar != '\n')
		throw SyntaxError();
}


RollParserToken RollParser::Fetch()
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

std::optional<RollParserLine> RollParser::FetchLine()
{
	while (File->peek() == '=')
		while(File->get() != '\n');

	if (File->eof())
	{
		return std::nullopt;
	}

	RollParserLine rVal(FetchLineDuration());
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
