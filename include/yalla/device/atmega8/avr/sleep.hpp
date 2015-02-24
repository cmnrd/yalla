/**
 * @brief  Functions for controlling sleep modes
 * @author Christian Menard
 * @date   2015-02-22
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

#include <avr/bitset.hpp>
#include <avr/io.hpp>

namespace yalla
{

enum class SleepMode
{
	Idle              = 0b000,
	ADCNoiseReduction = 0b001,
	PowerDown         = 0b010,
	PowerSave         = 0b011,
	Standby           = 0b110,
};

/**
 * Go to sleep.
 *
 * This function set the sleep mode, enables sleep mode, enables interrupts,
 * and goes to sleep by executing 'sleep' instruction. After the MCU wakes up
 * sleep mode is disabled.
 *
 * @param  mode sleep mode
 */
void inline sleep(SleepMode mode)
{
	// TODO remove when implemented in io.hpp
	using SM = BitSet<MCUCR, 3, SM0::idx>;

	SM::write(static_cast<uint8_t>(mode));

	SE::set();

	asm volatile("sei     \n"
	             "sleep   \n");

	SE::clear();
}

/**
 * Go to sleep.
 *
 * This function set the sleep mode, enables sleep mode, and goes to sleep by
 * executing 'sleep' instruction. Caution: This function does not ensure that
 * interrupts are enabled and does not disable sleep when MCU wakes up.
 *
 * @param  mode sleep mode
 */
void inline sleep_unsafe(SleepMode mode)
{
	// TODO remove when implemented in io.hpp
	using SM = BitSet<MCUCR, 3, SM0::idx>;

	SM::write(static_cast<uint8_t>(mode));

	SE::set();

	asm volatile ("sleep");
}

} // namespace yalla
