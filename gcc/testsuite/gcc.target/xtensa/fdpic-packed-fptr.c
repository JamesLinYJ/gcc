/* { dg-do compile } */
/* { dg-options "-O2 -mfdpic -fPIE" } */

extern void external_function (void);

struct __attribute__((packed)) holder
{
  char tag;
  void (*function) (void);
};

const struct holder packed_pointer = { 1, external_function };

/* Unaligned initializers still hold descriptor pointers, never raw code.  */
/* { dg-final { scan-assembler "\\.section\\s+\\.data\\.rel\\.ro" } } */
/* { dg-final { scan-assembler "external_function@funcdesc" } } */
