/**
 * @brief  A collection of classes used to concatenate separate bits to a set.
 * @author Christian Menard
 * @date   2015-01-24
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
#include <util/bits.hpp>

namespace yalla
{

template<typename _Reg, uint8_t _bitCount, uint8_t _idx>
struct BitSet
{
	using Reg = _Reg;
	static constexpr uint8_t bitCount = _bitCount;
	static constexpr uint8_t idx = _idx;

	static_assert(idx < 8, "Index is too large!");
	static_assert(bitCount + idx < 8, "Too many bits!");

	static void write(uint8_t v)
	{
		uint8_t tmp = Reg::read();
		v &= bitMask(bitCount);
		tmp &= ~bitMask(bitCount, idx);
		tmp |=  v << idx;
		Reg::write(tmp);
	}

	static uint8_t read()
	{
		uint8_t tmp = Reg::read();
		tmp = tmp >> idx;
	 	return tmp & bitMask(_bitCount);
	}
};

template<typename _Set1, typename _Set0>
struct MultiRegBitSet
{
	using Set1 = _Set1;
	using Set0 = _Set0;

	static void write(uint8_t v)
	{
		Set0::write(v);
		Set1::write(v >> Set0::bitCount);
	}

	static uint8_t read()
	{
		uint8_t tmp = Set0::read();
		tmp |= Set1::read() << Set0::bitCount;
	 	return tmp;
	}
};

} // namespace yalla
