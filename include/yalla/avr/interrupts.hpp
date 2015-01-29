/**
 * @brief  Methods for access to the global interrupt enable bit
 * @author Christian Menard
 * @date   2015-01-25
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

#include <attributes.hpp>
#include <avr/io.hpp>

namespace yalla
{

class Interrupts
{
private:
	using SREG = IOMMPtr<uint8_t, 0x3f>;
public:
	static void INLINE enableGlobally()      { asm volatile ("sei"); }
	static void INLINE disableGlobally()     { asm volatile ("cli"); }
	static bool INLINE areGloballyEnabled()  { return SREG::read() & (1 << 7); }
	static bool INLINE areGloballyDisabled() { return !(SREG::read() & (1 << 7)); }
};

} // namespace lunacy

