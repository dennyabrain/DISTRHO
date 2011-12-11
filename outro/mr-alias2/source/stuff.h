#ifndef MrAlias2Stuff_H
#define MrAlias2Stuff_H

#include "juce.h"

#define PI          3.1415926535897932384626433832795
#define TWO_PI      6.283185307179586476925286766559
#define INV_PI      0.31830988618379067153776752674503
#define float_2PI   6.28318530717958647692f
#define float_InvPi 0.318309886183790671538f

#define midiScaler 0.00787401574803149606299212598425197f // 1/127
#define velScaler 0.0079365079365079365079365079365079f // 1/126
#define goodXmlChars T("abcdefghijklmnopqrstuvwxyz0123456789")
#define denorm 0.000000000000001f
#define denormRand (JUCE_NAMESPACE::Random::getSystemRandom().nextFloat() * 0.000000000000001f)
#define numFrequencies 128
#define velocityMod 128
#define aftertouchMod 130

inline float linearMap(float x,float y1,float y2,float x1,float x2) {
      if (x1==x2) return x;
      float slope = ((float)(y2-y1))/((float)(x2-x1));
      float y0 = y1 - slope * x1;
      float y = slope * x + y0;
      return y;
}

class sfloat {
public:
    sfloat(float L, float R) {
        this->L=L;
        this->R=R;
    }
    sfloat() {
        this->L=0.f;
        this->R=0.f;
    }
    ~sfloat(){};
    float getL(){return L;}
    float getR(){return R;}
    void setL(float in) {this->L=in;}
    void setR(float in) {this->R=in;}
    inline void balance(float m) {
        //m==0: all L
        //m==1: all R
        m*=2.f;
        L*=jmin(1.f,(2.f-m));
        R*=jmin(1.f,m);
    }
    inline void pan(double m) {
        m*=0.5*double_Pi;
        float temp = R*(float)sin(m) + L*(float)cos(m);
        R = L*(float)sin(m) + R*(float)cos(m);
        L = temp;
    }
    void operator = (sfloat i) {
        this->L = i.L;
        this->R = i.R;
    }
    void operator += (sfloat i) {
        this->L += i.L;
        this->R += i.R;
    }
    sfloat operator + (sfloat i) {
        return sfloat(L+i.L,R+i.R);
    }
    sfloat operator + (float i) {
        return sfloat(L+i,R+i);
    }
    sfloat operator* (float i) {
        return sfloat(L*i,R*i);
    }
    void operator*= (float i) {
        L*=i;
        R*=i;
    }
    bool operator == (sfloat i) {
        return this->L==i.L && this->R==i.R;
    }
    bool operator != (sfloat i) {
        return this->L!=i.L || this->R!=i.R;
    }
    float L,R;
};

float fastsine(float);
float fastcosine(float);
//double fsqrt (double);
//double fpow(double a, double b);
double fpow2(double);
//float fexp(float);

inline float paramToLfoFreq(float in)	{ return in*in*20.f; }
inline float lfoFreqToParam(float freq) { return sqrt(freq/20.f); }

const inline unsigned short CombineBytes(unsigned char First, unsigned char Second){
	unsigned short _14bit;
	_14bit = (unsigned short)Second;
	_14bit <<= 7;
	_14bit |= (unsigned short)First;
	return(_14bit);
}

#endif