#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <sys/time.h>
#include <assert.h>

int main()
{
  const int maxpos = 50;
  const int maxexp = 230;
  const int ndigits = 16;

  srandom (time (0));

  for (int line = 0; line < 100000; line++)
    {
      /* s = <ndigits random digits> * 10^pos */
      int pos = random () % (2*maxpos) - maxpos;

      char s[1024];
      char *p = s;

      if (pos < 0)
	{
	  *p++ = '0';
	  *p++ = '.';
	  for (int k = 0; k > pos + 1; k--)
	    *p++ = '0';
	}

      bool started = false;
      for (int k = 0; k < ndigits; k++)
	{
	  if (k == pos)
	    *p++ = '.';

	  int d = random () % 10;

	  if (! (!started && d == 0))
	    {
	      *p++ = d + '0';
	      started = true;
	    }
	}

      while (p - s < pos)
	*p++ = '0';

      *p++ = 'e';
      int exp = random () % (maxexp * 2) - maxexp;
      sprintf (p, "%d", exp);

      double f;
      sscanf (s, "%lf", &f);

      assert (f * pow (10, -exp - pos) < 10);

      if (! isinf (f))
	printf ("%a %s\n", f, s);
    }
}


