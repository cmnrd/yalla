/**
 * @brief  Defines a OStream class in analogy to c++ std streams
 * @author Christian Menard
 * @date   2015-02-22
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

#include <stdlib.h>
 #include <avr/io.hpp>

namespace yalla
{

template<void (transmitByte)(char)>
class OStream
{
private:
	static constexpr uint8_t tmpStrSize = 10;
	char tempStr[tmpStrSize];

public:
	OStream& put(char c)
	{
		if(transmitByte != nullptr)
		{
			if( c == '\n')
				c = '\r';

			transmitByte(c);
		}
		return *this;
	}
	OStream& write( const char str[])
	{
		if(transmitByte != nullptr)
		{
			for(uint8_t i = 0; str[i] != '\0'; i++)
				put(str[i]);
		}
		return *this;
	}

	OStream& operator<<(char c) { return put(c); }
	OStream& operator<<(const char str[]) { return write(str); }
	OStream& operator<<( uint8_t i)
	{
		if(transmitByte != nullptr)
			return write( utoa(i, tempStr, tmpStrSize));
	}
	OStream& operator<<( int8_t i)
	{
		if(transmitByte != nullptr)
			return write( itoa(i, tempStr, tmpStrSize));
	}
	OStream& operator<<( uint16_t i)
	{
		if(transmitByte != nullptr)
			return write( utoa(i, tempStr, tmpStrSize));
	}
	OStream& operator<<( int16_t i)
	{
		if(transmitByte != nullptr)
			return write( itoa(i, tempStr, tmpStrSize));
	}
	OStream& operator<<( uint32_t i)
	{
		if(transmitByte != nullptr)
			return write( utoa(i, tempStr, tmpStrSize));
	}
	OStream& operator<<( int32_t i)
	{
		if(transmitByte != nullptr)
			return write( itoa(i, tempStr, tmpStrSize));
	}

	OStream& operator<<( float f)
	{
		if(transmitByte != nullptr)
			return write( dtostrf(f,1,6,tempStr));
	}
	OStream& operator<<( double d)
	{
		if(transmitByte != nullptr)
			return write( dtostrf(d,1,6,tempStr));
	}
};

} // namespace yalla
