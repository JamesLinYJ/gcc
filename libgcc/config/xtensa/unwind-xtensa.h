/* Header file for the Xtensa port of the FSF unwind library.
   Copyright (C) 2026 Free Software Foundation, Inc.

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3, or (at your
   option) any later version.

   GCC is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   Under Section 7 of GPL version 3, you are granted additional
   permissions described in the GCC Runtime Library Exception, version
   3.1, as published by the Free Software Foundation.

   You should have received a copy of the GNU General Public License
   and a copy of the GCC Runtime Library Exception along with this
   program; see the files COPYING3 and COPYING.RUNTIME respectively.
   If not, see <http://www.gnu.org/licenses/>.  */

#ifndef _UNWIND_XTENSA_H
#define _UNWIND_XTENSA_H

#include "unwind-generic.h"

#ifdef __FDPIC__

/* The loader can map text and data segments independently, so the GOT for
   an arbitrary unwind record cannot be inferred from the currently running
   module's A11.  Match the established ARM FDPIC contract: ask the loader
   by PC when it provides the hook, and use A11 only as the static or
   single-module fallback.  */

#ifdef __cplusplus
extern "C" {
#endif
extern _Unwind_Ptr __attribute__((weak))
__gnu_Unwind_Find_got (_Unwind_Ptr);
#ifdef __cplusplus
}
#endif

static inline _Unwind_Ptr _Unwind_gnu_Find_got (_Unwind_Ptr ptr)
{
    _Unwind_Ptr res;

    if (__gnu_Unwind_Find_got)
	res = __gnu_Unwind_Find_got (ptr);
    else
	asm volatile ("mov %[result], a11"
		      : [result] "=r" (res));
    return res;
}

#endif /* __FDPIC__ */

#endif /* _UNWIND_XTENSA_H */
