/* Xtensa Linux configuration.
   Derived from the configuration for GCC for Intel i386 running Linux.
   Copyright (C) 2001-2026 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#define TARGET_OS_CPP_BUILTINS() GNU_USER_TARGET_OS_CPP_BUILTINS()

/* An FDPIC system toolchain must build its own target runtime libraries with
   the same ABI as user code.  --enable-fdpic selects that system-wide
   default, while -mno-fdpic remains available for freestanding components
   such as the Linux kernel.  Make this a driver self-spec so cc1, assembler
   and linker all observe one canonical option.  */
#ifdef FDPIC_DEFAULT
# undef DRIVER_SELF_SPECS
# define DRIVER_SELF_SPECS "%{!mno-fdpic:-mfdpic}"
#endif

#undef SUBTARGET_CPP_SPEC
#define SUBTARGET_CPP_SPEC "%{posix:-D_POSIX_SOURCE} %{pthread:-D_REENTRANT}"

#undef SIZE_TYPE
#define SIZE_TYPE "unsigned int"

#undef PTRDIFF_TYPE
#define PTRDIFF_TYPE "int"

#undef WCHAR_TYPE
#define WCHAR_TYPE "long int"

#undef WCHAR_TYPE_SIZE
#define WCHAR_TYPE_SIZE 32

#undef ASM_SPEC
#define ASM_SPEC \
 "%{mtext-section-literals:--text-section-literals} \
  %{mno-text-section-literals:--no-text-section-literals} \
  %{mtarget-align:--target-align} \
  %{mno-target-align:--no-target-align} \
  %{mlongcalls:--longcalls} \
  %{mno-longcalls:--no-longcalls} \
  %{mauto-litpools:--auto-litpools} \
  %{mno-auto-litpools:--no-auto-litpools} \
  %{mfdpic:--fdpic} \
  %{mabi=windowed:--abi-windowed} \
  %{mabi=call0:--abi-call0}"

#define GLIBC_DYNAMIC_LINKER "/lib/ld.so.1"

#undef LINK_SPEC
#define LINK_SPEC \
 "%{shared:-shared} \
  %{mfdpic:%{static-pie:%e-static-pie is not supported with -mfdpic} \
    -z separate-code \
    %{!shared:%{!r:%{!static:-pie}}} \
    %{!static:-z now -z relro}} \
  %{!shared: \
    %{!static:%{!static-pie: \
      %{rdynamic:-export-dynamic} \
      -dynamic-linker " GNU_USER_DYNAMIC_LINKER "}} \
    %{static-pie:-static -pie --no-dynamic-linker -z text} \
    %{static:-static}} \
  %{mabi=windowed:--abi-windowed} \
  %{mabi=call0:--abi-call0}"

/* uClibc's FDPIC executable entry point calls __self_reloc before normal
   process startup.  Its freestanding implementation is installed as
   crtreloc.o and must be part of every FDPIC executable, but not a shared
   object or a conventional Xtensa link.  */
#undef STARTFILE_SPEC
#define STARTFILE_SPEC \
 "%{mfdpic:%{!shared:crtreloc.o%s}} " GNU_USER_TARGET_STARTFILE_SPEC

#undef LOCAL_LABEL_PREFIX
#define LOCAL_LABEL_PREFIX	"."

/* Always enable "-fpic" for Xtensa Linux.  */
#define XTENSA_ALWAYS_PIC 1

#undef DEBUGGER_REGNO

#define TARGET_ASM_FILE_END file_end_indicate_exec_stack
