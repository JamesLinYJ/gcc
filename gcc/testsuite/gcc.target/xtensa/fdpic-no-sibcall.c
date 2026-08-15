/* { dg-do compile } */
/* { dg-options "-O2 -mfdpic -fPIE" } */

extern int external_function (int);

int
tail_external (int value)
{
  return external_function (value);
}

/* A generic Xtensa sibling jump cannot carry descriptor word one (the GOT).  */
/* { dg-final { scan-assembler "callx0" } } */
/* { dg-final { scan-assembler-not "jx" } } */
