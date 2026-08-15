/* { dg-do compile } */
/* { dg-options "-O2 -mfdpic -fPIE" } */

extern int external_function (void);
extern int external_object;

int
call_then_read_external (void)
{
  return external_function () + external_object;
}

/* A descriptor call installs the callee GOT; later accesses require the
   caller's entry A11 value to be restored first.  */
/* { dg-final { scan-assembler "l32i(\\.n)?\\s+a11, sp," } } */
