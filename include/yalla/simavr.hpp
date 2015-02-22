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

#pragma once

#ifdef SIMAVR
extern "C"
{
#include <avr/avr_mcu_section.h>
}
#else
#define SIMAVR_CMD_VCD_START_TRACE 0
#define SIMAVR_CMD_VCD_STOP_TRACE 0
#endif

#include <avr/interrupts.hpp>
#include <avr/iomm.hpp>
#include <avr/sleep.hpp>
#include <simavr.h>
#include <util/ostream.hpp>

namespace yalla
{

#ifdef SIMAVR
constexpr bool simavr = true;
#else
constexpr bool simavr = false;
#endif

class Simavr
{
private:

	using CommandReg = IOMMPtr<uint8_t, SIMAVR_COMMAND_REG>;
	using ConsoleReg = IOMMPtr<uint8_t, SIMAVR_CONSOLE_REG>;

public:

	static void startTrace()
	{
		if(simavr)
			CommandReg::write(SIMAVR_CMD_VCD_START_TRACE);
	}

	static void stopTrace()
	{
		if(simavr)
			CommandReg::write(SIMAVR_CMD_VCD_STOP_TRACE);
	}

	static void stopSimulation()
	{
		if(simavr)
		{
			Interrupts::disable();
			sleep_unsafe(SleepMode::Idle);
		}
	}

	static void putc(char c)
	{
		if(simavr)
			ConsoleReg::write(c);
	}

	using OStreamType = OStream<simavr ? putc : nullptr>;

	static OStreamType cout;

};

} // namespace yalla
