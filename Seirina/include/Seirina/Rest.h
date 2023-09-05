/* Rest.h: Musical rest
 *
 * Copyright 2018, 2019 Vincent Damewood
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

#if !defined SEIRINA_NOTATION_REST_H
#define SEIRINA_NOTATION_REST_H

#include <Seirina/NoteDuration.h>

namespace Seirina::Notation
{
	class RestPrivate;
	/*! A rest in musical notation */
	class Rest
	{
	public:
		/*! Construct a Rest object */
		Rest(NoteDuration);
		/*! Copy constructor */
		Rest(const Rest&);
		/*! Destructor */
		~Rest();

		/*! Get the duration of the Rest */
		NoteDuration Duration() const;
	private:
		RestPrivate* p;
	};
};

#endif // SEIRINA_NOTATION_REST_H
