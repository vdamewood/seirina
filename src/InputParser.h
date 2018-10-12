/* InputParser.h: Parser for music input files
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

#if !defined INPUT_PARSER_H
#define INPUT_PARSER_H

#include <memory>

#include "Note.h"

class ParserToken
{
public:
	ParserToken ();
	ParserToken (std::unique_ptr<Note>);
	~ParserToken();

	bool hasEvent();
	std::unique_ptr<Note> ExtractNote();

private:
	class Pimpl;
	Pimpl* p;
};

class InputParserPrivate;
class InputParser
{
public:
	InputParser(const char* FileName);
	~InputParser();

	ParserToken Fetch();

private:
	InputParserPrivate* d;
};

#endif // INPUT_PARSER_H
