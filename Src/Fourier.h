#ifndef __Fourier_H
#define __Fourier_H	

#include "Header_Config.h"

#define PI 3.1415926535897932384626433832795028841971               //����Բ����ֵ
//�˴��޸Ĳ�������
#define FFT_N 256

struct compx {float real,imag;};                                    //����һ�������ṹ 

struct compx EE(struct compx a,struct compx b);
void FFT(struct compx *xin);


#endif
