/* AdsrTransform.h: The transoform applied by and ADSR envelope
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

#if !defined SEIRINA_ADSR_TRANSFORM_H
#define SEIRINA_ADSR_TRANSFORM_H

namespace Seirina
{
	/*! Represents the transform applied to a sound wave by an ADSR
	*  envelope. */
	class AdsrTransform
	{
		public:
		/*! Construct an AdsrTransorm object. */
		AdsrTransform(double value);

		/*! Convert to a double. */
		operator double() const;
	private:
		double value;
	};
};

#endif // SEIRINA_ADSR_TRANSFORM_H
