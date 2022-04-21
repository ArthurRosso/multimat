/* dclock.c */
/****************************************************************
 * Clock frequency in MHz.                                      *
 * Update it with the right one ! (cf. /proc/cpu-info)          *
 ****************************************************************/
#define CLOCK_FREQ 2900

typedef struct {
	unsigned long int l;                    /* bits 0-31 */
	unsigned long int h;                    /* bits 31-63 */
} ulonglong_t;

void rdtsc(ulonglong_t *p)
{
	asm __volatile__ (".byte 0x0F,0x31" : "=a"(p->l), "=d"(p->h)); 
}


double DCLOCK()
{
  double bignum = 4294967296.0;
  double temp, time;
  static int first = -1;
  static double rfrequency;
  ulonglong_t tsc;
  void rdtsc();

  if( first )
    {
      first = 0;
      rfrequency = 1.0/CLOCK_FREQ ;
    }
  rdtsc( &tsc );
  temp = (double)tsc.h * bignum;
  temp += (double)tsc.l;
  time = temp * rfrequency;
  return( time );
}
