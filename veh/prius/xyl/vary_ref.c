/*******************************************************************************************************************************************

    vary_ref.c
    
 Based on tran_ref.c  
 Based on gen_ref.c
 
 con_state. drive_mode=1;    //manual_sw; = 0-stay, 1-auto(CC),  2-auto_manual,  3-manual, 4-ACC, 5-CACC, 
 
 
 To dynamically generate reference trajectory for truck.

 To be used with ref_ini.c

 Simulated in truck_ref.

 Modified on               07/16/01
 Compiled on               07/19/01
 Modified on               08/24/01
 Tested   on               03/06/02
 Used Until                03/20/02
 Modified last part on     03/20/02
 Begin to use G on   03/20/02
 To put in trnsition on    03/22/02
 Corrected man_id[0] on    04/09/03
 Changed from switch-loop to if-loop such that it can always be called in all maneuvers  10/22/03 
 man_id = 7 is added for cruise speed    10_27_03 CRO
 Tested for transition at CRO for high sped  OK but not perfect yet                                          10/28/03
 Modified for variable Max_spd based on tran_ref()                                                                       09/06/10
 Removed man_id[0] assignment here; moved to maneuver();                                                  03/26/11
 Both man_id and man_des are used;                                                                                               03/26/11
 Deceleration has been approved;                                                                                                      03/27/11
 
                                                   XY_LU

***********************************************************************************************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#include "veh_long.h"
#include "coording.h"
#define PI 3.1415927


void vary_ref(float step_t, float t_control, float v_point[N_pt], float c[N_pt-1],
               float d[N_pt-1], control_config_typ* cnfg_pt, float grade, switch_typ* sw_rd_pt, control_state_typ *con_st_pt, 
               manager_cmd_typ* mng_cmd_pt,int man_id[2], float x_ref[2])        
{
    static float a=0.0, decel=0.0, v=0.0;
    static float t_brk=0.0, acc_t=0.0, dcc_t=0.0, dcc_intv=0.0;
    static int dcc_intv_sw =1;
    static float a_buff=0.0, d_buff=0.0, t_temp1=0.0, t_temp2=0.0, t_smth=0.0;
    static float stop_period, v_final=0.0;
    const  float smth_v=0.8;
   // static float G=0.0;  
    static int acc_s=1;  // max_spd_sw=1;
	static int sw_2_1=ON; // spd_ini_sw=1; 
    int i;
    static float Max_spd=0.0, Max_spd_pre=0.0,Max_dcc=0.0,t_ctrl=0.0, delta_t=0.0; 

	extern float min_f(float, float);
   
      Max_spd = con_st_pt-> max_spd;
      if (Max_spd_pre-con_st_pt-> max_spd > 0.5)  // 0.5
	  {
		  dcc_intv_sw=1;
		  //Max_spd_pre=con_st_pt-> max_spd;
	  }
    
      //if (man_id[0] == 4)  // changed on 06_02_15
	 /* if ((mng_cmd_pt->man_des == 4) || (mng_cmd_pt->man_des == 40) || (mng_cmd_pt->man_des == 41))
         Max_dcc = 0.2*cnfg_pt-> max_dcc;   // for transition; 0.5 => 0.3
      else
         Max_dcc = cnfg_pt-> max_dcc;
		 */
	  Max_dcc = 0.3*cnfg_pt-> max_dcc;   

      delta_t = step_t;
      t_ctrl = t_control;
      
      for (i=0;i<N_pt-1;i++)
           {
                  if (v >= v_point[i] && v < v_point[i+1])                                                    
                        cnfg_pt -> max_acc = c[i]*v+d[i] - G*sin(grade);                                                                                                                  
           }   
           
	  if (mng_cmd_pt-> drive_mode != 2)
        {  
		   //spd_ini_sw=1;
           t_brk=0.0;
           acc_t=0.0;
           dcc_t=0.0;           
           t_temp1=0.0;
		   v=con_st_pt-> spd;
		   a=con_st_pt-> acc;
		   dcc_intv_sw = 1;
		   
        } 		
	  else  //if (mng_cmd_pt-> drive_mode == 2)
		{				
				if (v <= Max_spd-v_threshold)
				{
					acc_s=1;                               
					dcc_t=0.0;		
					dcc_intv_sw=1;
				}			
				else if (v >= Max_spd+v_threshold)
				{
					acc_s=-1;					
					acc_t=0.0;   
					t_temp1=0.0;
				}
				else
				{
					acc_s=0;					
					Max_spd_pre = Max_spd;	  // removed on 	06_09_16
					t_temp1=0.0;
					dcc_intv_sw=1;
				}

                if (acc_s == 1)
                {
                  if (v < Max_spd - 3.0*smth_v)
                    {	                  
                      acc_t +=delta_t;
                      if (acc_t < 5.0)
                         a=(acc_t/5.0)*cnfg_pt-> max_acc;
                      else
                         a=cnfg_pt-> max_acc;
					  a_buff=a;
                      v += a*delta_t;
					  t_temp1=0.0;
                    }
                  else if (v <=  Max_spd-smth_v)
                    {                                
                           a=cnfg_pt-> max_acc;
                           v += a*delta_t;
                           a_buff=a;   
						   t_temp1=0.0;
						   acc_t=0.0;
                    }
                  else if (v <= Max_spd-v_threshold)
                       {
						   t_temp1 += delta_t;  
                           t_smth=2.0*smth_v/a_buff;
                           if (t_temp1 <= t_smth)
                              {                                                  
                                 a=-a_buff*(t_temp1/t_smth) + a_buff;
                                 v += a*delta_t;                                 
                              }  
						   acc_t=0.0;
                       }                         
                   else
                       {
						   acc_s=0;
                           a=0.0;
                           v=Max_spd;
						   t_temp1=0.0;
						   acc_t=0.0;
                       }
                 }  // accel end

                 else if (acc_s == -1)   // Decelerate to Max_spd
                 {	                   
	                  if (v > Max_spd + 3.0*smth_v)
                    {	                  
                      dcc_t +=delta_t;
                      if (dcc_t < 5.0)
                         decel=-(dcc_t/5.0)*Max_dcc;
                      else
                         decel=-Max_dcc;
                      v += decel*delta_t;
					  t_temp2=0.0;
					  d_buff=decel; 
                    }
                  else if (v >=  Max_spd+smth_v)
                    {                                
                        decel=-Max_dcc;
                        v += decel*delta_t;
                        d_buff=decel;   
						t_temp2=0.0;
						dcc_t=0.0;
                    }
                  else if (v >= Max_spd+v_threshold)
                    {
						t_temp2 += delta_t;  
                        t_smth=2.0*smth_v/fabs(d_buff);
                        if (t_temp2 <= t_smth)
                        {                                                  
                            decel=fabs(d_buff)*(t_temp2/t_smth) + d_buff;
                            v += decel*delta_t;                                 
                        }  
						dcc_t=0.0;
                    }                          
                   else
                    {
                       	   acc_s=0;
                           a=0.0;
                           v=Max_spd;
						   t_temp2=0.0;
						   dcc_t=0.0;
                    }
                 }      // dcc end 
                 else  // (acc_s == 0)
                 {
                      a=0.0;
                      v=Max_spd; 
					  acc_t=0.0;
					  dcc_t=0.0;
					  t_temp1=0.0;
					  t_temp2=0.0;
                 }
			}   // drive_mode ==2 end
                                                                              
    if (a > cnfg_pt-> max_acc)
       a = cnfg_pt-> max_acc;
    if (a < -Max_dcc)
       a = -Max_dcc;
    x_ref[0]=a;
    x_ref[1]=v;      
 
   // Max_spd_pre=cnfg_pt-> max_spd;    // update buffer; put back on 06_08_16
}    

