#include "long_control.hpp"


long_control::long_control(int _veh_id, double _sampling_period, int _control_mode) {
	// Constructor
	this->vehicle_id = _veh_id;
	this->Ts = _sampling_period;
	this->control_mode = _control_mode;
	switch (_veh_id) {
		case(PRIUS):
			 // set Prius variables
			 break;
		case(ACCORD):
			// set Accord variables
			 break;
		case(TAURUS):
			// set Taurus variables
			 break;
		default:
			 break;
	}
	this->speed_tracking_P_gain = 0.5;
	this->speed_tracking_I_gain = 0.1;
	this->acceleration_tracking_P_gain = 0.15;
	this->distance_error_gain = 1.0;
	this->speed_error_gain = 0.8;

	this->throttle_command = 0.;
	this->setpoint_speed = 0.;
	this->torque_applied = 0.;
	this->transmission_gear = 0;
	this->speed_error_integral = 0;
}

long_control::~long_control() {
	// Destructor

}

void long_control::Update_Open_loop_inputs(double i_long_speed, double i_long_acceleration, double i_acceleration) {
	this->long_speed = i_long_speed;
	this->long_acceleration = i_long_acceleration;
	this->desired_acceleration = i_acceleration;
	return;
}

void long_control::Update_Cruise_inputs(double i_long_speed, double i_long_acceleration, double i_torque_applied, int i_transmission_gear, double i_setpoint_speed) {
	
	this->long_speed = i_long_speed;
	this->long_acceleration = i_long_acceleration;
	this->setpoint_speed = i_setpoint_speed;
	this->torque_applied = i_torque_applied;
	this->transmission_gear = i_transmission_gear;

	return;
}

void long_control::Update_Cruise_inputs(double i_long_speed, double i_long_acceleration, double i_setpoint_speed) {

	this->long_speed = i_long_speed;
	this->long_acceleration = i_long_acceleration;
	this->setpoint_speed = i_setpoint_speed;

	return;
}

void long_control::Update_ACC_inputs(double i_long_speed, double i_long_acceleration, double i_relative_distance_to_target, double i_relative_speed_to_target, double i_torque_applied, int i_transmission_gear, double i_time_gap) {
	
	this->long_speed = i_long_speed;
	this->long_acceleration = i_long_acceleration;
	this->relative_distance_to_target = i_relative_distance_to_target;
	this->relative_speed_to_target = i_relative_speed_to_target;
	this->torque_applied = i_torque_applied;
	this->transmission_gear = i_transmission_gear;

	return;
}

void long_control::Execute_control() {
	switch (control_mode) {
		case(OPEN_LOOP):
			// Actuators_signal_from_reference_acceleration(this->long_speed, this->desired_acceleration + this->acceleration_tracking_P_gain * (this->desired_acceleration - this->long_acceleration));
			break;
		case(CRUISE):
			this->desired_acceleration = Apply_speed_tracking_control(this->setpoint_speed, this->long_speed, this->long_acceleration);
			Actuators_signal_from_reference_acceleration(this->long_speed, this->desired_acceleration);
			break;
		case(ACC):			
			// this->desired_acceleration = Apply_gap_feedback_control(Estimate_gap_error(this->current_time_gap, this->relative_distance_to_target, this->long_speed), this->relative_speed_to_target);
			// Actuators_signal_from_reference_acceleration(this->long_speed, this->desired_acceleration);
			break;
		case(CACC):
			// Nothing yet
			break;
	}
	return;
}

double long_control::Apply_speed_tracking_control(double _setpoint_speed, double _long_speed, double _long_acceleration) {
	double speedError = (_setpoint_speed - _long_speed);
	this->speed_error_integral += this->Ts * speedError;
	double accControlOut = this->speed_tracking_P_gain * (_setpoint_speed - _long_speed) + this->speed_tracking_I_gain * this->speed_error_integral;
	// accControlOut += this->acceleration_tracking_P_gain * (accControlOut - _long_acceleration);
	return accControlOut;
}

double long_control::Estimate_gap_error(double _time_gap, double _relative_distance, double _long_speed) {
	double error = _relative_distance - _time_gap * _long_speed;
	return error;
}

double long_control::Apply_gap_feedback_control(double _gap_error, double _relative_speed) {
	double fb_out=0;
	switch (current_control_mode) {
		case(ACC):
			
			break;
		case(CACC):

			break;
	}
	return fb_out;
}

void long_control::Actuators_signal_from_reference_acceleration(double _veh_speed, double _desired_acceleration) {

	if (_desired_acceleration >= -0.5) {
		this->throttle_level_command = Throttle_map_search(_veh_speed, _desired_acceleration);
		this->deceleration_command = 0.00000000;
		this->brake_level_command = 0.00000000;
	}
	if (_desired_acceleration < -0.5 || this->throttle_level_command < 0.00001) {
		this->throttle_level_command = 0.0000000;
		this->deceleration_command = _desired_acceleration;
		this->brake_level_command = -_desired_acceleration / 0.1534; // Brake map first order fitting
	}
	return;
}

double long_control::Throttle_map_search(double _veh_speed, double _desired_acceleration) {
	double speedIndex = fmax(0, fmin(129, _veh_speed * 3.6 - 1));
	double accelerationIndex = fmax(0, fmin(3.5, (_desired_acceleration + 0.5) / 3.5)) * 70;
	double out=0.;
	int speed_floor = floor(speedIndex), speed_ceil = ceil(speedIndex), accel_floor = floor(accelerationIndex), accel_ceil = ceil(accelerationIndex);
	switch (vehicle_id) {
		case(PRIUS):
			if (speed_floor == speed_ceil && accel_floor == accel_ceil)
				out = priusThrottleMap[speed_ceil][accel_floor];
			else if (speed_floor == speed_ceil && accel_floor != accel_ceil)
				out = priusThrottleMap[speed_ceil][accel_ceil] * (accelerationIndex - accel_floor) + priusThrottleMap[speed_ceil][accel_floor] * (accel_ceil - accelerationIndex);
			else if (speed_floor != speed_ceil && accel_floor == accel_ceil)
				out = priusThrottleMap[speed_ceil][accel_ceil] * (speedIndex - speed_floor) + priusThrottleMap[speed_floor][accel_ceil] * (speed_ceil - speedIndex);
			else
				out = (priusThrottleMap[speed_ceil][accel_ceil] * (speedIndex - speed_floor) + priusThrottleMap[speed_floor][accel_ceil] * (speed_ceil - speedIndex))* (accelerationIndex - accel_floor) + 
				(priusThrottleMap[speed_ceil][accel_floor] * (speedIndex - speed_floor) + priusThrottleMap[speed_floor][accel_floor] * (speed_ceil - speedIndex)) * (accel_ceil - accelerationIndex);				
			break;
		case(ACCORD):
			if (speed_floor == speed_ceil && accel_floor == accel_ceil)
				out = accordThrottleMap[speed_ceil][accel_floor];
			else if (speed_floor == speed_ceil && accel_floor != accel_ceil)
				out = accordThrottleMap[speed_ceil][accel_ceil] * (accelerationIndex - accel_floor) + accordThrottleMap[speed_ceil][accel_floor] * (accel_ceil - accelerationIndex);
			else if (speed_floor != speed_ceil && accel_floor == accel_ceil)
				out = accordThrottleMap[speed_ceil][accel_ceil] * (speedIndex - speed_floor) + accordThrottleMap[speed_floor][accel_ceil] * (speed_ceil - speedIndex);
			else
				out = (accordThrottleMap[speed_ceil][accel_ceil] * (speedIndex - speed_floor) + accordThrottleMap[speed_floor][accel_ceil] * (speed_ceil - speedIndex)) * (accelerationIndex - accel_floor) +
				(accordThrottleMap[speed_ceil][accel_floor] * (speedIndex - speed_floor) + accordThrottleMap[speed_floor][accel_floor] * (speed_ceil - speedIndex)) * (accel_ceil - accelerationIndex);
			break;
		case(TAURUS):
			if (speed_floor == speed_ceil && accel_floor == accel_ceil)
				out = taurusThrottleMap[speed_ceil][accel_floor];
			else if (speed_floor == speed_ceil && accel_floor != accel_ceil)
				out = taurusThrottleMap[speed_ceil][accel_ceil] * (accelerationIndex - accel_floor) + taurusThrottleMap[speed_ceil][accel_floor] * (accel_ceil - accelerationIndex);
			else if (speed_floor != speed_ceil && accel_floor == accel_ceil)
				out = taurusThrottleMap[speed_ceil][accel_ceil] * (speedIndex - speed_floor) + taurusThrottleMap[speed_floor][accel_ceil] * (speed_ceil - speedIndex);
			else
				out = (taurusThrottleMap[speed_ceil][accel_ceil] * (speedIndex - speed_floor) + taurusThrottleMap[speed_floor][accel_ceil] * (speed_ceil - speedIndex)) * (accelerationIndex - accel_floor) +
				(taurusThrottleMap[speed_ceil][accel_floor] * (speedIndex - speed_floor) + taurusThrottleMap[speed_floor][accel_floor] * (speed_ceil - speedIndex)) * (accel_ceil - accelerationIndex);
			break;
		default:
			break;
	}
	
	return out;
}

double long_control::Get_throttle_command() {
	return throttle_level_command;
}

double long_control::Get_deceleration_command() {
	return this->deceleration_command;
}

double long_control::Get_brake_command() {
	return this->brake_level_command;
}