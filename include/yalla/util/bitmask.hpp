
/**
 * @brief  A simple temp
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

#pragma once

#include <inttypes.hpp>

namespace yalla
{

template<typename Reg, typename Bit0, typename...Bits>
struct __BitMaskHelper
{
	static_assert(Reg::addr == Bit0::Reg::addr,
	              "The specified bits do not belong to the same register!");

	static constexpr uint8_t mask =
		Bit0::bitMask | __BitMaskHelper<Reg, Bits...>::mask;
};

template<typename Reg, typename Bit0>
struct __BitMaskHelper<Reg, Bit0>
{
	static_assert(Reg::addr == Bit0::Reg::addr,
	              "The specified bits do not belong to the same register!");

	static constexpr uint8_t mask = Bit0::bitMask;
};

template<typename...Bits>
struct BitMask
{
};

template<>
struct BitMask<>
{
	static constexpr uint8_t mask = 0;
};

template<typename Bit0>
struct BitMask<Bit0>
{
	static constexpr uint8_t mask = Bit0::bitMask;
};

template<typename Bit0, typename...Bits>
struct BitMask<Bit0, Bits...>
{
	static constexpr uint8_t mask =
		Bit0::bitMask | __BitMaskHelper<typename Bit0::Reg, Bits...>::mask;
};

} // namespace yalla
