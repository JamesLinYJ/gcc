/* { dg-do compile } */
/* { dg-options "-O2 -mfdpic -mlongcalls -fPIC -fno-inline" } */

static int
local_function (int value)
{
  return value + 1;
}

int
call_local (int value)
{
  return local_function (value);
}

/* An Xtensa long call normally uses an absolute executable literal.  FDPIC
   must instead use a writable descriptor slot so Flash remains XIP.  */
/* { dg-final { scan-assembler "local_function@GOTFUNCDESC" } } */
/* { dg-final { scan-assembler "callx0" } } */
/* { dg-final { scan-assembler-not "call0\\s+local_function" } } */
