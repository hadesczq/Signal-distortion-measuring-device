#ifndef __Fourier_H
#define __Fourier_H	

#include "Header_Config.h"

#define PI 3.1415926535897932384626433832795028841971               //定义圆周率值
//此处修改采样点数
#define FFT_N 256

struct compx {float real,imag;};                                    //定义一个复数结构 

struct compx EE(struct compx a,struct compx b);
void FFT(struct compx *xin);


#endif
