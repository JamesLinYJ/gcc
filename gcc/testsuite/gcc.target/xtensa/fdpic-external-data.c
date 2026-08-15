/* { dg-do compile } */
/* { dg-options "-O2 -mfdpic -fPIE" } */

extern int external_object;

int
read_external (void)
{
  return external_object;
}

/* { dg-final { scan-assembler "external_object@GOT" } } */
