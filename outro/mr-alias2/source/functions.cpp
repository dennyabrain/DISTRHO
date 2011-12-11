#include "stuff.h"


float fastsine(float x)
{
//    while(x <-PI) x += TWO_PI;
//    while(x > PI) x -= TWO_PI;

    const float B = (float)(1.2732395447351626861510701069801);
    const float C = -(float)(0.40528473456935108577551785283891);

    float y = B * x + C * x * fabs(x);

    //#ifdef EXTRA_PRECISION
    //  const float Q = 0.775;
        const float P = 0.225f;

        return P * (y * fabs(y) - y) + y;   // Q * y + P * y * abs(y)
    //#endif
}

float fastcosine(float x) {
    const float half_Pi = 1.5707963267948966192313216916398f;
    return fastsine(x+half_Pi);
}

//double fsqrt (double y) {
//    double x, z, tempf;
//    unsigned long *tfptr = ((unsigned long *)&tempf) + 1;
//
//	tempf = y;
//	*tfptr = (0xbfcdd90a - *tfptr)>>1; /* estimate of 1/sqrt(y) */
//	x =  tempf;
//	z =  y*0.5;                        /* hoist out the “/2”    */
//	x = (1.5*x) - (x*x)*(x*z);         /* iteration formula     */
//	x = (1.5*x) - (x*x)*(x*z);
//	//x = (1.5*x) - (x*x)*(x*z);
//	//x = (1.5*x) - (x*x)*(x*z);
//	//x = (1.5*x) - (x*x)*(x*z);
//	return (x*y);
//}

//double fpow(double a, double b) {
//    int tmp = (*(1 + (int32 *)&a));
//    int tmp2 = (int32)(b * (tmp - 1072632447) + 1072632447);
//    double p = 0.0;
//    *(1 + (int32 * )&p) = tmp2;
//    return p;
//}

double fpow2(double b) {
    double p = 0.0;
    *(1 + (int32 * )&p) = (int32)(b*1109377 + 1072632447);
    return p;
}

//float fexp(float x)  {
//    return 1.f + x + x*x*0.5f ;//+ x*x*x*0.33333333333f + x*x*x*x*0.25f;
//}
