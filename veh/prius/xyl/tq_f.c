#include <stdio.h>
#include <math.h>
//#include <signal.h>
//#include <string.h>
//#include <sys/types.h>
//#include <unistd.h>
#include <stdlib.h>
//#include <stdafx.h>

int tq_f(int phase_sw, float spd, float tq, float *accel_cmd)
{
	static int sw=0;
	static float v=0.0, q=0.0, a=0.0;
	
	sw=phase_sw;
	v=spd;
	q=tq;
	
	if (sw == 1)
		a = -0.079646 + 0.003503*v + 0.001935*q - 0.000326*v*v + 0.000002*v*q;
	else if (sw == 2)
		a = -0.08138 + 0.002967*v + 0.002007*q - 0.000303*v*v + 0.000002*v*q;
	else if (sw == 3)
		a = 0.0;
	else;
	
	*accel_cmd=a;
	
	return 1;
}