/**
 * @brief  Short timer test
 * @author Christian Menard
 * @date   2015-01-21
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

#include <avr/io.hpp>

namespace yalla
{
class Timer0
{
public:
	static void inline handleOvfl() __attribute__((__always_inline__))
	{
		PORTD::write(PORTD::read() + 1);
	}
};
}

#define YALLA_USER_CONFIG "/home/christian/yalla/src/yalla/test/avr/timer/config.hpp"

#include <avr/interrupts.hpp>
#include <simavr.hpp>
#include <avr/isr.hpp>
using namespace yalla;

int main()
{
	Simavr::startTrace();

	// enable Timer0 overflow interrupt
	TOIE0::set();
	// start Timer0, no prescaling
	CS0::write(0x01);

	Interrupts::enable();

	while(true)
	{
		if (PORTD::read() == 4)
			Simavr::stopSimulation();
	}
	return 0;
}
