#ifndef __MrAlias2effects__
#define __MrAlias2effects__

#include "juce.h"
#include "stuff.h"

class M_Effect {
public:
    M_Effect() {reset();}
    ~M_Effect(){};
    inline void stprocess(float &L, float &R, int m, float mix);
    void reset() {counterL=counterR=0;}
private:
    int counterL, counterR;
};

class mdaLimiter {
public:
    mdaLimiter(void);
    ~mdaLimiter(void);
    void stprocess(float &L, float &R);
private:
    float gain;
};

class decimate {
public:
    decimate(void);
    ~decimate(void);
    float process(float i, float rate);

private:
    //float y;
    float lasty, cnt;
};


class TLP24DB {
public:
    TLP24DB(void);
    ~TLP24DB(void);
    float process(float inp);
    void stprocess(float &inpL, float &inpR);
    void reset();
    void update(float Frq, float Res, float invSR);

private:
    float x, y1, y2, y3, y4, oldx, oldy1, oldy2, oldy3;
    float xR, y1R, y2R, y3R, y4R, oldxR, oldy1R, oldy2R, oldy3R;
    float t, t2, f, k, p, r;
    float res, z;
    unsigned long noise;
};

class SVF {
public:
    SVF(void);
    ~SVF(void);
    float process(float input, float cutoff, float value, float invSR, int mode);
    void stprocess(float &L, float &R, float cutoff, float value, float invSR, int mode);
private:
    float low, lowR;
    float band, bandR;
};

class OnePoleLPF {
public:
    OnePoleLPF();
    ~OnePoleLPF();
    float process(float in, float x);
    void updateSR(float SR);
private:
    float lastout;
    float invsr;
};

class RemoveDC {
public:
    RemoveDC();
    ~RemoveDC();
    void init(float SR);
    inline float process(float in);
private:
    float lastin, lastout, R;
};

class divider {
public:
    divider();
    ~divider();
    float process(float in, float threshold, int target);
private:
    int clock;
    bool high, lasthigh;
};

class Sine {
public:
    Sine();
    ~Sine();
    float process(float x, float sampleRateRecip, int target);
    void reset();
private:
    float ramp;
    float delta_ramp;
    float close_enough;
    float prev_x;
    int counter;
};

///*
//Public source code by alex@smartelectronix.com
//Simple example of implementation of formant filter
//Good for spectral rich input like saw or square
//*/

const double coeff[5][11]= {
    { 4.09431e-07,
    8.997322763, -37.20218544, 93.11385476, -156.2530937, 183.7080141, ///U
    -153.2631681, 89.59539726, -35.12454591, 8.338655623, -0.910251753
    },
    { 1.13572e-06,
    8.994734087, -37.2084849, 93.22900521, -156.6929844, 184.596544, ///O
    -154.3755513, 90.49663749, -35.58964535, 8.478996281, -0.929252233
    },
    { 8.11044e-06,
    8.943665402, -36.83889529, 92.01697887, -154.337906, 181.6233289,
    -151.8651235, 89.09614114, -35.10298511, 8.388101016, -0.923313471 ///A
    },
    { 4.36215e-06,
    8.90438318, -36.55179099, 91.05750846, -152.422234, 179.1170248, ///E
    -149.6496211,87.78352223, -34.60687431, 8.282228154, -0.914150747
    },
    { 3.33819e-06,
    8.893102966, -36.49532826, 90.96543286, -152.4545478, 179.4835618,
    -150.315433, 88.43409371, -34.98612086, 8.407803364, -0.932568035 ///I
    }
};

class formant_filter {
public:
    formant_filter();
    ~formant_filter();
    float process(float in, float r, float vowelnum, bool limit=false);
private:
    double memory[10];
    //mdaLimiter limiter;
};

inline float mixEP(float a, float b, float m) {
    //m==0.0: all a
    //m==1.0: all b
    if (m<=0.f) return a;
    if (m>=1.f) return b;
    return fastsine(0.5f*float_Pi*m)*b + fastcosine(0.5f*float_Pi*m)*a;
}

inline float mixEI(float a, float b, float m) {
    //m==0.0: all a
    //m==1.0: all b
    if (m<=0.f) return a;
    if (m>=1.f) return b;
    //equal intensity (linear)
    return m*b + (1.f-m)*a;
}

inline double mixEI(double a, double b, float m) {
    //m==0.0: all a
    //m==1.0: all b
    //if (m==0.f) return a;
    //if (m==1.f) return b;
    //equal intensity (linear)
    return m*b + (1.0-m)*a;
}

inline float mixB(float a, float b, float m) {
    //m==0.0: all a
    //m==1.0: all b
    if (m<=0.f) return a;
    if (m>=1.f) return b;
        return jmin(1.f,2.f*m)*b + jmin(1.f,(2.f-2.f*m))*a;
}

inline sfloat mix(sfloat a, sfloat b, float m, int mode=1) {
    //m==0.0: all a
    //m==1.0: all b
    if (m<=0.f) return a;
    if (m>=1.f) return b;
    switch (mode)
    {
    case 1: //equal power
        return b*(float)sin(0.5*double_Pi*m) + a*(float)cos(0.5*double_Pi*m);
    case 0: //equal intensity (linear)
        return b*m + a*(1.f-m);
    case 2: //balance control
        return b*jmin(1.f,2.f*m) + a*jmin(1.f,(2.f-2.f*m));
    default: return a+b;
    }
}

inline double mixEP(double a, double b, float m) {
    if (m<=0.f) return a;
    if (m>=1.f) return b;
    //m==0.0: all a
    //m==1.0: all b
//equal power
        return (sin(0.5*double_Pi*m)*b + cos(0.5*double_Pi*m)*a);
}

inline void xmix(float& a, float& b, float m) {

    //equivalent to
    //a = mix(a,0,m,2);
    //b = mix(0,b,m,2);

    if (m<=0.f) b=0.f; return;
    if (m>=1.f) a=0.f; return;
    a *= jmin(1.f,2.f*(1.f-m));
    b *= jmin(1.f,2.f*m);
}

inline void smix(float& aL, float& aR, float bL, float bR, float m) {
    //m==0.0: all a
    //m==1.0: all b
    if (m<denorm) return;
	m=jmin(1.f,m);
    aL = fastsine(0.5f*float_Pi*m)*bL + fastcosine(0.5f*float_Pi*m)*aL;
    aR = fastsine(0.5f*float_Pi*m)*bR + fastcosine(0.5f*float_Pi*m)*aR;
}

inline void smix2(float& aL, float& aR, float bL, float bR, float m/*, const int mode=0*/) {
    //m==0.0: all a
    //m==1.0: all b
    if (m<denorm) return;
	m=jmin(1.f,m);
//    switch (mode)
//    {
//    case 0: //equal intensity
        aL = m*bL + (1.f-m)*aL;
        aR = m*bR + (1.f-m)*aR;
//        break;
//    case 1: //equal power
//        aL = (float)(sin(0.5*double_Pi*m)*bL + cos(0.5*double_Pi*m)*aL);
//        aR = (float)(sin(0.5*double_Pi*m)*bR + cos(0.5*double_Pi*m)*aR);
//        break;
//    case 2: //balance control
//        aL = jmin(1.f,2.f*m)*bL + jmin(1.f,(2.f-2.f*m))*aL;
//        aR = jmin(1.f,2.f*m)*bR + jmin(1.f,(2.f-2.f*m))*aR;
//        break;
//    default:
//        break;
//    }
}

inline void xpanEI(float &a, float &b, float pan) {
    //pan two signals inversely
    //equal intensity
//    if (pan==0.f) return;
//    if (pan==1.f) {
//        swapVariables(a,b);
//        return;
//    }
//    float temp=0.f;
//    if (b==0.f) {
//        temp = (1.f-pan)*a;
//        b = pan*a;
//        a = temp;
//        return;
//    }
	pan = jlimit(0.f,1.f,pan);
    float temp = pan*b + (1.f-pan)*a;
    b = pan*a + (1.f-pan)*b;
    a = temp;
}

inline void xpanEP(float &a, float &b, const float pan) {
    //pan two signals inversely
    if (pan<=0.f) return;
    if (pan>=1.f) {
        swapVariables(a,b);
        return;
    }
    float temp=0.f;
    if (b==0.f) {
        temp = fastcosine(0.5f*float_Pi*pan)*a;
        b = fastsine(0.5f*float_Pi*pan)*a;
        a = temp;
        return;
    }
    temp = fastsine(0.5f*float_Pi*pan)*b + fastcosine(0.5f*float_Pi*pan)*a;
    b = fastsine(0.5f*float_Pi*pan)*a + fastcosine(0.5f*float_Pi*pan)*b;
    a = temp;
}

inline float waveshape_distort(float in) {
    return in-0.15f*in*in-0.15f*in*in*in;
}

inline float clip (float x, float a, float b) {
//    float x1 = fabs (x-a);
//    float x2 = fabs (x-b);
//    x = x1 + (a+b);
//    x -= x2;
//    x *= 0.5;
//    return x;
    return 0.5f*(x-fabs((fabs(x-a)+(a+b))-b));
}

//inline float clip2 (float x, float a, float b) {
//    if (x>b) x=b;
//    else if (x<a) x=a;
//    return (x);
//}


//void smbPitchShift(float pitchShift, long numSampsToProcess, long fftFrameSize, long osamp, float sampleRate, float *indata, float *outdata);

inline float RemoveDC::process(float in) {
    lastout = in - lastin + R * lastout + denorm;
    lastin = in;
    return lastout;
}

inline void M_Effect::stprocess(float &L, float &R, int m, float mix) {
    float mL,mR;
	float threshold = 0.5f;
    if (counterL==0) {
        if (L>=threshold) {
            counterL = m;
            mL=1.f;
        }
        else mL=-1.f;
    }
    else {
        --counterL;
        mL=1.f;
    }
    if (counterR==0) {
        if (R>=threshold) {
            counterR = m;
            mR=1.f;
        }
        else mR=-1.f;
    }
    else {
        --counterR;
        mR=1.f;
    }
    smix(L,R,mL,mR,mix);
}

class EnvelopeFollower
{
public:
   EnvelopeFollower();

   void setup( double attackMs, double releaseMs, double sampleRate );

   float process( float v );


protected:
   double envelope;
   double a;
   double r;
};



#endif
