
typedef struct {
   float ego_speed;
   float ego_accel;
   float preceding_dist;
   float preceding_rel_speed;
   float preceding_rel_accel;
} long_input_prius_t;

typedef struct{
   float accel; // positive values=acceleration, negative values=braking
} long_output_prius_t;
