/* { dg-do compile } */
/* { dg-options "-O2 -mfdpic -fPIC" } */

__thread int tls_value;

int *
tls_address (void)
{
  return &tls_value;
}

/* The dynamic loader may only initialize the descriptor in writable GOT
   storage; no legacy TLS dynamic relocation may target a literal pool.  */
/* { dg-final { scan-assembler "tls_value@GOTTLSDESC" } } */
/* { dg-final { scan-assembler-not "@TLSFUNC" } } */
/* { dg-final { scan-assembler-not "@TLSARG" } } */
