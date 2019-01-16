/* AudioFrame.cc: Representation of momentary audio sample
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

#include "AudioFrame.h"

namespace Seirina::Audio
{
	//! @private
	class FramePrivate
	{
	public:
		double channels[2];
	};

	Frame::Frame(double input)
		: p(new FramePrivate())
	{
		p->channels[0] = p->channels[1] = input;
	}

	Frame::Frame(double left, double right)
		: p(new FramePrivate())
	{
		p->channels[0] = left;
		p->channels[1] = right;
	}

	Frame::~Frame()
	{
		delete p;
	}

	double Frame::Left() const
	{
		return p->channels[0];
	}

	double Frame::Right() const
	{
		return p->channels[1];
	}

	double Frame::Mono() const
	{
		return (p->channels[0] + p->channels[1]) / 2;
	}

	Frame Frame::operator*(double op) const
	{
		return Frame(p->channels[0] * op, p->channels[1] * op);
	}
};
