#include "randcpuid.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dlfcn.h>
#include <errno.h>

static bool
writebytes (unsigned long long x, int nbytes)
{
  int ndigits = nbytes * 2;
  do
    {
      if (putchar ("0123456789abcdef"[x & 0xf]) < 0)
  return false;
      x >>= 4;
      ndigits--;
    }
  while (0 < ndigits);

  return 0 <= putchar ('\n');
}

/* Main program, which outputs N bytes of random data.  */
int
main (int argc, char **argv)
{
  /* Check arguments.  */
  bool valid = false;
  long long nbytes;
  if (argc == 2)
    {
      char *endptr;
      errno = 0;
      nbytes = strtoll (argv[1], &endptr, 10);
      if (errno)
  perror (argv[1]);
      else
  valid = !*endptr && 0 <= nbytes;
    }
  if (!valid)
    {
      fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
      return 1;
    }

  /* If there's no work to do, don't worry about which library to use.  */
  if (nbytes == 0)
    return 0;

  /* Now that we know we have work to do, arrange to use the
 *      appropriate library.  */
  unsigned long long (*rand64) (void);
  void* dlinking;
  char* err;
  if (rdrand_supported ())
    {
      dlinking = dlopen("randlibhw.so",RTLD_LAZY);
      if(!dlinking){
	printf("failed to open - %s\n", dlerror());
	return 1;
      }
      rand64 = dlsym(dlinking, "rand64");
      err = dlerror();
      if(err != NULL){
	printf("failed to obtain the address of the symbol - %s\n", err); return 1;
      }
    }
  else
    {
      dlinking = dlopen("randlibsw.so",RTLD_LAZY);
      if(!dlinking){
	printf("failed to open - %s\n", dlerror());
	return 1;
      }
      rand64 = dlsym(dlinking, "rand64");
      err = dlerror();
      
      if(err != NULL){
	printf("failed to obtain the address of the symbol - %s\n", err); return 1;
      }
    } 

  int wordsize = sizeof rand64 ();
  int output = 0;

  do
    {
      unsigned long long x = rand64 ();
      int outbytes = nbytes < wordsize ? nbytes : wordsize;
      if (!writebytes (x, outbytes))
	{
	  output = errno;
	  break;
	}
      nbytes -= outbytes;
    }
  while (0 < nbytes);

  if (fclose (stdout) != 0)
    output = errno;

  if (output)
    {
      errno = output;
      perror ("failed to output");
      return 1;
    }
  
  if (dlclose(dlinking))
  {
    fprintf (stderr, "failed to close - %s\n", dlerror());
    return 1;
  }

  return 0;
}

