/* { dg-do compile } */
/* { dg-options "-O2 -mfdpic -fPIC" } */

int
replaceable_function (int value)
{
  return value + 1;
}

int
call_replaceable (int value)
{
  return replaceable_function (value);
}

/* A default-visible definition in a shared object remains interposable.
   Calling it directly would require an executable relocation and would
   bypass ELF symbol interposition.  */
/* { dg-final { scan-assembler "replaceable_function@GOTFUNCDESC" } } */
