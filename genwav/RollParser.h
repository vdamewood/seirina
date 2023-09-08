/* InputParser.h: Parser for music input files
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

#if !defined ROLL_PARSER_H
#define ROLL_PARSER_H

#include <vector>
#include <optional>
#include <string>

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

class RollParserToken
{
public:
	RollParserToken(const RollParserToken&);
	RollParserToken(const Note&);
	RollParserToken(const Rest&);
	~RollParserToken();

	bool IsNote();
	bool IsRest();
	const Note& GetNote();
	const Rest& GetRest();

private:
	std::variant<Note,Rest> item;
};

class RollParserLine
{
public:
	RollParserLine(NoteDuration newDuration);
	RollParserLine& AddToken(RollParserToken);
//private:
	NoteDuration duration;
	std::vector<RollParserToken> Tokens;
};

class RollParser
{
public:
	RollParser(const std::string& FileName);
	~RollParser();

	RollParserToken Fetch();
	std::optional<RollParserLine> FetchLine();

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
	RollParserToken FetchToken();

	std::ifstream* File;
};

class SyntaxError
{

};

#endif // ROLL_PARSER_H
