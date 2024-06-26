
/*
 * FILE: resample.h
 *   BY: Julius Smith (at CCRMA, Stanford U)
 * C BY: translated from SAIL to C by Christopher Lee Fraley
 *          (cf0v@andrew.cmu.edu)
 * DATE: 7-JUN-88
 * VERS: 2.0  (17-JUN-88, 3:00pm)
 */

#define MAXNWING  5122
#define MAXFACTOR 4       /* Maximum Factor without output buff overflow */



/* Conversion constants */
#define Nhc       8
#define Na        7
#define Np       (Nhc+Na)
#define Npc      (1<<Nhc)
#define Amask    ((1<<Na)-1)
#define Pmask    ((1<<Np)-1)
#define Nh       16
#define Nb       16
#define Nhxn     14
#define Nhg      (Nh-Nhxn)
#define NLpScl   13

/* Description of constants:
 *
 * Npc - is the number of look-up values available for the lowpass filter
 *    between the beginning of its impulse response and the "cutoff time"
 *    of the filter.  The cutoff time is defined as the reciprocal of the
 *    lowpass-filter cut off frequence in Hz.  For example, if the
 *    lowpass filter were a sinc function, Npc would be the index of the
 *    impulse-response lookup-table corresponding to the first zero-
 *    crossing of the sinc function.  (The inverse first zero-crossing
 *    time of a sinc function equals its nominal cutoff frequency in Hz.)
 *    Npc must be a power of 2 due to the details of the current
 *    implementation. The default value of 512 is sufficiently high that
 *    using linear interpolation to fill in between the table entries
 *    gives approximately 16-bit accuracy in filter coefficients.
 *
 * Nhc - is log base 2 of Npc.
 *
 * Na - is the number of bits devoted to linear interpolation of the
 *    filter coefficients.
 *
 * Np - is Na + Nhc, the number of bits to the right of the binary point
 *    in the integer "time" variable. To the left of the point, it indexes
 *    the input array (X), and to the right, it is interpreted as a number
 *    between 0 and 1 sample of the input X.  Np must be less than 16 in
 *    this implementation.
 *
 * Nh - is the number of bits in the filter coefficients. The sum of Nh and
 *    the number of bits in the input data (typically 16) cannot exceed 32.
 *    Thus Nh should be 16.  The largest filter coefficient should nearly
 *    fill 16 bits (32767).
 *
 * Nb - is the number of bits in the input data. The sum of Nb and Nh cannot
 *    exceed 32.
 *
 * Nhxn - is the number of bits to right shift after multiplying each input
 *    sample times a filter coefficient. It can be as great as Nh and as
 *    small as 0. Nhxn = Nh-2 gives 2 guard bits in the multiply-add
 *    accumulation.  If Nhxn=0, the accumulation will soon overflow 32 bits.
 *
 * Nhg - is the number of guard bits in mpy-add accumulation (equal to Nh-Nhxn).
 *
 * NLpScl - is the number of bits allocated to the unity-gain normalization
 *    factor.  The output of the lowpass filter is multiplied by LpScl and
 *    then right-shifted NLpScl bits. To avoid overflow, we must have 
 *    Nb+Nhg+NLpScl < 32.
 */


void resample_getopts(eff_t effp,int n, char **argv);
void resample_start(eff_t effp);

int makeFilter(HWORD *Imp,HWORD *ImpD,UHWORD *LpScl,UHWORD Nwing,double Froll,double Beta);
/*HWORD Imp[], ImpD[];
UHWORD *LpScl, Nwing;
double Froll, Beta;*/

void resample_flow(eff_t effp,long * ibuf,long * obuf,long * isamp,long * osamp);


long SrcUp(HWORD  *X,HWORD * Y,double Factor, UWORD * Time,UHWORD Nx,UHWORD Nwing,UHWORD LpScl,HWORD * Imp,HWORD * ImpD,BOOL Interp);
int SrcUD(HWORD  *X,HWORD * Y,double Factor, UWORD * Time,UHWORD Nx,UHWORD Nwing,UHWORD LpScl,HWORD * Imp,HWORD * ImpD,BOOL Interp);
void resample_drain(eff_t effp,unsigned long * obuf,unsigned long * osamp);
void resample_stop(eff_t effp);


IWORD FilterUp(HWORD *Imp,HWORD* ImpD,UHWORD Nwing,BOOL Interp,HWORD* Xp,HWORD Ph,HWORD Inc);

IWORD FilterUD(HWORD *Imp,HWORD * ImpD,UHWORD  Nwing,BOOL Interp,HWORD * Xp,HWORD  Ph,HWORD  Inc,UHWORD  dhb);
double Izero(double x);



void setUpFileParams (long inRate, long outRate, short numBits, short numChannels);

OSErr convertSDIIFormat (FSSpec inFile, FSSpec outFile, long destRate, short destBits, short destChans);