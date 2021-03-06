/**
 * @brief  simavr trace settings for iomm test
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

#ifdef SIMAVR

#include <avr/avr_mcu_section.h>
#include <avr/io.h>
#include <simavr.h>

AVR_MCU(F_CPU, MCU);

AVR_MCU_SIMAVR_COMMAND((void*)SIMAVR_COMMAND_REG);
AVR_MCU_SIMAVR_CONSOLE((void*)SIMAVR_CONSOLE_REG);

const struct avr_mmcu_vcd_trace_t _mytrace[] _MMCU_ =
{
	{ AVR_MCU_VCD_SYMBOL("PORTD"), .what = (void*)&PORTD},
	{ AVR_MCU_VCD_SYMBOL("PORTC"), .what = (void*)&PORTC},
	{ AVR_MCU_VCD_SYMBOL("PORTB"), .what = (void*)&PORTB},
};

#endif // SIMAVR
