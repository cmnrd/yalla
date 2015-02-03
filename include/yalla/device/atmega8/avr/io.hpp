/**
 * @brief  Atmega8 IO register and bit definitions
 * @author Hannes Ellinger
 * @author Christian Menard
 * @date   2015-01-25
 */

/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Hannes Ellinger
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

#include <avr/bit.hpp>
#include <avr/register.hpp>

namespace yalla
{

using SREG = Register<0x5f,
                      ReadWriteBit,  // I
                      ReadWriteBit,  // T
                      ReadWriteBit,  // H
                      ReadWriteBit,  // S
                      ReadWriteBit,  // V
                      ReadWriteBit,  // N
                      ReadWriteBit,  // Z
                      ReadWriteBit>; // C

using I = SREG::Bit7;
using T = SREG::Bit6;
using H = SREG::Bit5;
using S = SREG::Bit4;
using V = SREG::Bit3;
using N = SREG::Bit2;
using C = SREG::Bit1;
using Z = SREG::Bit0;

using SPH = Register<0x5e,
                     ReservedBit,   // -
                     ReservedBit,   // -
                     ReservedBit,   // -
                     ReservedBit,   // -
                     ReservedBit,   // -
                     ReadWriteBit,  // SP10
                     ReadWriteBit,  // SP9
                     ReadWriteBit>; // SP8

using SP10 = SREG::Bit2;
using SP9  = SREG::Bit1;
using SP8  = SREG::Bit0;

using SPL = Register<0x5d,
                     ReadWriteBit,  // SP7
                     ReadWriteBit,  // SP6
                     ReadWriteBit,  // SP5
                     ReadWriteBit,  // SP4
                     ReadWriteBit,  // SP3
                     ReadWriteBit,  // SP2
                     ReadWriteBit,  // SP1
                     ReadWriteBit>; // SP0

using SP7 = SREG::Bit7;
using SP6 = SREG::Bit6;
using SP5 = SREG::Bit5;
using SP4 = SREG::Bit4;
using SP3 = SREG::Bit3;
using SP2 = SREG::Bit2;
using SP1 = SREG::Bit1;
using SP0 = SREG::Bit0;

using SP = DataRegister16<0x5d>;

using GICR = Register<0x5b,
                     ReadWriteBit,  // INT1
                     ReadWriteBit,  // INT0
                     ReservedBit,   // -
                     ReservedBit,   // -
                     ReservedBit,   // -
                     ReservedBit,   // -
                     ReadWriteBit,  // IVSEL
                     ReadWriteBit>; // IVCE

using INT1  = GICR::Bit7;
using INT0  = GICR::Bit6;
using IVSEL = GICR::Bit1;
using IVCE  = GICR::Bit0;

using GIFR = Register<0x5A,
                     StatusBitClearBy1,  // INTF1
                     StatusBitClearBy1,  // INTF0
                     ReservedBit,   // -
                     ReservedBit,   // -
                     ReservedBit,   // -
                     ReservedBit,   // -
                     ReservedBit,   // -
                     ReservedBit>;  // -

using INTF1 = GIFR::Bit7;
using INTF0 = GIFR::Bit6;

using TIMSK = Register<0x59,
                     ReadWriteBit,  // OCIE2
                     ReadWriteBit,  // TOIE2
                     ReadWriteBit,  // TICIE1
                     ReadWriteBit,  // OCIE1A
                     ReadWriteBit,  // OCIE1B
                     ReadWriteBit,  // TOIE1
                     ReservedBit,   // -
                     ReadWriteBit>; // TOIE0

using OCIE2 = TIMSK::Bit7;
using TOIE2 = TIMSK::Bit6;
using TICIE1 = TIMSK::Bit5;
using OCIE1A = TIMSK::Bit4;
using OCIE1B = TIMSK::Bit3;
using TOIE1 = TIMSK::Bit2;
using TOIE0 = TIMSK::Bit0;

using TIFR = Register<0x58,
                     ReadWriteBit,  // OCF2
                     ReadWriteBit,  // TOV2
                     ReadWriteBit,  // ICF1
                     ReadWriteBit,  // OCF1A
                     ReadWriteBit,  // OCF1B
                     ReadWriteBit,  // TOV1
                     ReservedBit,   // -
                     ReadWriteBit>; // TOV0

using OCF2 = TIFR::Bit7;
using TOV2 = TIFR::Bit6;
using ICF1 = TIFR::Bit5;
using OCF1A = TIFR::Bit4;
using OCF1B = TIFR::Bit3;
using TOV1 = TIFR::Bit2;
using TOV0 = TIFR::Bit0;

using SPMCR = Register<0x57,
                     ReadWriteBit,  // SPMIE
                     ReadWriteBit,  // RWWSB
                     ReservedBit,   // -
                     ReadWriteBit,  // RWWSRE
                     ReadWriteBit,  // BLBSET
                     ReadWriteBit,  // PGWRT
                     ReadWriteBit,  // PGERS
                     ReadWriteBit>; // SPMEN

using SPMIE = SPMCR::Bit7;
using RWWSB = SPMCR::Bit6;
using RWWSRE = SPMCR::Bit4;
using BLBSET = SPMCR::Bit3;
using PGWRT = SPMCR::Bit2;
using PGERS = SPMCR::Bit1;
using SPMEN = SPMCR::Bit0;

using TWCR = Register<0x56,
                      StatusBitClearBy1, // TWINT
                      ReadWriteBit,      // TWEA
                      ReadWriteBit,      // TWSTA
                      ReadWriteBit,      // TWSTO
                      ReadOnlyBit,       // TWWC
                      ReadWriteBit,      // TWEN
                      ReservedBit,       // -
                      ReadWriteBit>;     // TWIE

using TWINT = TWCR::Bit7;
using TWEA  = TWCR::Bit6;
using TWSTA = TWCR::Bit5;
using TWSTO = TWCR::Bit4;
using TWWC  = TWCR::Bit3;
using TWEN  = TWCR::Bit2;
using TWIE  = TWCR::Bit0;

using MCUCR = Register<0x55,
                       ReadWriteBit, // SE
                       ReadWriteBit, // SM2
                       ReadWriteBit, // SM1
                       ReadWriteBit, // SM0
                       ReadWriteBit, // ISC11
                       ReadWriteBit, // ISC10
                       ReadWriteBit, // ISC01
                       ReadWriteBit>; // ISC00

using SE = MCUCR::Bit7;
using SM2 = MCUCR::Bit6;
using SM1 = MCUCR::Bit5;
using SM0 = MCUCR::Bit4;
using ISC11 = MCUCR::Bit3;
using ISC10 = MCUCR::Bit2;
using ISC01 = MCUCR::Bit1;
using ISC00 = MCUCR::Bit0;

using MCUCSR = Register<0x54,
                        ReservedBit,  // -
                        ReservedBit,  // -
                        ReservedBit,  // -
                        ReservedBit,  // -
                        ReadWriteBit, // WDRF
                        StatusBitClearBy0, // BORF
                        StatusBitClearBy0, // EXTRF
                        StatusBitClearBy0>; // PORF

// RESERVED = MCUCSR::Bit7;
// RESERVED = MCUCSR::Bit6;
// RESERVED = MCUCSR::Bit5;
// RESERVED = MCUCSR::Bit4;
using WDRF = MCUCSR::Bit3;
using BORF = MCUCSR::Bit2;
using EXTRF = MCUCSR::Bit1;
using PORF = MCUCSR::Bit0;

using TCCR0 = Register<0x53,
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReadWriteBit, // CS02
                     ReadWriteBit, // CS01
                     ReadWriteBit>; // CS00

// RESERVED = TCCR0::Bit7;
// RESERVED = TCCR0::Bit6;
// RESERVED = TCCR0::Bit5;
// RESERVED = TCCR0::Bit4;
// RESERVED = TCCR0::Bit3;
using CS02 = TCCR0::Bit2;
using CS01 = TCCR0::Bit1;
using CS00 = TCCR0::Bit0;

using TCNT = DataRegister<0x52>;

using OSCCAL = DataRegister<0x51>;

using SFIOR = Register<0x50,
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReservedBit,  // -
                     StatusBitClearBy1, // ACME
                     StatusBitClearBy1, // PUD
                     ReadWriteBit, // PSR2
                     ReadWriteBit>; // PSR10

// RESERVED = SFIOR::Bit7;
// RESERVED = SFIOR::Bit6;
// RESERVED = SFIOR::Bit5;
// RESERVED = SFIOR::Bit4;
using ACME = SFIOR::Bit3;
using PUD = SFIOR::Bit2;
using PSR2 = SFIOR::Bit1;
using PSR10 = SFIOR::Bit0;

using TCCR1A = Register<0x4F,
                     ReadWriteBit, // COM1A1
                     ReadWriteBit, // COM1A0
                     ReadWriteBit, // COM1B1
                     ReadWriteBit, // COM1B0
                     ReadWriteBit, // FOC1A
                     ReadWriteBit, // FOC1B
                     ReadWriteBit, // WGM11
                     ReadWriteBit>; // WGM10

using COM1A1 = TCCR1A::Bit7;
using COM1A0 = TCCR1A::Bit6;
using COM1B1 = TCCR1A::Bit5;
using COM1B0 = TCCR1A::Bit4;
using FOC1A = TCCR1A::Bit3;
using FOC1B = TCCR1A::Bit2;
using WGM11 = TCCR1A::Bit1;
using WGM10 = TCCR1A::Bit0;

using TCCR1B = Register<0x4E,
                     ReadWriteBit, // ICNC
                     ReadWriteBit, // ICES1
                     ReservedBit,  // -
                     ReadWriteBit, // WGM13
                     ReadWriteBit, // WGM12
                     ReadWriteBit, // CS12
                     ReadWriteBit, // CS11
                     ReadWriteBit>; // CS10

using ICNC = TCCR1B::Bit7;
using ICES1 = TCCR1B::Bit6;
// RESERVED = TCCR1B::Bit5;
using WGM13 = TCCR1B::Bit4;
using WGM12 = TCCR1B::Bit3;
using CS12 = TCCR1B::Bit2;
using CS11 = TCCR1B::Bit1;
using CS10 = TCCR1B::Bit0;

using TCNT1H = DataRegister<0x4D>;
using TCNT1L = DataRegister<0x4C>;
using TCNT1  = DataRegister16<0x4C>;

using OCR1AH = DataRegister<0x4B>;
using OCR1AL = DataRegister<0x4A>;
using OCR1A  = DataRegister16<0x4A>;

using OCR1BH = DataRegister<0x49>;
using OCR1BL = DataRegister<0x48>;
using OCR1B = DataRegister16<0x48>;

using ICR1H = DataRegister<0x47>;
using ICR1L = DataRegister<0x46>;
using ICR1  = DataRegister16<0x46>;

using TCCR2 = Register<0x45,
                     ReadWriteBit, // FOC2
                     ReadWriteBit, // WGM20
                     ReadWriteBit, // COM21
                     ReadWriteBit, // COM20
                     ReadWriteBit, // WGM21
                     ReadWriteBit, // CS22
                     ReadWriteBit, // CS21
                     ReadWriteBit>; // CS20

using FOC2 = TCCR2::Bit7;
using WGM20 = TCCR2::Bit6;
using COM21 = TCCR2::Bit5;
using COM20 = TCCR2::Bit4;
using WGM21 = TCCR2::Bit3;
using CS22 = TCCR2::Bit2;
using CS21 = TCCR2::Bit1;
using CS20 = TCCR2::Bit0;

using TCNT2 = DataRegister<0x44>;

using OCR2 = DataRegister<0x43>;

using ASSR = Register<0x42,
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReadWriteBit, // AS2
                     ReadOnlyBit, // TCN2UB
                     ReadOnlyBit, // OCR2UB
                     ReadOnlyBit>; // TCR2UB

// RESERVED = ASSR::Bit7;
// RESERVED = ASSR::Bit6;
// RESERVED = ASSR::Bit5;
// RESERVED = ASSR::Bit4;
using AS2 = ASSR::Bit3;
using TCN2UB = ASSR::Bit2;
using OCR2UB = ASSR::Bit1;
using TCR2UB = ASSR::Bit0;

using WDTCR = Register<0x41,
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReadWriteBit, // WDCE
                     ReadWriteBit, // WDE
                     ReadWriteBit, // WDP2
                     ReadWriteBit, // WDP1
                     ReadWriteBit>; // WDP0

// RESERVED = WDTCR::Bit7;
// RESERVED = WDTCR::Bit6;
// RESERVED = WDTCR::Bit5;
using WDCE = WDTCR::Bit4;
using WDE = WDTCR::Bit3;
using WDP2 = WDTCR::Bit2;
using WDP1 = WDTCR::Bit1;
using WDP0 = WDTCR::Bit0;

using UBRRH = Register<0x40,
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReadWriteBit, //
                     ReadWriteBit, //
                     ReadWriteBit, //
                     ReadWriteBit>; //

class UCSRC : public Register<0x40,
                              ReadWriteBit, // URSEL
                              ReadWriteBit, // UMSEL
                              ReadWriteBit, // UPM1
                              ReadWriteBit, // UPM0
                              ReadWriteBit, // USBS
                              ReadWriteBit, // UCSZ1
                              ReadWriteBit, // UCSZ0
                              ReadWriteBit> // UCPOL
{
private:
	using Base = Register<0x40,
                          ReadWriteBit, // URSEL
                          ReadWriteBit, // UMSEL
                          ReadWriteBit, // UPM1
                          ReadWriteBit, // UPM0
                          ReadWriteBit, // USBS
                          ReadWriteBit, // UCSZ1
                          ReadWriteBit, // UCSZ0
                          ReadWriteBit>;// UCPOL

	using URSEL = Bit7;
public:
	static INLINE void write(uint8_t v)
	{
		// URSEL bit must be set to write UCSRC
		Base::write( URSEL::bitMask | v);
	}

	static INLINE uint8_t read()
	{
		// read two times from addr 0x40 to read UCSRC
		Base::read();
		return Base::read();
	}
};

using URSEL = UCSRC::Bit7;
using UMSEL = UCSRC::Bit6;
using UPM1 = UCSRC::Bit5;
using UPM0 = UCSRC::Bit4;
using USBS = UCSRC::Bit3;
using UCSZ1 = UCSRC::Bit2;
using UCSZ0 = UCSRC::Bit1;
using UCPOL = UCSRC::Bit0;

using EEARH = Register<0x3F,
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReadWriteBit>; // EEAR8

// RESERVED = EEARH::Bit7;
// RESERVED = EEARH::Bit6;
// RESERVED = EEARH::Bit5;
// RESERVED = EEARH::Bit4;
// RESERVED = EEARH::Bit3;
// RESERVED = EEARH::Bit2;
// RESERVED = EEARH::Bit1;
using EEAR8 = EEARH::Bit0;

using EEARL = Register<0x3E,
                     ReadWriteBit, // EEAR7
                     ReadWriteBit, // EEAR6
                     ReadWriteBit, // EEAR5
                     ReadWriteBit, // EEAR4
                     ReadWriteBit, // EEAR3
                     ReadWriteBit, // EEAR2
                     ReadWriteBit, // EEAR1
                     ReadWriteBit>; // EEAR0

using EEAR7 = EEARL::Bit7;
using EEAR6 = EEARL::Bit6;
using EEAR5 = EEARL::Bit5;
using EEAR4 = EEARL::Bit4;
using EEAR3 = EEARL::Bit3;
using EEAR2 = EEARL::Bit2;
using EEAR1 = EEARL::Bit1;
using EEAR0 = EEARL::Bit0;

using EEDR = DataRegister<0x3D>;

using EECR = Register<0x3C,
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReadWriteBit, // EERIE
                     ReadWriteBit, // EEMWE
                     ReadWriteBit, // EEWE
                     ReadWriteBit>; // EERE

// RESERVED = EECR::Bit7;
// RESERVED = EECR::Bit6;
// RESERVED = EECR::Bit5;
// RESERVED = EECR::Bit4;
using EERIE = EECR::Bit3;
using EEMWE = EECR::Bit2;
using EEWE = EECR::Bit1;
using EERE = EECR::Bit0;

using PORTB = Register<0x38,
                       ReadWriteBit,  // PORTB7
                       ReadWriteBit,  // PORTB6
                       ReadWriteBit,  // PORTB5
                       ReadWriteBit,  // PORTB4
                       ReadWriteBit,  // PORTB3
                       ReadWriteBit,  // PORTB2
                       ReadWriteBit,  // PORTB1
                       ReadWriteBit>; // PORTB0

using PORTB7 = PORTB::Bit7;
using PORTB6 = PORTB::Bit6;
using PORTB5 = PORTB::Bit5;
using PORTB4 = PORTB::Bit4;
using PORTB3 = PORTB::Bit3;
using PORTB2 = PORTB::Bit2;
using PORTB1 = PORTB::Bit1;
using PORTB0 = PORTB::Bit0;

using DDRB = Register<0x37,
                       ReadWriteBit,  // DDB7
                       ReadWriteBit,  // DDB6
                       ReadWriteBit,  // DDB5
                       ReadWriteBit,  // DDB4
                       ReadWriteBit,  // DDB3
                       ReadWriteBit,  // DDB2
                       ReadWriteBit,  // DDB1
                       ReadWriteBit>; // DDB0

using DDB7 = DDRB::Bit7;
using DDB6 = DDRB::Bit6;
using DDB5 = DDRB::Bit5;
using DDB4 = DDRB::Bit4;
using DDB3 = DDRB::Bit3;
using DDB2 = DDRB::Bit2;
using DDB1 = DDRB::Bit1;
using DDB0 = DDRB::Bit0;

using PINB = Register<0x36,
                       ReadWriteBit,  // PINB7
                       ReadWriteBit,  // PINB6
                       ReadWriteBit,  // PINB5
                       ReadWriteBit,  // PINB4
                       ReadWriteBit,  // PINB3
                       ReadWriteBit,  // PINB2
                       ReadWriteBit,  // PINB1
                       ReadWriteBit>; // PINB0

using PINB7 = PINB::Bit7;
using PINB6 = PINB::Bit6;
using PINB5 = PINB::Bit5;
using PINB4 = PINB::Bit4;
using PINB3 = PINB::Bit3;
using PINB2 = PINB::Bit2;
using PINB1 = PINB::Bit1;
using PINB0 = PINB::Bit0;

using PORTC = Register<0x35,
                     ReservedBit,  // -
                     ReadWriteBit, // PORTC6
                     ReadWriteBit, // PORTC5
                     ReadWriteBit, // PORTC4
                     ReadWriteBit, // PORTC3
                     ReadWriteBit, // PORTC2
                     ReadWriteBit, // PORTC1
                     ReadWriteBit>; // PORTC0

// RESERVED = PORTC::Bit7;
using PORTC6 = PORTC::Bit6;
using PORTC5 = PORTC::Bit5;
using PORTC4 = PORTC::Bit4;
using PORTC3 = PORTC::Bit3;
using PORTC2 = PORTC::Bit2;
using PORTC1 = PORTC::Bit1;
using PORTC0 = PORTC::Bit0;

using DDRC = Register<0x34,
                     ReservedBit,  // -
                     ReadWriteBit, // DDC6
                     ReadWriteBit, // DDC5
                     ReadWriteBit, // DDC4
                     ReadWriteBit, // DDC3
                     ReadWriteBit, // DDC2
                     ReadWriteBit, // DDC1
                     ReadWriteBit>; // DDC0

// RESERVED = DDC::Bit7;
using DDC6 = DDRC::Bit6;
using DDC5 = DDRC::Bit5;
using DDC4 = DDRC::Bit4;
using DDC3 = DDRC::Bit3;
using DDC2 = DDRC::Bit2;
using DDC1 = DDRC::Bit1;
using DDC0 = DDRC::Bit0;

using PINC = Register<0x33,
                     ReservedBit,  // -
                     ReadWriteBit, // PINC6
                     ReadWriteBit, // PINC5
                     ReadWriteBit, // PINC4
                     ReadWriteBit, // PINC3
                     ReadWriteBit, // PINC2
                     ReadWriteBit, // PINC1
                     ReadWriteBit>; // PINC0

// RESERVED = PINC::Bit7;
using PINC6 = PINC::Bit6;
using PINC5 = PINC::Bit5;
using PINC4 = PINC::Bit4;
using PINC3 = PINC::Bit3;
using PINC2 = PINC::Bit2;
using PINC1 = PINC::Bit1;
using PINC0 = PINC::Bit0;

using PORTD = Register<0x32,
                       ReadWriteBit,  // PORTD7
                       ReadWriteBit,  // PORTD6
                       ReadWriteBit,  // PORTD5
                       ReadWriteBit,  // PORTD4
                       ReadWriteBit,  // PORTD3
                       ReadWriteBit,  // PORTD2
                       ReadWriteBit,  // PORTD1
                       ReadWriteBit>; // PORTD0

using PORTD7 = PORTD::Bit7;
using PORTD6 = PORTD::Bit6;
using PORTD5 = PORTD::Bit5;
using PORTD4 = PORTD::Bit4;
using PORTD3 = PORTD::Bit3;
using PORTD2 = PORTD::Bit2;
using PORTD1 = PORTD::Bit1;
using PORTD0 = PORTD::Bit0;

using DDRD = Register<0x31,
                       ReadWriteBit,  // DDD7
                       ReadWriteBit,  // DDD6
                       ReadWriteBit,  // DDD5
                       ReadWriteBit,  // DDD4
                       ReadWriteBit,  // DDD3
                       ReadWriteBit,  // DDD2
                       ReadWriteBit,  // DDD1
                       ReadWriteBit>; // DDD0

using DDD7 = DDRD::Bit7;
using DDD6 = DDRD::Bit6;
using DDD5 = DDRD::Bit5;
using DDD4 = DDRD::Bit4;
using DDD3 = DDRD::Bit3;
using DDD2 = DDRD::Bit2;
using DDD1 = DDRD::Bit1;
using DDD0 = DDRD::Bit0;

using PIND = Register<0x30,
                       ReadWriteBit,  // PIND7
                       ReadWriteBit,  // PIND6
                       ReadWriteBit,  // PIND5
                       ReadWriteBit,  // PIND4
                       ReadWriteBit,  // PIND3
                       ReadWriteBit,  // PIND2
                       ReadWriteBit,  // PIND1
                       ReadWriteBit>; // PIND0

using PIND7 = PIND::Bit7;
using PIND6 = PIND::Bit6;
using PIND5 = PIND::Bit5;
using PIND4 = PIND::Bit4;
using PIND3 = PIND::Bit3;
using PIND2 = PIND::Bit2;
using PIND1 = PIND::Bit1;
using PIND0 = PIND::Bit0;

using SPDR = DataRegister<0x2F>;

using SPSR = Register<0x2E,
                     ReadOnlyBit, // SPIF
                     ReadOnlyBit, // WCOL
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReservedBit,  // -
                     ReadWriteBit>; // SPI2X

using SPIF = SPSR::Bit7;
using WCOL = SPSR::Bit6;
// RESERVED = SPSR::Bit5;
// RESERVED = SPSR::Bit4;
// RESERVED = SPSR::Bit3;
// RESERVED = SPSR::Bit2;
// RESERVED = SPSR::Bit1;
using SPI2X = SPSR::Bit0;

using SPCR = Register<0x2D,
                     ReadWriteBit, // SPIE
                     ReadWriteBit, // SPE
                     ReadWriteBit, // DORD
                     ReadWriteBit, // MSTR
                     ReadWriteBit, // CPOL
                     ReadWriteBit, // CPHA
                     ReadWriteBit, // SPR1
                     ReadWriteBit>; // SPR0

using SPIE = SPCR::Bit7;
using SPE = SPCR::Bit6;
using DORD = SPCR::Bit5;
using MSTR = SPCR::Bit4;
using CPOL = SPCR::Bit3;
using CPHA = SPCR::Bit2;
using SPR1 = SPCR::Bit1;
using SPR0 = SPCR::Bit0;

using UDR = DataRegister<0x2C>;

using UCSRA = Register<0x2B,
                     ReadOnlyBit, // RXC
                     ReadWriteBit, // TXC
                     ReadOnlyBit, // UDRE
                     ReadOnlyBit, // FE
                     ReadOnlyBit, // DOR
                     ReadOnlyBit, // PE
                     ReadWriteBit, // U2X
                     ReadWriteBit>; // MPCM

using RXC = UCSRA::Bit7;
using TXC = UCSRA::Bit6;
using UDRE = UCSRA::Bit5;
using FE = UCSRA::Bit4;
using DOR = UCSRA::Bit3;
using PE = UCSRA::Bit2;
using U2X = UCSRA::Bit1;
using MPCM = UCSRA::Bit0;

using UCSRB = Register<0x2a,
                     ReadWriteBit, // RXCIE
                     ReadWriteBit, // TXCIE
                     ReadWriteBit, // UDRIE
                     ReadWriteBit, // RXEN
                     ReadWriteBit, // TXEN
                     ReadWriteBit, // UCSZ2
                     ReadOnlyBit, // RXB8
                     ReadWriteBit>; // TXB8

using RXCIE = UCSRB::Bit7;
using TXCIE = UCSRB::Bit6;
using UDRIE = UCSRB::Bit5;
using RXEN = UCSRB::Bit4;
using TXEN = UCSRB::Bit3;
using UCSZ2 = UCSRB::Bit2;
using RXB8 = UCSRB::Bit1;
using TXB8 = UCSRB::Bit0;

using UBRRL = DataRegister<0x29>;

using ACSR = Register<0x28,
                     ReadWriteBit, // ACD
                     ReadWriteBit, // ACBG
                     ReadOnlyBit, // ACO
                     ReadWriteBit, // ACI
                     ReadWriteBit, // ACIE
                     ReadWriteBit, // ACIC
                     ReadWriteBit, // ACIS1
                     ReadWriteBit>; // ACIS0

using ACD = ACSR::Bit7;
using ACBG = ACSR::Bit6;
using ACO = ACSR::Bit5;
using ACI = ACSR::Bit4;
using ACIE = ACSR::Bit3;
using ACIC = ACSR::Bit2;
using ACIS1 = ACSR::Bit1;
using ACIS0 = ACSR::Bit0;

using ADMUX = Register<0x27,
                     ReadWriteBit, // REFS1
                     ReadWriteBit, // REFS0
                     ReadWriteBit, // ADLAR
                     ReservedBit,  // -
                     ReadWriteBit, // MUX3
                     ReadWriteBit, // MUX2
                     ReadWriteBit, // MUX1
                     ReadWriteBit>; // MUX0

using REFS1 = ADMUX::Bit7;
using REFS0 = ADMUX::Bit6;
using ADLAR = ADMUX::Bit5;
// RESERVED = ADMUX::Bit4;
using MUX3 = ADMUX::Bit3;
using MUX2 = ADMUX::Bit2;
using MUX1 = ADMUX::Bit1;
using MUX0 = ADMUX::Bit0;

using ADCSRA = Register<0x26,
                     ReadWriteBit, // ADEN
                     ReadWriteBit, // ADSC
                     ReadWriteBit, // ADFR
                     ReadWriteBit, // ADIF
                     ReadWriteBit, // ADIE
                     ReadWriteBit, // ADPS2
                     ReadWriteBit, // ADPS1
                     ReadWriteBit>; // ADPS0

using ADEN = ADCSRA::Bit7;
using ADSC = ADCSRA::Bit6;
using ADFR = ADCSRA::Bit5;
using ADIF = ADCSRA::Bit4;
using ADIE = ADCSRA::Bit3;
using ADPS2 = ADCSRA::Bit2;
using ADPS1 = ADCSRA::Bit1;
using ADPS0 = ADCSRA::Bit0;

using ADCH = DataRegister<0x25>;
using ADCL = DataRegister<0x24>;
using ADC  = DataRegister16<0x24>;

using TWDR = DataRegister<0x23>;

using TWAR = Register<0x22,
                     ReadWriteBit, // TWA6
                     ReadWriteBit, // TWA5
                     ReadWriteBit, // TWA4
                     ReadWriteBit, // TWA3
                     ReadWriteBit, // TWA2
                     ReadWriteBit, // TWA1
                     ReadWriteBit, // TWA0
                     ReadWriteBit>; // TWGCE

using TWA6 = TWAR::Bit7;
using TWA5 = TWAR::Bit6;
using TWA4 = TWAR::Bit5;
using TWA3 = TWAR::Bit4;
using TWA2 = TWAR::Bit3;
using TWA1 = TWAR::Bit2;
using TWA0 = TWAR::Bit1;
using TWGCE = TWAR::Bit0;

using TWSR = Register<0x21,
                     ReadWriteBit, // TWS7
                     ReadWriteBit, // TWS6
                     ReadWriteBit, // TWS5
                     ReadWriteBit, // TWS4
                     ReadWriteBit, // TWS3
                     ReservedBit,  // -
                     ReadWriteBit, // TWS1
                     ReadWriteBit>; // TWS0

using TWS7 = TWSR::Bit7;
using TWS6 = TWSR::Bit6;
using TWS5 = TWSR::Bit5;
using TWS4 = TWSR::Bit4;
using TWS3 = TWSR::Bit3;
// RESERVED = TWSR::Bit2;
using TWS1 = TWSR::Bit1;
using TWS0 = TWSR::Bit0;

using TWBR = DataRegister<0x20>;

}
