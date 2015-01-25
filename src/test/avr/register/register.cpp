/**
 * @brief  Short test of io register implementation
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

#include <avr/bit.hpp>
#include <avr/register.hpp>
using namespace yalla;

using PORTD = Register<0x32,
                       ReadWriteBit,
                       ReadWriteBit,
                       ReadWriteBit,
                       ReadWriteBit,
                       ReadWriteBit,
                       ReadWriteBit,
                       ReadWriteBit,
                       ReadWriteBit>;

using PORTD7 = PORTD::Bit7;
using PORTD6 = PORTD::Bit6;
using PORTD5 = PORTD::Bit5;
using PORTD4 = PORTD::Bit4;
using PORTD3 = PORTD::Bit3;
using PORTD2 = PORTD::Bit2;
using PORTD1 = PORTD::Bit1;
using PORTD0 = PORTD::Bit0;

using PORTC = Register<0x35,
                       ReservedBit,
                       ReadWriteBit,
                       ReadWriteBit,
                       ReadWriteBit,
                       ReadWriteBit,
                       ReadWriteBit,
                       ReadWriteBit,
                       ReadWriteBit>;

using PORTC6 = PORTC::Bit6;
using PORTC5 = PORTC::Bit5;
using PORTC4 = PORTC::Bit4;
using PORTC3 = PORTC::Bit3;
using PORTC2 = PORTC::Bit2;
using PORTC1 = PORTC::Bit1;
using PORTC0 = PORTC::Bit0;

using TWCR = Register<0x56,
                      StatusBitClearBy1, // TWINT
                      ReadWriteBit,      // TWEA
                      ReadWriteBit,      // TWSTA
                      ReadWriteBit,      // TWSTO
                      ReadOnlyBit,       // TWWC
                      ReadWriteBit,      // TWEN
                      ReservedBit,       // -
                      ReadWriteBit>;     // TWIE

using TWINT  = TWCR::Bit7;
using TWEA   = TWCR::Bit6;
using TWSTA  = TWCR::Bit5;
using TWSTO  = TWCR::Bit4;
using TWWC   = TWCR::Bit3;
using TWEN   = TWCR::Bit2;
using TWIE   = TWCR::Bit0;

int main()
{
	PORTC::write(0x00);
	PORTD::write(0x00);
	TWCR::write(0x00);

	PORTC::write(0xff);
	PORTD::write(0xff);
	TWCR::write(0xff);

	PORTC::write(0x00);
	PORTD::write(0x00);
	TWCR::write(0x00);

	TWEN::set();
	TWEN::clear();

	PORTC::write(0x00);
	PORTD::write(0x00);
	TWCR::write(0x00);

	while(true);

	return 0;
}

