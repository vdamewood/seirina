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
#include <Seirina/RollLine.h>

using Seirina::NoteDuration;
using Seirina::Note;
using Seirina::Octave;
using Seirina::PitchClass;
using Seirina::Rest;


class RollParser
{
public:
	RollParser(const std::string& FileName);
	~RollParser();

	std::optional<Seirina::RollLine> FetchLine();

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
	std::variant<Rest,Note> FetchToken();

	std::ifstream* File;
};

class SyntaxError
{

};

#endif // ROLL_PARSER_H
