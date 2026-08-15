/* { dg-do compile } */
/* { dg-options "-O2 -mfdpic -fPIC -fno-inline" } */

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

/* A non-preemptible function needs neither a descriptor lookup nor a
   dynamic relocation, so retain the direct call as the fast path.  */
/* { dg-final { scan-assembler "call0\\s+local_function" } } */
/* { dg-final { scan-assembler-not "local_function@GOTFUNCDESC" } } */
