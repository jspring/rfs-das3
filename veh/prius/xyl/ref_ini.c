/**************************************************************
 Using linear v-a relation
 Shift speed point is based on CalTrans new spec data
 
 To be used with spd_init only run once

                Simulated 

**************************************************************/

#include <stdio.h>
#include <math.h>

#include "veh_long.h"
//#include <stdafx.h>


void ref_ini(float v_point[N_pt], float c[N_pt-1], float d[N_pt-1])
              
{
	static float coeff = 0.0;
	int i;

	const float x[N_pt]={  0.0,     2.0,      4.0,    6.0,           //For new Freightliner, from data
                           8.0,     10.0,     12.0,   14.0,               
                           16.0,    18.0,     20.0,   22.0,              
                           24.0,    26.0,     28.00,  30.0,             
                           32.0,    33.0,     34.0,   35.0,
                           36.0,    37.0,     38.0,   39.0,               
                           40.0}; 

       static float y[N_pt]={ 0.0,   0.0,  0.0,   0.0,      // Reduced on 05_20_03 // 1.05  Old// Reduced in May, 2003; Tested form two vehicles 10_29_03; for 3 vehs SR722 Nevada Sept. 2010
                           0.0,    0.0,  0.0,    0.0,
                           0.0,   0.0,  0.0,    0.0,
                           0.0,    0.0,  0.0,   0.0,
                           0.0,   0.0,  0.0,   0.0,
                           0.0,   0.0,  0.0,   0.0,
                           0.0};  
                                                   
          coeff=0.9;
           
          y[0]=1.0;
          y[1]=1.2;
          y[2]=1.4;
          y[3]=1.6;      
          y[4]=1.8;
          y[5]=2.0;
          y[6]=2.0;
          y[7]=1.9;
          y[8]=1.9;
          y[9]=1.8;
          y[10]=1.8;
          y[11]=1.8;
          y[12]=1.7;
          y[13]=1.6;
          y[14]=1.4;
          y[15]=1.2;
          y[16]=1.0;
          y[17]=0.9;
          y[18]=0.8;
          y[19]=0.7;
          y[20]=0.6;
          y[21]=0.5;
          y[22]=0.4;
          y[23]=0.3;
          y[24]=0.2;
	
    for (i=0;i<=N_pt-2;i++)
       {
          
          c[i]=(y[i]-y[i+1])/(x[i]-x[i+1]);
          d[i]=(-x[i+1]*y[i]+x[i]*y[i+1])/(x[i]-x[i+1]);
       }
    for (i=0;i<=N_pt-1;i++)
       v_point[i]=x[i];
    
}    
    


