 /**
 * @brief  Macro for easy USR definition
 * @author Christian Menard
 * @date   2015-03-01
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

/*
 * We define a function __vector_n and a function __vector_n_isr for each
 * interrupt. __vector_n_isr is the actual interrupt handler. It is declared
 * using the __signal__ attribute and calls the interrupt handler specified in
 * Config. It automagically ensures that no registers are clobbered when
 * returning from the interrupt handler.
 *
 * The address of __vector_n is automatically added to the vector table. However,
 * it does not perform any interrupt handling itself. __vector_n is declared
 * using the __used__ and __naked__ attributes. __used__ ensures that the
 * function is not optimized away as it is never called. __naked__ ensures that
 * the compiler does not insert any instructions. This is needed to optimize
 * the ISR in the case that the handler is not specified in Config (nullptr).
 * In this case only a reti instruction should be executed.
 *
 * When a handler is specified in Config __vector_n calls __vector_n_isr which
 * ensures that all clobbered registers are saved and restored. __vector_n_isr
 * in turn calls the handler specified in Config. Dependend on optimization
 * settings the compiler may insert a call or a jmp to __vector_n_isr. If the
 * compiler inserts a call, an additional ret instruction is needed. This
 * instruction is added preventively to ensure correct operation in both cases.
 * However, if the copiler decides to use a jmp it may remove the ret
 * instruction due to optimization.
 *
 * The check if a handler is specified or is a nullptr cannot be evaluated
 * during compilation, as the handler address is unknown. To avoid evaluating
 * this expression at runtime, link-time optimization needs to be enabled. This
 * is done by declaring __vector_n with the attribute optimize("-flto").
 * To avoid the warning "the address of 'Config::xxxIsr' will never be NULL"
 * '-Waddress' is disabled temporarly.
 */

#define YALLA_ISR(vector, vector_isr, handler)              \
extern "C"                                                  \
{                                                           \
void vector_isr() __attribute__((__signal__));              \
void vector_isr()                                           \
{                                                           \
    handler();                                              \
}                                                           \
void vector() __attribute__((__used__,                      \
                                    __externally_visible__, \
                                     __naked__,             \
                                    optimize("-flto")));    \
void vector()                                               \
{                                                           \
    if (handler != nullptr)                                 \
    {                                                       \
        vector_isr();                                       \
        asm ("ret");                                        \
    }                                                       \
    else                                                    \
        asm volatile ("reti");                              \
}                                                           \
}                                                           \
struct force_semicolon
