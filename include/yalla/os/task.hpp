/**
 * @brief  Defines a Task
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

#include <avr/io.hpp>
#include <os/context.hpp>

namespace yalla
{

/// Enumeration of all the states a Task can be in
class enum TaskState
{
	Active,  /// Task is executing
	Ready,   /// Task is reaady to be executing and not waiting to get any locks
	Blocked  /// Task is blocked on a lock
};

/**
 * Defines a simple Task object, capable of storing and restoring it's own state.
 *
 * @tparam stackBase initial stack pointer used for this Task
 * @tparam workload function pointer that is executed as the tasks main function
 */
template<addr_t stackBase, void (workload)()>
class Task
{
private:
	/// The current state
	TaskState state;
	/// Stack Pointer, saved when task is not Active
	uint16_t sp = stackBase - sizeof(Context);
public:
	/**
	 * Constructor
	 *
	 * Prepares the stack, so that the task can be startet for the first time.
	 */
	Task()
	{
		memset((void*) (sp), 0, sizeof(Context)); // TODO try to avoid the memset

		constexpr Context* context = reinterpret_cast<Context*>(stackBase);

		context->pc = reinterpret_cast<addr_t>(workload);
	}

	/**
	 * Get a pointer to the tasks context structure.
	 *
	 * Useful to examine or manipulate register contents.
	 *
	 * @return pointer to the tasks context structure
	 */
	INLINE Context* getContextPtr()
	{
		// sp points to last byte on stack which is the last byte of the stored context.

		if( TaskState == TaskState::Active)
			return nullptr;
		else
			return reinterpret_cast<Context*>(sp - sizeof(Context));
	}

	/**
	 * Stores the tasks context on the stack.
	 *
	 * May only be called with interrupts disabled. The tasks current PC has to
	 * be on top of the current stack.
	 */
	INLINE void storeContext() // TODO move asm to external asm file
	{
		asm volatile ( \
			"push r0\n\t" \
			"in r0, __SREG__\n\t" \
			"push r0\n\t" \
			"push r1\n\t" \
			"clr r1\n\t" \
			"push r2\n\t" \
			"push r3\n\t" \
			"push r4\n\t" \
			"push r5\n\t" \
			"push r6\n\t" \
			"push r7\n\t" \
			"push r8\n\t" \
			"push r9\n\t" \
			"push r10\n\t" \
			"push r11\n\t" \
			"push r12\n\t" \
			"push r13\n\t" \
			"push r14\n\t" \
			"push r15\n\t" \
			"push r16\n\t" \
			"push r17\n\t" \
			"push r18\n\t" \
			"push r19\n\t" \
			"push r20\n\t" \
			"push r21\n\t" \
			"push r22\n\t" \
			"push r23\n\t" \
			"push r24\n\t" \
			"push r25\n\t" \
			"push r26\n\t" \
			"push r27\n\t" \
			"push r28\n\t" \
			"push r29\n\t" \
			"push r30\n\t" \
			"push r31\n\t" \
		);

		sp = SP::read();
	}

	/**
	 * Loads the tasks context from the stack.
	 *
	 * May only be called with interrupts disabled. The tasks current PC is on
	 * top of the stack when the operation finishes.
	 */
	INLINE void loadContext() // TODO move asm to external asm file
	{
		SP::write(sp);

		asm volatile ( \
			"push r0\n\t" \
			"in r0, __SREG__\n\t" \
			"push r0\n\t" \
			"push r1\n\t" \
			"clr r1\n\t" \
			"push r2\n\t" \
			"push r3\n\t" \
			"push r4\n\t" \
			"push r5\n\t" \
			"push r6\n\t" \
			"push r7\n\t" \
			"push r8\n\t" \
			"push r9\n\t" \
			"push r10\n\t" \
			"push r11\n\t" \
			"push r12\n\t" \
			"push r13\n\t" \
			"push r14\n\t" \
			"push r15\n\t" \
			"push r16\n\t" \
			"push r17\n\t" \
			"push r18\n\t" \
			"push r19\n\t" \
			"push r20\n\t" \
			"push r21\n\t" \
			"push r22\n\t" \
			"push r23\n\t" \
			"push r24\n\t" \
			"push r25\n\t" \
			"push r26\n\t" \
			"push r27\n\t" \
			"push r28\n\t" \
			"push r29\n\t" \
			"push r30\n\t" \
			"push r31\n\t" \
		);
	}
};
};

} // namespace lunacy
