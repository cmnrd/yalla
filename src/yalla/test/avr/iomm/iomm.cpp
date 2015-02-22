/**
 * @brief  Short test of IOMMPtr
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

#include <avr/iomm.hpp>
#include <simavr.hpp>
using namespace yalla;

using MYPORTD = IOMMPtr<uint8_t, 0x32>;
using MYPORTC = IOMMPtr<uint8_t, 0x35>;
using MYPORTB = IOMMPtr<uint8_t, 0x38>;

int main()
{
	Simavr::startTrace();

	MYPORTB::write(0x00);
	MYPORTC::write(0x00);
	MYPORTD::write(0x00);

	MYPORTD::write(0x01);
	MYPORTD::write(0x20);

	MYPORTB::write(0);

	MYPORTC::write(0x55);

	MYPORTB::write(MYPORTD::read());

	MYPORTC::deref() = MYPORTB::deref();

	MYPORTB::write(0x00);
	MYPORTC::write(0x00);
	MYPORTD::write(0x00);

	Simavr::stopSimulation();

	while(true);

	return 0;
}
