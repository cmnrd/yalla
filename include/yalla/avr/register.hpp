 
/**
 * @brief  Class representing a io register
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

#include <avr/iomm.hpp>
#include <inline.hpp>

namespace yalla
{

/**
 * Simple wrapper for a IOMMPtr. Represents a 8-bit io data register.
 *
 * In contrast to a Register a DataRegister is represented only by a 8-bit value
 * and is not a set of individual bits.
 *
 * @tparam addr Address of the register.
 */
template<addr_t addr>
struct DataRegister : public IOMMPtr<uint8_t, addr>
{};

/**
 * Simple wrapper for a IOMMPtr. Represents a 16-bit io data register.
 *
 * In contrast to a Register a DataRegister is represented only by a 16-bit value
 * and is not a set of individual bits.
 *
 * @tparam addr Address of the register.
 */
template<addr_t addr>
struct DataRegister16 : public IOMMPtr<uint16_t, addr>
{};

/**
 * Represents a 8-bit io register that is assembled from 8 individual bits.
 *
 * @tparam addr  Address of the register.
 * @tparam _Bit7 Type of the registers 8th bit.
 * @tparam _Bit6 Type of the registers 7th bit.
 * @tparam _Bit5 Type of the registers 6th bit.
 * @tparam _Bit4 Type of the registers 5th bit.
 * @tparam _Bit3 Type of the registers 4th bit.
 * @tparam _Bit2 Type of the registers 3rd bit.
 * @tparam _Bit1 Type of the registers 2nd bit.
 * @tparam _Bit0 Type of the registers 1st bit.
 */
template<addr_t addr,
         template<class, uint8_t, uint8_t> class _Bit7,
         template<class, uint8_t, uint8_t> class _Bit6,
         template<class, uint8_t, uint8_t> class _Bit5,
         template<class, uint8_t, uint8_t> class _Bit4,
         template<class, uint8_t, uint8_t> class _Bit3,
         template<class, uint8_t, uint8_t> class _Bit2,
         template<class, uint8_t, uint8_t> class _Bit1,
         template<class, uint8_t, uint8_t> class _Bit0>
class Register
{
private:
	/// Alias for the IOMMPtr
	using Ptr = IOMMPtr<uint8_t, addr>;

public:
	/// And-mask used on write operations to mask out reserved bits.
	static constexpr uint8_t regAndMask = _Bit7<Ptr, 7, 0>::bitAndMask &
	                                      _Bit6<Ptr, 6, 0>::bitAndMask &
	                                      _Bit5<Ptr, 5, 0>::bitAndMask &
	                                      _Bit4<Ptr, 4, 0>::bitAndMask &
	                                      _Bit3<Ptr, 3, 0>::bitAndMask &
	                                      _Bit2<Ptr, 2, 0>::bitAndMask &
	                                      _Bit1<Ptr, 1, 0>::bitAndMask &
	                                      _Bit0<Ptr, 0, 0>::bitAndMask;

	/// The registers 8th bit.
	using Bit7 = _Bit7<Ptr, 7, regAndMask>;
	/// The registers 7th bit.
	using Bit6 = _Bit6<Ptr, 6, regAndMask>;
	/// The registers 6th bit.
	using Bit5 = _Bit5<Ptr, 5, regAndMask>;
	/// The registers 5th bit.
	using Bit4 = _Bit4<Ptr, 4, regAndMask>;
	/// The registers 4th bit.
	using Bit3 = _Bit3<Ptr, 3, regAndMask>;
	/// The registers 3rd bit.
	using Bit2 = _Bit2<Ptr, 2, regAndMask>;
	/// The registers 2nd bit.
	using Bit1 = _Bit1<Ptr, 1, regAndMask>;
	/// The registers 1st bit.
	using Bit0 = _Bit0<Ptr, 0, regAndMask>;

	/**
	 * Write a 8-bit integer to the register.
	 *
	 * Before writing the value regAndMask is applied to mask out reserved bits,
	 * read-only bits and interrupt flags.
	 *
	 * @param v value to be written
	 */
	static void INLINE write(uint8_t v)
	{
		Ptr::write( v & regAndMask);
	}

	/**
	 * Write a 8-bit integer to the register.
	 *
	 * In contrast to write() this does not apply the regAndMask, thus the value
	 * is directly to the register. Use with care!
	 *
	 * @param v value to be written
	 */
	static void INLINE write_direct(uint8_t v)
	{
		Ptr::write(v);
	}

	/**
	 * Read a 8-bit integer from the register.
	 *
	 * @return value read from register
	 */
	static uint8_t INLINE read()
	{
		return Ptr::read();
	}
};

} // namespace lunacy
