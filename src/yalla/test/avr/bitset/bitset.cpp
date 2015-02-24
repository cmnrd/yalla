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

#include <avr/bitset.hpp>
#include <avr/io.hpp>
#include <simavr.hpp>
using namespace yalla;

volatile uint8_t a = 0xff;

using Set = BitSet<PORTD, 3, 2>;

using Set2 = BitSet<PORTC, 2, 5>;

using MultiSet = MultiRegBitSet<Set2, Set>;


int main()
{
	Simavr::startTrace();

	PORTD::write(0);

	Set::write(0xff);

	Simavr::cout << "PORTD::read(): " << PORTD::read() << " - should be 28\n";
	Simavr::cout << "Set::read(): " << Set::read() << " - should be 7\n";

	Set::write(2);

	Simavr::cout << "Set::read(): " << Set::read() << " - should be 2\n";

	PORTD::write(0b01010101);

	Simavr::cout << "Set::read(): " << Set::read() << " - should be 5\n";

	PORTD::write(0);

	MultiSet::write(21);

	Simavr::cout << "MultiSet::read(): " << MultiSet::read() << " - should be 21\n";

	Set2::write(3);
	Simavr::cout << "MultiSet::read(): " << MultiSet::read() << " - should be 29\n";

	PORTD::write(0x0);
	PORTC::write(0x0);

	Simavr::stopSimulation();

	while(true);

	return 0;
}
