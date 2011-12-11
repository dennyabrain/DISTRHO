#include "effects.h"

TLP24DB::TLP24DB(void)
{
    this->y1 = 0.f;
    this->y2 = 0.f;
    this->y3 = 0.f;
    this->y4 = 0.f;
    this->oldx = 0.f;
    this->oldy1 = 0.f;
    this->oldy2 = 0.f;
    this->oldy3 = 0.f;
    this->y1R = 0.f;
    this->y2R = 0.f;
    this->y3R = 0.f;
    this->y4R = 0.f;
    this->oldxR = 0.f;
    this->oldy1R = 0.f;
    this->oldy2R = 0.f;
    this->oldy3R = 0.f;
    this->noise = 22222;
    this->res = 0.5f;
    this->z = 1.f;
}

TLP24DB::~TLP24DB(void)
{
}

void TLP24DB::reset() {
    this->y1 = 0.f;
    this->y2 = 0.f;
    this->y3 = 0.f;
    this->y4 = 0.f;
    this->oldx = 0.f;
    this->oldy1 = 0.f;
    this->oldy2 = 0.f;
    this->oldy3 = 0.f;
    this->y1R = 0.f;
    this->y2R = 0.f;
    this->y3R = 0.f;
    this->y4R = 0.f;
    this->oldxR = 0.f;
    this->oldy1R = 0.f;
    this->oldy2R = 0.f;
    this->oldy3R = 0.f;
    this->noise = 22222;
}

void TLP24DB::update(float Frq, float Res, float invSR) {
    res=jlimit(0.2f,2.25f,Res)+0.0005f;
    f = jlimit(20.f,20000.f,Frq) * invSR;
    p = f*(1.8f-0.8f*f);
    k = p+p-1.0f;
    t = (1.0f-p)*1.386249f;
    t2 = 12.0f+t*t;
    r = res*(t2+6.0f*t)/(t2-6.0f*t);
    z = (1.5f-f*2.f)*(1.f+1.5f*res);
}

float TLP24DB::process(float inp) {
    noise = (noise * 196314165) + 907633515;
    const unsigned long random = (noise & 0x7FFFFF) + 0x40000000; //generate noise + fast convert to float
    float w = *(float *)&random;
    w = 0.00002f * (w - 3.0f)*res*res;
    inp+=w;

    x = inp - r*y4;
    y1 = x*p + oldx*p - k*y1;
    y1 = waveshape_distort( y1 );
    y2 = y1*p+oldy1*p - k*y2;
    y3 = y2*p+oldy2*p - k*y3;
    y4 = y3*p+oldy3*p - k*y4;
    y4 = y4 - ((y4*y4*y4)/6.0f);
    oldx = x;
    oldy1 = y1+denorm;
    oldy2 = y2+denorm;
    oldy3 = y3+denorm;

    return y4*z;
}

void TLP24DB::stprocess(float &L, float &R) {
    noise = (noise * 196314165) + 907633515;
    const unsigned long random = (noise & 0x7FFFFF) + 0x40000000; //generate noise + fast convert to float
    float w = *(float *)&random;
    w = 0.00002f * (w - 3.0f)*res*res;
    L+=w;
    R+=w;

    x = L - r*y4;
    y1 = x*p + oldx*p - k*y1;
    y1 = waveshape_distort( y1 );
    y2 = (y1+oldy1)*p - k*y2;
    y3 = (y2+oldy2)*p - k*y3;
    y4 = (y3+oldy3)*p - k*y4;
    y4 = y4 - ((y4*y4*y4)*0.16666667f);
    oldx = x;
    oldy1 = y1+denorm;
    oldy2 = y2+denorm;
    oldy3 = y3+denorm;

    xR = R - r*y4R;
    y1R = xR*p + oldxR*p - k*y1R;
    y1R = waveshape_distort( y1R );
    y2R = (y1R+oldy1R)*p - k*y2R;
    y3R = (y2R+oldy2R)*p - k*y3R;
    y4R = (y3R+oldy3R)*p - k*y4R;
    y4R = y4R - ((y4R*y4R*y4R)*0.16666667f);
    oldxR = xR;
    oldy1R = y1R+denorm;
    oldy2R = y2R+denorm;
    oldy3R = y3R+denorm;

    L = y4*z;
    R = y4R*z;
}

decimate::decimate(void)
{
    //this->y = 0.f;
    this->cnt = 0.f;
    this->lasty = 0.f;
}

decimate::~decimate(void)
{
}

float decimate::process(float i, float rate)
{
    rate+=0.005f;

    //long int m=1<<(bits-1);
    //float quantum = powf( 2.0f, bits );
    cnt+=rate;
    if (cnt>=1.f)
    {
        cnt-=1.f;
        //y=(long int)(i*m)/(float)m;
        //y = floorf( i * quantum ) / quantum;
        lasty=0.5f*(i+lasty);
    }
    //lasty=y;
    return lasty;
}

OnePoleLPF::OnePoleLPF () {
    lastout=0.f;
    invsr=1.f/44100.f;
}

OnePoleLPF::~OnePoleLPF() {}

float OnePoleLPF::process(float in, float x)
{
    x*=44100.f*invsr;
    lastout = x*in + (1.f-x)*lastout;
    return x==0.f ? 0.f : lastout;
}

void OnePoleLPF::updateSR(float SR)
{
    invsr=1.f/SR;
}

RemoveDC::RemoveDC () {
    lastin=0;
    lastout=0;
    R = 1.f-(126.f/44100.f);
}

RemoveDC::~RemoveDC() {}

void RemoveDC::init(float SR) {
    lastin=0;
    lastout=0;
    R = 1.f-(126.f/SR);
}

//float RemoveDC::process(float in) {
//    lastout = in - lastin + R * lastout;
//    lastin = in;
//    return lastout;
//}


divider::divider() {
    clock=0;
    high=false;
    lasthigh=false;
}

divider::~divider() {}

float divider::process(float in, float threshold, int target) {
    if (in>threshold) {
        if (!lasthigh) { //going above threshold, toggle
            clock++;
            if (clock>=target) {
                clock=0;
                high=!high;
            }
        }
        lasthigh=true;
    }
    else lasthigh=false;
    return high ? 0.5f : -0.5f;
}

Sine::Sine(){
    ramp = 0.f;
    prev_x = -20.0f;
    counter = 0;
}

Sine::~Sine() {}

float Sine::process(float x, float sampleRateRecip, int target)
{
    ++counter;
    if (counter>=target) {
        counter=0;
        if( x != prev_x )
        {
            prev_x = x;
            float freq = jlimit( 20.f,10000.f, 440.0f * (float)fpow2(x*10.0 - 5.0) );
            //float freq = x * 10000.0f;

            //freq = jlimit(20.f,10000.f,freq);
            delta_ramp = float_2PI * freq * sampleRateRecip;
            close_enough = float_2PI - ( delta_ramp * 0.5f );
        }
    }
    //per sample
    ramp += delta_ramp;
    if( ramp >= close_enough ) ramp -= float_2PI;
    return sin(ramp) * 0.5f;
}

void Sine::reset() {
    ramp = 0.f;
    prev_x = -20.0f;
    counter = 0;
}

SVF::SVF() {
    low=band=0.f;
}

SVF::~SVF() {}

float SVF::process(float input, float cutoff, float value, float invSR, int mode) {
    value=jlimit(0.f,1.f,value);
    const float f = 2.f*fastsine(float_Pi * jlimit(0.f,20000.f,cutoff) * invSR);
    //f = cutoff / (6.f*invSR);
    const float q = 2.f*sqrt(1.0f - atan(sqrt(value*39.0f+0.5f)) * 2.0f * float_InvPi)-0.5f;
    //float scale = q;
    const float scale = 1.f;//sqrt(q);
    //    input += 0.0000000001f;

    low = low + f * band + denorm;
    const float high = scale * input - low - q*band + denorm;
    band = f * high + band + denorm;
    //const float notch = high + low;// + 0.0000000001f;

    switch(mode) {
        case 0: return low;
        case 1: return band;
        case 2: return high + low; //notch
        case 3: return high;
        default: return low;
    }
}

void SVF::stprocess(float &L, float &R, float cutoff, float value, float invSR, int mode) {
 //   value=jlimit(0.2f,2.25f,value);
	//cutoff=jlimit(0.f,12500.f,cutoff);
    const float f = 2.f*fastsine(float_Pi * jlimit(0.f,15000.f,cutoff) * invSR);
    const float q = 2.f*sqrt(1.0f - atan(sqrt(jlimit(0.2f,2.25f,value)*39.0f+0.5f)) * 2.0f * float_InvPi)-0.5f;
    //const float scale = 1.f;//sqrt(q);

    low = low + f * band + denorm;
    lowR = lowR + f * bandR + denorm;
    const float high = /*scale **/ L - low - q*band + denorm;
    const float highR = /*scale **/ R - lowR - q*bandR + denorm;
    band = f * high + band + denorm;
    bandR = f * highR + bandR + denorm;

    switch(mode) {
        case 0:
            L = low;
            R = lowR;
            break;
        case 1:
            L = band;
            R = bandR;
            break;
        case 2:
            L = high + low;
            R = highR + lowR;
            break;
        case 3:
            L = high;
            R = highR;
            break;
        default:
            L = low;
            R = lowR;
            break;
    }
}

formant_filter::formant_filter(){
    for (int i=0;i<10;i++) memory[i]=0.;
}
formant_filter::~formant_filter(){}
//---------------------------------------------------------------------------------
float formant_filter::process(float in, float r, float vowelnum, bool limit)
{
    // 0=U, 1=O, 2=A, 3=E, 4=I

    in=(0.9f*jlimit(0.2f,2.25f,r)+0.1f)*waveshape_distort(in);
    vowelnum=jlimit(0.f,4.f,vowelnum);
    double res;
    if (vowelnum<=1.f) {
        //U-O
        res=( mixEI(coeff[0][0],coeff[1][0],vowelnum) * (double)in +
            mixEI(coeff[0][1],coeff[1][1],vowelnum) *memory[0] +
            mixEI(coeff[0][2],coeff[1][2],vowelnum) *memory[1] +
            mixEI(coeff[0][3],coeff[1][3],vowelnum) *memory[2] +
            mixEI(coeff[0][4],coeff[1][4],vowelnum) *memory[3] +
            mixEI(coeff[0][5],coeff[1][5],vowelnum) *memory[4] +
            mixEI(coeff[0][6],coeff[1][6],vowelnum) *memory[5] +
            mixEI(coeff[0][7],coeff[1][7],vowelnum) *memory[6] +
            mixEI(coeff[0][8],coeff[1][8],vowelnum) *memory[7] +
            mixEI(coeff[0][9],coeff[1][9],vowelnum) *memory[8] +
            mixEI(coeff[0][10],coeff[1][10],vowelnum) *memory[9] );
    }
    else if (vowelnum<=2.f) {
        //O-A
        res=( mixEI(coeff[1][0],coeff[2][0],vowelnum-1.f) * (double)in +
            mixEI(coeff[1][1], coeff[2][1], vowelnum-1.f) *memory[0] +
            mixEI(coeff[1][2], coeff[2][2], vowelnum-1.f) *memory[1] +
            mixEI(coeff[1][3], coeff[2][3], vowelnum-1.f) *memory[2] +
            mixEI(coeff[1][4], coeff[2][4], vowelnum-1.f) *memory[3] +
            mixEI(coeff[1][5], coeff[2][5], vowelnum-1.f) *memory[4] +
            mixEI(coeff[1][6], coeff[2][6], vowelnum-1.f) *memory[5] +
            mixEI(coeff[1][7], coeff[2][7], vowelnum-1.f) *memory[6] +
            mixEI(coeff[1][8], coeff[2][8], vowelnum-1.f) *memory[7] +
            mixEI(coeff[1][9], coeff[2][9], vowelnum-1.f) *memory[8] +
            mixEI(coeff[1][10],coeff[2][10],vowelnum-1.f) *memory[9] );
    }
    else if (vowelnum<=3.f) {
        //A-E
        res=( mixEI(coeff[2][0],coeff[3][0],vowelnum-2.f) * (double)in +
            mixEI(coeff[2][1], coeff[3][1], vowelnum-2.f) *memory[0] +
            mixEI(coeff[2][2], coeff[3][2], vowelnum-2.f) *memory[1] +
            mixEI(coeff[2][3], coeff[3][3], vowelnum-2.f) *memory[2] +
            mixEI(coeff[2][4], coeff[3][4], vowelnum-2.f) *memory[3] +
            mixEI(coeff[2][5], coeff[3][5], vowelnum-2.f) *memory[4] +
            mixEI(coeff[2][6], coeff[3][6], vowelnum-2.f) *memory[5] +
            mixEI(coeff[2][7], coeff[3][7], vowelnum-2.f) *memory[6] +
            mixEI(coeff[2][8], coeff[3][8], vowelnum-2.f) *memory[7] +
            mixEI(coeff[2][9], coeff[3][9], vowelnum-2.f) *memory[8] +
            mixEI(coeff[2][10],coeff[3][10],vowelnum-2.f) *memory[9] );
    }
    else {//(vowelnum<=4.f) {
        //E-I
        res=( mixEI(coeff[3][0],coeff[4][0],vowelnum-3.f) * (double)in +
            mixEI(coeff[3][1], coeff[4][1], vowelnum-3.f) *memory[0] +
            mixEI(coeff[3][2], coeff[4][2], vowelnum-3.f) *memory[1] +
            mixEI(coeff[3][3], coeff[4][3], vowelnum-3.f) *memory[2] +
            mixEI(coeff[3][4], coeff[4][4], vowelnum-3.f) *memory[3] +
            mixEI(coeff[3][5], coeff[4][5], vowelnum-3.f) *memory[4] +
            mixEI(coeff[3][6], coeff[4][6], vowelnum-3.f) *memory[5] +
            mixEI(coeff[3][7], coeff[4][7], vowelnum-3.f) *memory[6] +
            mixEI(coeff[3][8], coeff[4][8], vowelnum-3.f) *memory[7] +
            mixEI(coeff[3][9], coeff[4][9], vowelnum-3.f) *memory[8] +
            mixEI(coeff[3][10],coeff[4][10],vowelnum-3.f) *memory[9] );
    }

    memory[9]= memory[8];
    memory[8]= memory[7];
    memory[7]= memory[6];
    memory[6]= memory[5];
    memory[5]= memory[4];
    memory[4]= memory[3];
    memory[3]= memory[2];
    memory[2]= memory[1];
    memory[1]= memory[0];
    memory[0]= res+denorm;
	res=jlimit(-2.0,2.0,res);

    //if (limit) return limiter.process((float)res,true);
    return (float)res;
}


/*
mda VST plug-ins

Copyright (c) 2008 Paul Kellett

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
mdaLimiter::mdaLimiter() {
//  thresh = (float)pow(10.0, 1.0 - (2.0 * 0.6));
//  att = (float)pow(10.0, -2.0 * 0.15);
//  rel = (float)pow(10.0, -2.0 - (3.0 * 0.5));
//  trim = (float)(pow(10.0, (2.0 * 0.6) - 1.0));

  gain = 1.f;
}

mdaLimiter::~mdaLimiter() {}

//float mdaLimiter::process(float in, float threshold, bool softknee) {
////  float fParam1 = (float)0.91; //thresh
//  float fParam2 = (float)0.50; //trim
//  float fParam3 = (float)0.25; //attack
//  float fParam4 = (float)0.50; //release
//
//  if(softknee) //soft knee
//  {
//    thresh = (float)pow(10.0, 1.0 - (2.0 * threshold));
//  }
//  else //hard knee
//  {
//    thresh = (float)pow(10.0, (2.0 * threshold) - 2.0);
//  }
//  trim = (float)(pow(10.0, (2.0 * fParam2) - 1.0));
//  att = (float)pow(10.0, -2.0 * fParam3);
//  rel = (float)pow(10.0, -2.0 - (3.0 * fParam4));
//
//	float g, at, re, tr, th, lev;
//
//    th = thresh;
//    g = gain;
//    at = att;
//    re = rel;
//    tr = trim;
//
//    if (softknee) {
//      lev = (float)(1.0 / (1.0 + th * fabs(in)));
//      if(g>lev) { g=g-at*(g-lev); } else { g=g+re*(lev-g); }
//    }
//    else
//    {
//      lev = (float)(0.5 * g * fabs(in));
//
//      if (lev > th)
//      {
//        g = g - (at * (lev - th));
//      }
//      else //below threshold
//      {
//        g = g + (float)(re * (1.0 - g));
//      }
//    }
//    return in*tr*g;
//    gain = g;
//}

void mdaLimiter::stprocess(float &L, float &R) {
    float g = gain;
    const float th = 0.1f;
    const float lev = (0.5f * g * fabs(L+R));

    g += (lev>th) ? -(0.00001f*(lev-th)) : 0.0000316227766f*(1.f-g);

    //L *= g;
    //R *= g;
	L=jlimit(-1.f,1.f,L*g);
	R=jlimit(-1.f,1.f,R*g);
    gain = g;
}

EnvelopeFollower::EnvelopeFollower()
{
   envelope=0;
   a = pow( 0.01, 1.0 / ( 10 * 44100 * 0.001 ) );
   r = pow( 0.01, 1.0 / ( 500 * 44100 * 0.001 ) );
}

void EnvelopeFollower::setup( double attackMs, double releaseMs, double sampleRate )
{
   a = pow( 0.01, 1.0 / ( attackMs * sampleRate * 0.001 ) );
   r = pow( 0.01, 1.0 / ( releaseMs * sampleRate * 0.001 ) );
}

float EnvelopeFollower::process( float v )
{
	//double v=fabs(L+R);
	if (v>envelope) envelope = a * ( envelope - v ) + v;
	else			envelope = r * ( envelope - v ) + v;
	return (float)envelope;
} 
