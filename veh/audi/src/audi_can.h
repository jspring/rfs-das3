#include <di_soft.h>

#define DB_AUDI_TYPE	1500
#define DB_AUDI_VAR	DB_AUDI_TYPE

typedef struct {
        int brake;
        double brake_pressure;
        double lat_acc;
        double long_acc;
        double throttle;
        double steering_angle;
        double veh_speed;
        double yaw;
        int turn_lights;
        int cc;
        int gear;
        int turn_signal;
        int wiper;
	usb4761_digin_typ ignition;
} audi_t;

