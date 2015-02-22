/**
 * @brief  Implementation of a guard ensuring atomic operation within a block
 * @author Christian Menard
 * @date   2015-01-25
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
#include <avr/interrupts.hpp>
#include <avr/iomm.hpp>

namespace yalla
{

/**
 * Policy setting the behavior of AtomicGuard and NonAtomicGuard.
 */
enum class AtomicPolicy
{
	/// Restore state when AtomicGuard or NonAtomicGuard object is destroyed
	RestoreState,
	/// Force interrupts enabled when AtomicGuard object is destroyed (more efficient then RestoreState)
	ForceOn,
	/// Force interrupts disabled when NonAtomicGuard object is destroyed (more efficient then RestoreState)
	ForceOff,
};

/**
 * Guard ensuring atomic operation as long as the object exists.
 *
 * @tparam Policy AtomicPolicy::RestoreState or AtomicPolicy::ForceOn
 */
template<AtomicPolicy Policy>
struct AtomicGuard
{
	static_assert(Policy == AtomicPolicy::ForceOff,
	               "ForceOff is not a valid Policy for AtomicGuard!");
};

template<>
struct AtomicGuard<AtomicPolicy::ForceOn>
{
	/// Constructor, disables interrupts on object creation.
	INLINE AtomicGuard()  { Interrupts::disable(); }
	/// Destructor, enables interrupts on object destruction.
	INLINE ~AtomicGuard() { Interrupts::enable(); }
};

template<>
class AtomicGuard<AtomicPolicy::RestoreState>
{
private:
	/// safe the SREG state
	uint8_t sreg;
	/// Alias for the pointer pointing to SREG
	using SREG = IOMMPtr<uint8_t, 0x3f>;
public:
	/// Constructor, disables interrupts on object creation.
	INLINE AtomicGuard()
	{
		sreg = SREG::read();
		Interrupts::disable();
	}

	/// Destructor, restores old state on object destruction.
	INLINE ~AtomicGuard()
	{
		SREG::write(sreg);
	}
};

/**
 * Guard ensuring non-atomic operation as long as the object exists.
 *
 * This is useful when a big atomic block guarded by AtomicGuard contains smaller
 * blocks that can operate non-atomically.
 *
 * @tparam Policy AtomicPolicy::RestoreState or AtomicPolicy::ForceOff
 */
template<AtomicPolicy Policy>
struct NonAtomicGuard
{
	static_assert(Policy == AtomicPolicy::ForceOn,
	               "ForceOn is not a valid Policy for AtomicGuard!");
};

template<>
struct NonAtomicGuard<AtomicPolicy::ForceOff>
{
	/// Constructor, enables interrupts on object creation.
	INLINE NonAtomicGuard()  { Interrupts::enable(); }
	/// Constructor, disables interrupts on object creation.
	INLINE ~NonAtomicGuard() { Interrupts::disable(); }
};

template<>
class NonAtomicGuard<AtomicPolicy::RestoreState>
{
private:
	/// safe the SREG state
	uint8_t sreg;
	/// Alias for the pointer pointing to SREG
	using SREG = IOMMPtr<uint8_t, 0x3f>;
public:
	/// Constructor, enables interrupts on object creation.
	INLINE NonAtomicGuard()
	{
		sreg = SREG::read();
		Interrupts::enable();
	}

	/// Destructor, restores old state on object destruction.
	INLINE ~NonAtomicGuard()
	{
		SREG::write(sreg);
	}
};

} // namespace yalla
