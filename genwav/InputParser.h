/* InputParser.h: Parser for music input files
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

#if !defined INPUT_PARSER_H
#define INPUT_PARSER_H

#include <vector>
#include <optional>

#include <Seirina/NoteDuration.h>
#include <Seirina/Note.h>
#include <Seirina/Octave.h>
#include <Seirina/PitchClass.h>
#include <Seirina/Rest.h>

using Seirina::Notation::NoteDuration;
using Seirina::Notation::Note;
using Seirina::Notation::Octave;
using Seirina::Notation::PitchClass;
using Seirina::Notation::Rest;

class ParserToken
{
public:
	ParserToken();
	ParserToken(const ParserToken&);
	ParserToken(const Note&);
	ParserToken(const Rest&);
	~ParserToken();

	bool IsNote();
	bool IsRest();
	// FIXME: std::variant!
	std::optional<Note> note;
	std::optional<Rest> rest;
};

class ParserLine
{
public:
	ParserLine(NoteDuration newDuration);
	ParserLine& AddToken(ParserToken);
//private:
	NoteDuration duration;
	std::vector<ParserToken> Tokens;
};
class InputParser
{
public:
	InputParser(const char* FileName);
	~InputParser();

	ParserToken Fetch();
	std::optional<ParserLine> FetchLine();

private:
	int FetchInteger();
	NoteDuration FetchDuration();
	PitchClass FetchPitchClass();
	Octave FetchOctave();
	Note FetchNote();
	Rest FetchRest();
	void FetchEndOfLine();

	int FetchVoice();
	NoteDuration FetchLineDuration();
	ParserToken FetchToken();

	std::ifstream* File;
};

class SyntaxError
{

};

#endif // INPUT_PARSER_H
