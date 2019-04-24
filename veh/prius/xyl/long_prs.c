
#include <stdio.h>
#include <math.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
//#include <unistd.h>
#include <stdlib.h>

//#include <local.h>
//#include <sys_ini.h>
//#include <sys_rt.h>
//#include <sys_arma.h>
//#include <sys_list.h>
//#include <sys_buff.h>

#include "coording.h"
#include "veh_long.h"
#include "long_prius.h"
#include "long_ctl_prius.h"

/*      Parameters for I15. For N11, values were: 1.0, 6.0 and 30.0     */

#define SPLITTING_DIST          7.0     /* Distance to split [m] */
#define DES_FOLLOW_DIST         8.0     /* Inter-car spacing [m] */
#define FALLBACK_TIME_PAR       46.0    /* Time parameter for car #8 to fall back to end of platoon [sec] */

#define STOP_BRAKE_PRESSURE     300.0   /* Brake pressure required when car is stopped [psi] */
#define MAN_TEMP_TO_PRESS       0.07267 /*      tmtopm  */
#define BRAKE_FLUID_COEFF       0.1670  /*      Cq      */

/*      Vehicle parameters.     */

#define MASS                    1701.0  /*      [kg]    */
#define I_ENG                   0.169
#define I_WHL                   2.603   /*      Lincoln */
#define VEHICLE_WHEEL_RADIUS    0.323   /*      [m]     */
#define VEHICLE_DRAG_COEFF      0.3693
#define VEHICLE_ROLL_FRICTION   0.0     /*      ?       */

#define MAX_DATA_LOG            30000
#define NUM_AIR_INDEX           15
#define NUM_AIR_VALS            14
#define MAXHOSTNAMELEN			256


static control_state_typ con_state;
static control_state_typ* con_state_pt;
static control_config_typ config;
static control_config_typ* config_pt;
static switch_typ sw_read;
static switch_typ* sw_read_pt;
static jbus_read_typ jbus_read;
static jbus_read_typ* jbus_read_pt;
static sens_read_typ sens_read;
static sens_read_typ* sens_read_pt;
static con_output_typ con_output;
static con_output_typ* con_output_pt;
static road_info_typ  road_info;
static road_info_typ* road_info_pt;
static manager_cmd_typ manager_cmd;
static manager_cmd_typ* manager_cmd_pt;

float c[N_pt-1]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
float d[N_pt-1]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
float v_p[N_pt]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};


int init_tasks(long_input_prius_t *pctrl, long_output_prius_t *pcmd)

{
                
    char hostname[MAXHOSTNAMELEN+1];
    //FILE *pfin1; 
    
    void ref_ini(float *, float *, float *);
    
     memset(&con_state, 0, sizeof(con_state));      
     memset(&jbus_read, 0, sizeof(jbus_read));                        
	 memset(&sens_read, 0, sizeof(sens_read));
	 memset(&con_output, 0, sizeof(con_output));           
     memset(&sw_read, 0, sizeof(sw_read));
	 memset(&config, 0, sizeof(config));
	 memset(&road_info, 0, sizeof(road_info));
	 memset(&manager_cmd, 0, sizeof(manager_cmd));
     
     con_state. max_brake=MAX_BRAKE;        
     con_state. min_brake=MIN_BRAKE;        
     con_state. ini_brake=INI_BRAKE;        
     con_state. stop_brake=STOP_BRAKE;
              
    
     con_state_pt = &con_state;
     sw_read_pt = &sw_read;        
     con_output_pt = &con_output;
     jbus_read_pt = &jbus_read;
	 sens_read_pt = &sens_read;
	 config_pt = &config;
	 road_info_pt = &road_info;
	 manager_cmd_pt = &manager_cmd;
	 
     ref_ini(v_p, c, d);  // To use config_pt, moved back.
     
     if (first_file == NULL) {
                        open_data_log_infix(&pout, ac_rm_pre, ".dat",
                         &start_time, &old_fileday, &serial_num, monthday, serialnum, tripstr);
                        first_file = pout;
                        first_file_str = ac_rm_pre;
                        pfirst_buff = pbuff_long_trk;
                        sprintf(id_string, "%s%s%s", monthday, tripstr, serialnum);
                } else {
                        open_another_file(&pout, ac_rm_pre,
                                  id_string, ".dat");
                }
            
     return 1;
}



bool_typ run_tasks(long_input_prius_t *pctrl, long_output_prius_t *pcmd)
{

       static int init_sw=1;
       static int end_sw=1;
	   static int man_id[2] = { 0,0 }, man_des[2]= { 0, 0 };
	   static float x_ref[2] = { 0.0, 0.0 };
       
       //static float time_filter = 0.0;
       static float dt=0.0;                   
       static float t_ctrl=0.0;                
       static float global_time = 0.0;     
       
       
      
       static float v, lead_speed=0.0,  preceeding_speed=0.0;               
       static float lead_accel=0.0, acl, preceeding_accel=0.0;
	   static float q = 0.0, a_cmd = 0.0;
	   static int ph_sw = 0;
          
       static float r_star=1.0; 
       static float r_starh;                     
       static float eff_in;
       static float beta;                  
       static float eps_dot = 0.0, eps = 0.0;    
       
       static float tnet, tnet_des; //tnet_p;    
       static float tnet_min = 0.0;   /* Le Sabre has no engine brake on Drive */
       static float tnet_a, tnet_b;       
       static float usyn; //usyn_old;       
	   static float k1 = 0.707, k2 = 0.707;
	   static float rst_total = 0.0, pitch = 0.0;
       
       //const float  tman = 301.0;           /* 301 in Kelvin = 82 F */
       const float  hr = 0.305;             /* Wheel radius of Prius Prime -2019*/
       const float  c_a = 0.3693;           /* Air drag coefficient */
       const float  rd = 1.0/3.06;
       const float  car_length = 5.10;
	   const float f_0 = 0.05175;
    
	   static float decel_cmd = 0.0, accel_cmd = 0.0;
       static float s_1=0.0, s_2=0.0;
           
        char filename[128];
        FILE *pout;
           
     /*---Function declaration---*/
     
  	   void ref_ini(float *, float *, float *);
       int tq_f(int, float, float, float *);     
	   void vary_ref(float, float, float *, float *, float *, control_config_typ*, float, switch_typ*, control_state_typ *,
		   manager_cmd_typ*, int*, float*);
	   int tq_f(int, float, float, float *);
       void filt_1(float, float, float, float, float, float*);                                  
       void filt_2(float, float, float, float, float *, float *);
       void filt_4(float, float, float, float, float, float *,float *);

     
  
	config_pt-> max_spd = 55.0*mph2mps;
	config_pt-> max_acc=1.5;
	
	con_state_pt->max_spd = config_pt-> max_spd;
	
	
	/***********************
	    Timing
	************************/         
        
        dt = 0.05;          /* sec */
		t_ctrl +=dt;
		global_time=t_ctrl;
		
		/***************************************************
		             Sensor reading
		***************************************************/
		
	
		con_state_pt-> spd=pctrl-> ego_speed;
		con_state_pt-> auto_speed=pctrl-> ego_speed;
   		con_state_pt-> auto_acc=pctrl-> ego_accel;
   		con_state_pt-> acc=pctrl-> ego_accel;
   		con_state_pt->front_rang = pctrl-> preceding_dist;
   		
		con_state_pt-> pre_v=pctrl-> preceding_rel_speed + v;
		con_state_pt-> pre_a=pctrl-> preceding_rel_accel + con_state_pt-> acc;
		
		if (t_ctrl < 3.0)
			manager_cmd_pt-> drive_mode = 0;
		else
			manager_cmd_pt-> drive_mode = 2;
        
        /************************************************************/
        /*          */
        /*                                     */
        /************************************************************/
		vary_ref(dt, t_ctrl, v_p, c, d, config_pt, (road_info_pt->grade), sw_read_pt, con_state_pt, manager_cmd_pt, man_id, x_ref);
   		con_state_pt->ref_v=x_ref[1];
		con_state_pt->ref_a=x_ref[0];
		
        /*****************************************************************/
        /*      Calculate time after gear change begins and gear ratio   */
        /*****************************************************************/

		s_2 = v - con_state_pt->ref_v;
		s_1 = con_state_pt->temp_dist - con_state_pt->front_range;
		usyn = -(k1 + k2)*s_2 - k1 * k2*s_1 + con_state_pt->ref_a;

        r_starh = r_star*hr;
        eff_in = (MASS*hr*hr+I_WHL)*r_star*r_star;
        beta = eff_in/r_starh;

		rst_total = c_a * v*v*r_starh + f_0 * MASS*r_starh*(1.0 + sin(pitch));
		tnet_des = beta * usyn + rst_total;
		q=tnet_des;
  
        /**********************************************************/
        /*      Control law to calculate desired throttle angle   */
        /*      using the third sliding surface.                 */
        /**********************************************************/

        if( tnet_des >= tnet_min )
        {
              //adap_a = 1;
              //adap_b = 0;
              tnet_a = tnet_des;
              tnet_b = 0.0;
			  ph_sw = 1;
        }
		else if (tnet_des >= -tnet_min)
		{
			tnet_a = tnet_min;
			tnet_b = - tnet_min;
			ph_sw = 2;
		}
		else
        {
             
              tnet_a = tnet_min;
              tnet_b = tnet_des - tnet_min;
			  ph_sw = 3;

        }

		
		tq_f(ph_sw, v, q, &a_cmd);
        if (ph_sw ==1)
        {
        	accel_cmd=a_cmd;
        	if (accel_cmd <0.0)
        		accel_cmd=0.0;
        	if (accel_cmd > config_pt-> max_acc)	
        		accel_cmd = config_pt-> max_acc;
        	decel_cmd=0.0;
        	pcmd->accel=accel_cmd;
    	}
        if (ph_sw ==2)
        {
	        accel_cmd=0.0;
        	decel_cmd=a_cmd;
        	if (decel_cmd > 0.0)
        		decel_cmd = 0.0;
        	if (decel_cmd < -2.0)
        		decel_cmd = -2.0;
        	pcmd->accel=decel_cmd;
    	}
       
       


        /*********************************************/

        /*      Calculate desired brake pressure     */

        /*********************************************/

        /* Brake control */
       
// NEW MODIFICATION TODAY
              
        if (reopen_data_log_infix(&first_file, file_time, first_file_str,
	    ".dat", &start_time, &old_fileday, &serial_num,
	    monthday, serialnum, tripstr, pfirst_buff))  
		{
		// done for first file in reopen_data_log
		sprintf(id_string, "%s%s%s", monthday, tripstr, serialnum);
		reopen_another_file(&pout, ac_rm_pre, id_string, ".dat", pbuff_long_trk);
		}
  
		fprintf(pout, "%02d:%02d:%02.3f %3i %3i %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f\n",
			timestamp->tm_hour,				//1
            timestamp->tm_min,				//2
            seconds,						//3
            ph_sw,							//4
			manager_cmd_pt-> drive_mode,	//5
			global_time,                    //6 
			dt,								//7
			t_ctrl,							//8
			x_ref[0],						//9
			x_ref[1],						//10
			s_1,                            //11      
			s_2,							//12
			v,                              //13                                
			usyn,                           //14
			r_star,							//15
			r_starh,						//16
			accel_cmd,					    //17
			decel_cmd,						//18
			acl,							//19
			tnet_des,						//20
			tnet_a,							//21
			tnet_b);						//22
			                           

        return( TRUE );                      
}


int exit_tasks(long_input_prius_t *pctrl, long_output_prius_t *pcmd)
{       
        
        *pcmd = inactive_ctrl;
        //if (!clt_update(pclt, DB_LONG_OUTPUT_VAR, DB_LONG_OUTPUT_TYPE, // To deactivate control befopre writing data; Main program is to do it agin.
        //        sizeof(long_output_typ), (void *) pcmd))
        //                printf("long_ctl update long_out failed\n");
        //status = buff_done (pbuff);
        fflush(pout);
        fclose(pout);  
                                  
        return 1;
}
