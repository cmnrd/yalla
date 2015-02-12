/**
 * @brief  C++ simavr wrapper class
 * @author Christian Menard
 * @date   2015-02-21
 */

/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Christian Menard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifdef SIMAVR
extern "C"
{
#include <avr/avr_mcu_section.h>
}
#endif

#include <avr/iomm.hpp>
#include <simavr.h>

#pragma once

namespace yalla
{

class Simavr
{
private:

	using CommandReg = IOMMPtr<uint8_t, SIMAVR_CMD_REG>;

public:

	static void startTrace()
	{
#ifdef SIMAVR
		CommandReg::write(SIMAVR_CMD_VCD_START_TRACE);
#endif
	}

	static void stopTrace()
	{
#ifdef SIMAVR
		CommandReg::write(SIMAVR_CMD_VCD_STOP_TRACE);
#endif
	}

};

} // namespace yalla
