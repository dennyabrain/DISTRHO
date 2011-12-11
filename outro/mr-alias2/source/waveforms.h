#ifndef __MrAlias2waves__
#define __MrAlias2waves__

#define ITER 50

/* Minkowski's question mark function */
inline double Minkowski(double x) {
    long p=(long)x; if ((double)p>x) --p; /* p=floor(x) */
    long q=1, r=p+1, s=1, m, n;
    double d=1, y=p;
    if (x<(double)p||(p<0)^(r<=0)) return x; /* out of range ?(x) =~ x */
    for (;;) /* invariants: q*r-p*s==1 && (double)p/q <= x && x < (double)r/s */
    {
        d/=2; if (y+d==y) break; /* reached max possible precision */
        m=p+r; if ((m<0)^(p<0)) break; /* sum overflowed */
        n=q+s; if (n<0) break; /* sum overflowed */

        if (x<(double)m/n) r=m, s=n;
        else y+=d, p=m, q=n;
    }
    return y+d; /* final round-off */
}

inline double Weierstrass(double x, double a) {
    double val = 0;
    int k;

    for (k=1;k<ITER;k++)
        val += sin(PI * pow((double)k,a) * x) / (PI * pow((double)k,a));

    return val ;
}

#endif

