/**
 * @brief  Defines a Task's Context
 * @author Christian Menard
 * @date   2015-01-29
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
#include <inttypes.hpp>

namespace yalla
{

struct PACKED Context
{
	uint16_t pc;
	uint8_t  r0;
	uint8_t  sreg;
	uint8_t  r1;
	uint8_t  r2;
	uint8_t  r3;
	uint8_t  r4;
	uint8_t  r5;
	uint8_t  r6;
	uint8_t  r7;
	uint8_t  r8;
	uint8_t  r9;
	uint8_t  r10;
	uint8_t  r11;
	uint8_t  r12;
	uint8_t  r13;
	uint8_t  r14;
	uint8_t  r15;
	uint8_t  r16;
	uint8_t  r17;
	uint8_t  r18;
	uint8_t  r19;
	uint8_t  r20;
	uint8_t  r21;
	uint8_t  r22;
	uint8_t  r23;
	uint8_t  r24;
	uint8_t  r25;
	uint8_t  r26;
	uint8_t  r27;
	uint8_t  r28;
	uint8_t  r29;
	uint8_t  r30;
	uint8_t  r31;
};

} // namespace lunacy
