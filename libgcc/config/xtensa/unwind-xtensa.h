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

/* Return the GOT value for the FDPIC module the unwind code belongs
   to.  The ABI keeps the current module's GOT in A11 for the whole
   function (A11 is callee-saved under FDPIC), so no lookup through
   the function descriptor is needed.  */

static inline _Unwind_Ptr _Unwind_gnu_Find_got (_Unwind_Ptr ptr)
{
    _Unwind_Ptr res;

    (void)ptr;
    asm volatile ("mov %[result], a11"
		  : [result] "=r" (res));
    return res;
}

#endif /* __FDPIC__ */

#endif /* _UNWIND_XTENSA_H */
