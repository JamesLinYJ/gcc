/* { dg-do compile } */
/* { dg-options "-O2 -mfdpic -fPIE" } */

extern int external_function (int);

int
call_external (int value)
{
  return external_function (value) + 1;
}

/* Runtime-resolved addresses must stay in writable GOT storage.  */
/* { dg-final { scan-assembler "external_function@GOTFUNCDESC" } } */
/* { dg-final { scan-assembler-not "external_function@funcdesc" } } */
