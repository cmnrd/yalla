/**
 * @brief  Define ISRs that call handlers that can be configured
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

#include <avr/isr_base.hpp>
#include <config.hpp>

// ATTENTION This file must not be included more then once per project!

YALLA_ISR(__vector_1,  __vector_1_isr,  yalla::Config::int0Isr);
YALLA_ISR(__vector_2,  __vector_2_isr,  yalla::Config::int1Isr);
YALLA_ISR(__vector_3,  __vector_3_isr,  yalla::Config::timer2CompIsr);
YALLA_ISR(__vector_4,  __vector_4_isr,  yalla::Config::timer2OvfIsr);
YALLA_ISR(__vector_5,  __vector_5_isr,  yalla::Config::timer1CaptIsr);
YALLA_ISR(__vector_6,  __vector_6_isr,  yalla::Config::timer1CompAIsr);
YALLA_ISR(__vector_7,  __vector_7_isr,  yalla::Config::timer1CompBIsr);
YALLA_ISR(__vector_8,  __vector_8_isr,  yalla::Config::timer1OvfIsr);
YALLA_ISR(__vector_9,  __vector_9_isr,  yalla::Config::timer0OvfIsr);
YALLA_ISR(__vector_10, __vector_10_isr, yalla::Config::spiStcIsr);
YALLA_ISR(__vector_11, __vector_11_isr, yalla::Config::usartRxcIsr);
YALLA_ISR(__vector_12, __vector_12_isr, yalla::Config::usartUdreIsr);
YALLA_ISR(__vector_13, __vector_13_isr, yalla::Config::usartTxcIsr);
YALLA_ISR(__vector_14, __vector_14_isr, yalla::Config::AdcIsr);
YALLA_ISR(__vector_15, __vector_15_isr, yalla::Config::eeRdyIsr);
YALLA_ISR(__vector_16, __vector_16_isr, yalla::Config::anaCompIsr);
YALLA_ISR(__vector_17, __vector_17_isr, yalla::Config::twiIsr);
YALLA_ISR(__vector_18, __vector_18_isr, yalla::Config::spmRdyIsr);
