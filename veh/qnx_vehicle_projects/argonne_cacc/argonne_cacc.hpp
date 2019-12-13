#pragma once
//#include <db_utils.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//#include <iostream>
#include <stdio.h>
//#include <sys_os.h>
#include <time.h>
#include "long_control.hpp"

#define PRIUS 0
#define TAURUS 1
#define ACCORD 2

#define OPEN_LOOP 0
#define CRUISE 1
#define ACC 2
#define CACC 3
#define E_BRAKE 4

#define TS 0.05

void Initialization_task();
bool Read_inputs();
bool Process_data();
bool Write_outputs();
void End_tasks();

int vehicle_id;
double sampling_period;
int control_mode;

double i_long_speed;
double i_long_acceleration;
double i_relative_distance_to_target;
double i_relative_speed_to_target;
double i_torque_applied;
int    i_transmission_gear;
double i_control_mode;
double i_time_gap;
double i_setpoint_speed;
double i_throttle_test;
double i_deceleration_test;
double i_desired_acceleration;

double o_throttle_command;
double o_brake_command;
double o_deceleration_command;
long_control* control_structure;
