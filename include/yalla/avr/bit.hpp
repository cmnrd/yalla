/**
 * @brief  A collection of classes representing different kinds of bits in IO registers
 * @author Christian Menard
 * @date   2015-01-22
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

#include<attributes.hpp>
#include<inttypes.hpp>

namespace yalla
{

/**
 * Represents a reserved io bit.
 *
 * This class does not implement any functionality but is a base class for all
 * other bit classes.
 *
 * @tparam Reg        IOMMptr pointing to a 8-bit io register
 * @tparam idx        number of the bit with the register (0<=idx<=7)
 * @tparam regAndMask and-mask used to mask out read only bits when writing to
 *                    the register
 */
template<class Reg, uint8_t idx, uint8_t regAndMask>
struct ReservedBit
{
	///
	static constexpr uint8_t bitMask = 1 << idx;
	static constexpr uint8_t bitAndMask = static_cast<uint8_t>(~bitMask);

	static_assert(idx >= 0 && idx <= 7, "Index out of range! (0 <= idx <= 7)");
	static_assert(sizeof(typename Reg::Type) == 1, "Only 8-bit registers are supported!");
};

/**
 * Represents a io bit that may only be read.
 *
 * @tparam Reg        IOMMptr pointing to a 8-bit io register
 * @tparam idx        number of the bit with the register (0<=idx<=7)
 * @tparam regAndMask and-mask used to mask out read only bits when writing to
 *                    the register
 */
template<class Reg, uint8_t idx, uint8_t regAndMask>
struct ReadOnlyBit : public ReservedBit<Reg, idx, regAndMask>
{
	/// Alias for the base type.
	using Base = ReservedBit<Reg, idx, regAndMask>;

	/// Check if the bit is set.
	static bool INLINE isSet()     { return Reg::read() & Base::bitMask; }
	/// Check if the bit is cleared.
	static bool INLINE isCleared() { return !isSet(); }
};

/**
 * Represents a io bit that is set by hardware and cleared by software by writing a 0.
 *
 * @tparam Reg        IOMMptr pointing to a 8-bit io register
 * @tparam idx        number of the bit with the register (0<=idx<=7)
 * @tparam regAndMask and-mask used to mask out read only bits when writing to
 *                    the register
 */
template<class Reg, uint8_t idx, uint8_t regAndMask>
struct StatusBitClearBy0 : public ReadOnlyBit<Reg, idx, regAndMask>
{
	/// Alias for the base type.
	using Base = ReadOnlyBit<Reg, idx, regAndMask>;

	static constexpr uint8_t bitAndMask = 0xff;

	/// Clear the bit by writing a 0.
	static void INLINE clear()
	{
		Reg::write( Reg::read() & regAndMask & ~Base::bitMask);
	}
};

/**
 * Represents a io bit that is set by hardware and cleared by software by writing a 1.
 *
 * @tparam Reg        IOMMptr pointing to a 8-bit io register
 * @tparam idx        number of the bit with the register (0<=idx<=7)
 * @tparam regAndMask and-mask used to mask out read only bits when writing to
 *                    the register
 */
template<class Reg, uint8_t idx, uint8_t regAndMask>
struct StatusBitClearBy1 : public ReadOnlyBit<Reg, idx, regAndMask>
{
	/// Alias for the base type.
	using Base = ReadOnlyBit<Reg, idx, regAndMask>;

	/// Clear the bit by writing a 1.
	static void INLINE clear()
	{
		Reg::write( (Reg::read() & regAndMask) | Base::bitMask);
	}
};

/**
 * Represents a io bit that is readable and writable.
 *
 * @tparam Reg        IOMMptr pointing to a 8-bit io register
 * @tparam idx        number of the bit with the register (0<=idx<=7)
 * @tparam regAndMask and-mask used to mask out read only bits when writing to
 *                    the register
 */
template<class Reg, uint8_t idx, uint8_t regAndMask>
struct ReadWriteBit : public StatusBitClearBy0<Reg, idx, regAndMask>
{
	/// Alias for the base type.
	using Base = ReadOnlyBit<Reg, idx, regAndMask>;

	/// Set the bit.
	static void INLINE set()
	{
		Reg::write( (Reg::read() & regAndMask) | Base::bitMask);
	}
};


} // namespace lunacy
