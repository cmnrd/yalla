/**
 * @brief  Default ATmega8 Configuration
 * @author Christian Menard
 * @date   2015-03-01
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

namespace yalla
{

struct DefaultConfig
{
	static constexpr auto int0Isr        = static_cast<void(*)()>(nullptr);
	static constexpr auto int1Isr        = static_cast<void(*)()>(nullptr);
	static constexpr auto timer2CompIsr  = static_cast<void(*)()>(nullptr);
	static constexpr auto timer2OvfIsr   = static_cast<void(*)()>(nullptr);
	static constexpr auto timer1CaptIsr  = static_cast<void(*)()>(nullptr);
	static constexpr auto timer1CompAIsr = static_cast<void(*)()>(nullptr);
	static constexpr auto timer1CompBIsr = static_cast<void(*)()>(nullptr);
	static constexpr auto timer1OvfIsr   = static_cast<void(*)()>(nullptr);
	static constexpr auto timer0OvfIsr   = static_cast<void(*)()>(nullptr);
	static constexpr auto spiStcIsr      = static_cast<void(*)()>(nullptr);
	static constexpr auto usartRxcIsr    = static_cast<void(*)()>(nullptr);
	static constexpr auto usartUdreIsr   = static_cast<void(*)()>(nullptr);
	static constexpr auto usartTxcIsr    = static_cast<void(*)()>(nullptr);
	static constexpr auto AdcIsr         = static_cast<void(*)()>(nullptr);
	static constexpr auto eeRdyIsr       = static_cast<void(*)()>(nullptr);
	static constexpr auto anaCompIsr     = static_cast<void(*)()>(nullptr);
	static constexpr auto twiIsr         = static_cast<void(*)()>(nullptr);
	static constexpr auto spmRdyIsr      = static_cast<void(*)()>(nullptr);
};

} // namsepace yalla
