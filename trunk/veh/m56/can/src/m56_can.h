#include <komodo.h>

#ifndef M56_CAN_H
#define M56_CAN_H

//Define some resolutions and offsets
#define steering_angle_res  0.1 //deg
#define steering_velocity_res  4 //deg/sec
#define rpm_res  0.125
#define mean_eff_tq_res 0.5
#define mean_eff_tq_off 400
#define pedal_pos_res  0.392
#define wheel_speed_res  0.04166666
#define vehicle_speed_res  0.01
#define acceleration_res  0.001
#define acceleration_offset  -2.048
#define yaw_rate_res  0.1
#define yaw_rate_offset  -204.8
#define estimated_pressure_res 0.05
#define its_target_pressure_res 0.05
#define targ_eng_tq_res 0.4
#define virtual_accelerator_angle_res 0.392
#define lidar_res 0.1
#define yaw_rate_sensor_res 0.050
#endif

#define DB_M56_VCAN2_MSG002_TYPE	5000
#define DB_M56_VCAN2_MSG160_TYPE	5001
#define DB_M56_VCAN2_MSG174_TYPE	5002
#define DB_M56_VCAN2_MSG177_TYPE	5003
#define DB_M56_VCAN2_MSG180_TYPE	5004
#define DB_M56_VCAN2_MSG1c3_TYPE	5005
#define DB_M56_VCAN2_MSG239_TYPE	5006
#define DB_M56_VCAN2_MSG245_TYPE	5007
#define DB_M56_VCAN2_MSG284_TYPE	5008
#define DB_M56_VCAN2_MSG285_TYPE	5009
#define DB_M56_VCAN2_MSG292_TYPE	5010
#define DB_M56_VCAN2_MSG2aa_TYPE	5011
#define DB_M56_VCAN2_MSG2b0_TYPE	5012
#define DB_M56_VCAN2_MSG2b3_TYPE	5013
#define DB_M56_VCAN2_MSG354_TYPE	5014
#define DB_M56_VCAN2_MSG358_TYPE	5015
#define DB_M56_VCAN2_MSG421_TYPE	5016
#define DB_M56_VCAN2_MSG5b0_TYPE	5017
#define DB_M56_VCAN2_MSG625_TYPE	5018

#define DB_M56_ITSCAN_MSG52b_TYPE	5019
#define DB_M56_ITSCAN_MSG52c_TYPE	5020
#define DB_M56_ITSCAN_MSG52d_TYPE	5021
#define DB_M56_ITSCAN_MSG27A_TYPE	5022
#define DB_M56_IGNITION_TYPE		5023

#define DB_M56_VCAN2_MSG210_TYPE		5024
#define DB_M56_VCAN2_MSG211_TYPE		5025
#define DB_M56_VCAN2_MSG212_TYPE		5026
#define DB_M56_VCAN2_MSG213_TYPE		5027
#define DB_M56_VCAN2_MSG214_TYPE		5028
#define DB_M56_VCAN2_MSG215_TYPE		5029
#define DB_M56_VCAN2_MSG216_TYPE		5030
#define DB_M56_VCAN2_MSG217_TYPE		5031
#define DB_M56_VCAN2_MSG218_TYPE		5032
#define DB_M56_VCAN2_MSG219_TYPE		5033
#define DB_M56_VCAN2_MSG21a_TYPE		5034
#define DB_M56_VCAN2_MSG21b_TYPE		5035
#define DB_M56_VCAN2_MSG21c_TYPE		5036
#define DB_M56_VCAN2_MSG21d_TYPE		5037
#define DB_M56_VCAN2_MSG21e_TYPE		5038
#define DB_M56_VCAN2_MSG21f_TYPE		5039
#define DB_M56_VCAN2_MSG289_TYPE		5040
#define DB_M56_VCAN2_MSG28a_TYPE		5041

#define DB_M56_ITSCAN_MSG200_TYPE		5100
#define DB_M56_ITSCAN_MSG201_TYPE		5101
#define DB_M56_ITSCAN_MSG202_TYPE		5102
#define DB_M56_ITSCAN_MSG203_TYPE		5103
#define DB_M56_ITSCAN_MSG650_TYPE		5104
#define DB_M56_ITSCAN_MSG651_TYPE		5105
#define DB_M56_ITSCAN_MSG652_TYPE		5106
#define DB_M56_ITSCAN_MSG653_TYPE		5107
#define DB_M56_ITSCAN_MSG654_TYPE		5108
#define DB_M56_ITSCAN_MSG655_TYPE		5109
#define DB_M56_ITSCAN_MSG656_TYPE		5110
#define DB_M56_ITSCAN_MSG657_TYPE		5111
#define DB_M56_ITSCAN_MSG658_TYPE		5112
#define DB_M56_ITSCAN_MSG710_TYPE		5113
#define DB_M56_ITSCAN_MSG711_TYPE		5114

#define DB_M56_ITSCAN_MSG430_TYPE		5115
#define DB_M56_ITSCAN_MSG440_TYPE		5116
#define DB_M56_ITSCAN_MSG450_TYPE		5117
#define DB_M56_ITSCAN_MSG460_TYPE		5118
#define DB_M56_ITSCAN_MSG470_TYPE		5119

#define DB_M56_ITSCAN_MSG431_TYPE		5120
#define DB_M56_ITSCAN_MSG441_TYPE		5121
#define DB_M56_ITSCAN_MSG451_TYPE		5122
#define DB_M56_ITSCAN_MSG461_TYPE		5123
#define DB_M56_ITSCAN_MSG471_TYPE		5124

#define DB_M56_ITSCAN_MSG432_TYPE		5125
#define DB_M56_ITSCAN_MSG442_TYPE		5126
#define DB_M56_ITSCAN_MSG452_TYPE		5127
#define DB_M56_ITSCAN_MSG462_TYPE		5128
#define DB_M56_ITSCAN_MSG472_TYPE		5129

#define DB_M56_ITSCAN_MSG433_TYPE		5130
#define DB_M56_ITSCAN_MSG443_TYPE		5131
#define DB_M56_ITSCAN_MSG453_TYPE		5132
#define DB_M56_ITSCAN_MSG463_TYPE		5133
#define DB_M56_ITSCAN_MSG473_TYPE		5134

#define DB_M56_ITSCAN_MSG434_TYPE		5135
#define DB_M56_ITSCAN_MSG444_TYPE		5136
#define DB_M56_ITSCAN_MSG454_TYPE		5137
#define DB_M56_ITSCAN_MSG464_TYPE		5138
#define DB_M56_ITSCAN_MSG474_TYPE		5139

#define DB_M56_ITSCAN_MSG435_TYPE		5140
#define DB_M56_ITSCAN_MSG445_TYPE		5141
#define DB_M56_ITSCAN_MSG455_TYPE		5142
#define DB_M56_ITSCAN_MSG465_TYPE		5143
#define DB_M56_ITSCAN_MSG475_TYPE		5144

#define DB_M56_ITSCAN_MSG436_TYPE		5145
#define DB_M56_ITSCAN_MSG446_TYPE		5146
#define DB_M56_ITSCAN_MSG456_TYPE		5147
#define DB_M56_ITSCAN_MSG466_TYPE		5148
#define DB_M56_ITSCAN_MSG476_TYPE		5149

#define DB_M56_ITSCAN_MSG437_TYPE		5150
#define DB_M56_ITSCAN_MSG447_TYPE		5151
#define DB_M56_ITSCAN_MSG457_TYPE		5152
#define DB_M56_ITSCAN_MSG467_TYPE		5153
#define DB_M56_ITSCAN_MSG477_TYPE		5154

#define DB_M56_ITSCAN_MSG438_TYPE		5155
#define DB_M56_ITSCAN_MSG448_TYPE		5156
#define DB_M56_ITSCAN_MSG458_TYPE		5157
#define DB_M56_ITSCAN_MSG468_TYPE		5158
#define DB_M56_ITSCAN_MSG478_TYPE		5159

#define DB_M56_ITSCAN_MSG480_TYPE		5160
#define DB_M56_ITSCAN_MSG490_TYPE		5161
#define DB_M56_ITSCAN_MSG4A0_TYPE		5162
#define DB_M56_ITSCAN_MSG4B0_TYPE		5163
#define DB_M56_ITSCAN_MSG4C0_TYPE		5164

#define DB_M56_ITSCAN_MSG481_TYPE		5165
#define DB_M56_ITSCAN_MSG491_TYPE		5166
#define DB_M56_ITSCAN_MSG4A1_TYPE		5167
#define DB_M56_ITSCAN_MSG4B1_TYPE		5168
#define DB_M56_ITSCAN_MSG4C1_TYPE		5169

#define DB_M56_ITSCAN_MSG482_TYPE		5170
#define DB_M56_ITSCAN_MSG492_TYPE		5171
#define DB_M56_ITSCAN_MSG4A2_TYPE		5172
#define DB_M56_ITSCAN_MSG4B2_TYPE		5173
#define DB_M56_ITSCAN_MSG4C2_TYPE		5174

#define DB_M56_ITSCAN_MSG483_TYPE		5175
#define DB_M56_ITSCAN_MSG493_TYPE		5176
#define DB_M56_ITSCAN_MSG4A3_TYPE		5177
#define DB_M56_ITSCAN_MSG4B3_TYPE		5178
#define DB_M56_ITSCAN_MSG4C3_TYPE		5179

#define DB_M56_ITSCAN_MSG484_TYPE		5180
#define DB_M56_ITSCAN_MSG494_TYPE		5181
#define DB_M56_ITSCAN_MSG4A4_TYPE		5182
#define DB_M56_ITSCAN_MSG4B4_TYPE		5183
#define DB_M56_ITSCAN_MSG4C4_TYPE		5184

#define DB_M56_ITSCAN_MSG485_TYPE		5185
#define DB_M56_ITSCAN_MSG495_TYPE		5186
#define DB_M56_ITSCAN_MSG4A5_TYPE		5187
#define DB_M56_ITSCAN_MSG4B5_TYPE		5188
#define DB_M56_ITSCAN_MSG4C5_TYPE		5189

#define DB_M56_ITSCAN_MSG486_TYPE		5190
#define DB_M56_ITSCAN_MSG496_TYPE		5191
#define DB_M56_ITSCAN_MSG4A6_TYPE		5192
#define DB_M56_ITSCAN_MSG4B6_TYPE		5193
#define DB_M56_ITSCAN_MSG4C6_TYPE		5194

#define DB_M56_ITSCAN_MSG487_TYPE		5195
#define DB_M56_ITSCAN_MSG497_TYPE		5196
#define DB_M56_ITSCAN_MSG4A7_TYPE		5197
#define DB_M56_ITSCAN_MSG4B7_TYPE		5198
#define DB_M56_ITSCAN_MSG4C7_TYPE		5199

#define DB_M56_ITSCAN_MSG488_TYPE		5200
#define DB_M56_ITSCAN_MSG498_TYPE		5201
#define DB_M56_ITSCAN_MSG4A8_TYPE		5202
#define DB_M56_ITSCAN_MSG4B8_TYPE		5203
#define DB_M56_ITSCAN_MSG4C8_TYPE		5204

#define DB_M56_VCAN2_MSG002_VAR 	DB_M56_VCAN2_MSG002_TYPE
#define DB_M56_VCAN2_MSG160_VAR 	DB_M56_VCAN2_MSG160_TYPE
#define DB_M56_VCAN2_MSG174_VAR 	DB_M56_VCAN2_MSG174_TYPE
#define DB_M56_VCAN2_MSG177_VAR 	DB_M56_VCAN2_MSG177_TYPE
#define DB_M56_VCAN2_MSG180_VAR 	DB_M56_VCAN2_MSG180_TYPE
#define DB_M56_VCAN2_MSG1c3_VAR 	DB_M56_VCAN2_MSG1c3_TYPE
#define DB_M56_VCAN2_MSG239_VAR 	DB_M56_VCAN2_MSG239_TYPE
#define DB_M56_VCAN2_MSG245_VAR 	DB_M56_VCAN2_MSG245_TYPE
#define DB_M56_VCAN2_MSG284_VAR 	DB_M56_VCAN2_MSG284_TYPE
#define DB_M56_VCAN2_MSG285_VAR 	DB_M56_VCAN2_MSG285_TYPE
#define DB_M56_VCAN2_MSG292_VAR 	DB_M56_VCAN2_MSG292_TYPE
#define DB_M56_VCAN2_MSG2aa_VAR 	DB_M56_VCAN2_MSG2aa_TYPE
#define DB_M56_VCAN2_MSG2b0_VAR 	DB_M56_VCAN2_MSG2b0_TYPE
#define DB_M56_VCAN2_MSG2b3_VAR 	DB_M56_VCAN2_MSG2b3_TYPE
#define DB_M56_VCAN2_MSG354_VAR 	DB_M56_VCAN2_MSG354_TYPE
#define DB_M56_VCAN2_MSG358_VAR 	DB_M56_VCAN2_MSG358_TYPE
#define DB_M56_VCAN2_MSG421_VAR 	DB_M56_VCAN2_MSG421_TYPE
#define DB_M56_VCAN2_MSG5b0_VAR 	DB_M56_VCAN2_MSG5b0_TYPE
#define DB_M56_VCAN2_MSG625_VAR 	DB_M56_VCAN2_MSG625_TYPE

#define DB_M56_ITSCAN_MSG52b_VAR 	DB_M56_ITSCAN_MSG52b_TYPE
#define DB_M56_ITSCAN_MSG52c_VAR 	DB_M56_ITSCAN_MSG52c_TYPE
#define DB_M56_ITSCAN_MSG52d_VAR 	DB_M56_ITSCAN_MSG52d_TYPE
#define DB_M56_ITSCAN_MSG27A_VAR	DB_M56_ITSCAN_MSG27A_TYPE
#define DB_M56_IGNITION_VAR		DB_M56_IGNITION_TYPE

#define DB_M56_VCAN2_MSG210_VAR 	DB_M56_VCAN2_MSG210_TYPE
#define DB_M56_VCAN2_MSG211_VAR 	DB_M56_VCAN2_MSG211_TYPE
#define DB_M56_VCAN2_MSG212_VAR 	DB_M56_VCAN2_MSG212_TYPE
#define DB_M56_VCAN2_MSG213_VAR 	DB_M56_VCAN2_MSG213_TYPE
#define DB_M56_VCAN2_MSG214_VAR 	DB_M56_VCAN2_MSG214_TYPE
#define DB_M56_VCAN2_MSG215_VAR 	DB_M56_VCAN2_MSG215_TYPE
#define DB_M56_VCAN2_MSG216_VAR 	DB_M56_VCAN2_MSG216_TYPE
#define DB_M56_VCAN2_MSG217_VAR 	DB_M56_VCAN2_MSG217_TYPE
#define DB_M56_VCAN2_MSG218_VAR 	DB_M56_VCAN2_MSG218_TYPE
#define DB_M56_VCAN2_MSG219_VAR 	DB_M56_VCAN2_MSG219_TYPE
#define DB_M56_VCAN2_MSG21a_VAR 	DB_M56_VCAN2_MSG21a_TYPE
#define DB_M56_VCAN2_MSG21b_VAR 	DB_M56_VCAN2_MSG21b_TYPE
#define DB_M56_VCAN2_MSG21c_VAR 	DB_M56_VCAN2_MSG21c_TYPE
#define DB_M56_VCAN2_MSG21d_VAR 	DB_M56_VCAN2_MSG21d_TYPE
#define DB_M56_VCAN2_MSG21e_VAR 	DB_M56_VCAN2_MSG21e_TYPE
#define DB_M56_VCAN2_MSG21f_VAR 	DB_M56_VCAN2_MSG21f_TYPE
#define DB_M56_VCAN2_MSG289_VAR 	DB_M56_VCAN2_MSG289_TYPE
#define DB_M56_VCAN2_MSG28a_VAR 	DB_M56_VCAN2_MSG28a_TYPE

#define DB_M56_ITSCAN_MSG200_VAR 	DB_M56_ITSCAN_MSG200_TYPE
#define DB_M56_ITSCAN_MSG201_VAR 	DB_M56_ITSCAN_MSG201_TYPE
#define DB_M56_ITSCAN_MSG202_VAR 	DB_M56_ITSCAN_MSG202_TYPE
#define DB_M56_ITSCAN_MSG203_VAR 	DB_M56_ITSCAN_MSG203_TYPE
#define DB_M56_ITSCAN_MSG650_VAR 	DB_M56_ITSCAN_MSG650_TYPE

#define DB_M56_ITSCAN_MSG651_VAR 	DB_M56_ITSCAN_MSG651_TYPE
#define DB_M56_ITSCAN_MSG652_VAR 	DB_M56_ITSCAN_MSG652_TYPE
#define DB_M56_ITSCAN_MSG653_VAR 	DB_M56_ITSCAN_MSG653_TYPE
#define DB_M56_ITSCAN_MSG654_VAR 	DB_M56_ITSCAN_MSG654_TYPE
#define DB_M56_ITSCAN_MSG655_VAR 	DB_M56_ITSCAN_MSG655_TYPE

#define DB_M56_ITSCAN_MSG656_VAR 	DB_M56_ITSCAN_MSG656_TYPE
#define DB_M56_ITSCAN_MSG657_VAR 	DB_M56_ITSCAN_MSG657_TYPE
#define DB_M56_ITSCAN_MSG658_VAR 	DB_M56_ITSCAN_MSG658_TYPE
#define DB_M56_ITSCAN_MSG710_VAR 	DB_M56_ITSCAN_MSG710_TYPE
#define DB_M56_ITSCAN_MSG711_VAR 	DB_M56_ITSCAN_MSG711_TYPE

#define DB_M56_ITSCAN_MSG430_VAR 	DB_M56_ITSCAN_MSG430_TYPE
#define DB_M56_ITSCAN_MSG440_VAR 	DB_M56_ITSCAN_MSG440_TYPE
#define DB_M56_ITSCAN_MSG450_VAR 	DB_M56_ITSCAN_MSG450_TYPE
#define DB_M56_ITSCAN_MSG460_VAR 	DB_M56_ITSCAN_MSG460_TYPE
#define DB_M56_ITSCAN_MSG470_VAR 	DB_M56_ITSCAN_MSG470_TYPE

#define DB_M56_ITSCAN_MSG431_VAR 	DB_M56_ITSCAN_MSG431_TYPE
#define DB_M56_ITSCAN_MSG441_VAR 	DB_M56_ITSCAN_MSG441_TYPE
#define DB_M56_ITSCAN_MSG451_VAR 	DB_M56_ITSCAN_MSG451_TYPE
#define DB_M56_ITSCAN_MSG461_VAR 	DB_M56_ITSCAN_MSG461_TYPE
#define DB_M56_ITSCAN_MSG471_VAR 	DB_M56_ITSCAN_MSG471_TYPE

#define DB_M56_ITSCAN_MSG432_VAR 	DB_M56_ITSCAN_MSG432_TYPE
#define DB_M56_ITSCAN_MSG442_VAR 	DB_M56_ITSCAN_MSG442_TYPE
#define DB_M56_ITSCAN_MSG452_VAR 	DB_M56_ITSCAN_MSG452_TYPE
#define DB_M56_ITSCAN_MSG462_VAR 	DB_M56_ITSCAN_MSG462_TYPE
#define DB_M56_ITSCAN_MSG472_VAR 	DB_M56_ITSCAN_MSG472_TYPE

#define DB_M56_ITSCAN_MSG433_VAR 	DB_M56_ITSCAN_MSG433_TYPE
#define DB_M56_ITSCAN_MSG443_VAR 	DB_M56_ITSCAN_MSG443_TYPE
#define DB_M56_ITSCAN_MSG453_VAR 	DB_M56_ITSCAN_MSG453_TYPE
#define DB_M56_ITSCAN_MSG463_VAR 	DB_M56_ITSCAN_MSG463_TYPE
#define DB_M56_ITSCAN_MSG473_VAR 	DB_M56_ITSCAN_MSG473_TYPE

#define DB_M56_ITSCAN_MSG434_VAR 	DB_M56_ITSCAN_MSG434_TYPE
#define DB_M56_ITSCAN_MSG444_VAR 	DB_M56_ITSCAN_MSG444_TYPE
#define DB_M56_ITSCAN_MSG454_VAR 	DB_M56_ITSCAN_MSG454_TYPE
#define DB_M56_ITSCAN_MSG464_VAR 	DB_M56_ITSCAN_MSG464_TYPE
#define DB_M56_ITSCAN_MSG474_VAR 	DB_M56_ITSCAN_MSG474_TYPE

#define DB_M56_ITSCAN_MSG435_VAR 	DB_M56_ITSCAN_MSG435_TYPE
#define DB_M56_ITSCAN_MSG445_VAR 	DB_M56_ITSCAN_MSG445_TYPE
#define DB_M56_ITSCAN_MSG455_VAR 	DB_M56_ITSCAN_MSG455_TYPE
#define DB_M56_ITSCAN_MSG465_VAR 	DB_M56_ITSCAN_MSG465_TYPE
#define DB_M56_ITSCAN_MSG475_VAR 	DB_M56_ITSCAN_MSG475_TYPE

#define DB_M56_ITSCAN_MSG436_VAR 	DB_M56_ITSCAN_MSG436_TYPE
#define DB_M56_ITSCAN_MSG446_VAR 	DB_M56_ITSCAN_MSG446_TYPE
#define DB_M56_ITSCAN_MSG456_VAR 	DB_M56_ITSCAN_MSG456_TYPE
#define DB_M56_ITSCAN_MSG466_VAR 	DB_M56_ITSCAN_MSG466_TYPE
#define DB_M56_ITSCAN_MSG476_VAR 	DB_M56_ITSCAN_MSG476_TYPE

#define DB_M56_ITSCAN_MSG437_VAR 	DB_M56_ITSCAN_MSG437_TYPE
#define DB_M56_ITSCAN_MSG447_VAR 	DB_M56_ITSCAN_MSG447_TYPE
#define DB_M56_ITSCAN_MSG457_VAR 	DB_M56_ITSCAN_MSG457_TYPE
#define DB_M56_ITSCAN_MSG467_VAR 	DB_M56_ITSCAN_MSG467_TYPE
#define DB_M56_ITSCAN_MSG477_VAR 	DB_M56_ITSCAN_MSG477_TYPE

#define DB_M56_ITSCAN_MSG438_VAR 	DB_M56_ITSCAN_MSG438_TYPE
#define DB_M56_ITSCAN_MSG448_VAR 	DB_M56_ITSCAN_MSG448_TYPE
#define DB_M56_ITSCAN_MSG458_VAR 	DB_M56_ITSCAN_MSG458_TYPE
#define DB_M56_ITSCAN_MSG468_VAR 	DB_M56_ITSCAN_MSG468_TYPE
#define DB_M56_ITSCAN_MSG478_VAR 	DB_M56_ITSCAN_MSG478_TYPE

#define DB_M56_ITSCAN_MSG480_VAR 	DB_M56_ITSCAN_MSG480_TYPE
#define DB_M56_ITSCAN_MSG490_VAR 	DB_M56_ITSCAN_MSG490_TYPE
#define DB_M56_ITSCAN_MSG4A0_VAR 	DB_M56_ITSCAN_MSG4A0_TYPE
#define DB_M56_ITSCAN_MSG4B0_VAR 	DB_M56_ITSCAN_MSG4B0_TYPE
#define DB_M56_ITSCAN_MSG4C0_VAR 	DB_M56_ITSCAN_MSG4C0_TYPE

#define DB_M56_ITSCAN_MSG481_VAR 	DB_M56_ITSCAN_MSG481_TYPE
#define DB_M56_ITSCAN_MSG491_VAR 	DB_M56_ITSCAN_MSG491_TYPE
#define DB_M56_ITSCAN_MSG4A1_VAR 	DB_M56_ITSCAN_MSG4A1_TYPE
#define DB_M56_ITSCAN_MSG4B1_VAR 	DB_M56_ITSCAN_MSG4B1_TYPE
#define DB_M56_ITSCAN_MSG4C1_VAR 	DB_M56_ITSCAN_MSG4C1_TYPE

#define DB_M56_ITSCAN_MSG482_VAR 	DB_M56_ITSCAN_MSG482_TYPE
#define DB_M56_ITSCAN_MSG492_VAR 	DB_M56_ITSCAN_MSG492_TYPE
#define DB_M56_ITSCAN_MSG4A2_VAR 	DB_M56_ITSCAN_MSG4A2_TYPE
#define DB_M56_ITSCAN_MSG4B2_VAR 	DB_M56_ITSCAN_MSG4B2_TYPE
#define DB_M56_ITSCAN_MSG4C2_VAR 	DB_M56_ITSCAN_MSG4C2_TYPE

#define DB_M56_ITSCAN_MSG483_VAR 	DB_M56_ITSCAN_MSG483_TYPE
#define DB_M56_ITSCAN_MSG493_VAR 	DB_M56_ITSCAN_MSG493_TYPE
#define DB_M56_ITSCAN_MSG4A3_VAR 	DB_M56_ITSCAN_MSG4A3_TYPE
#define DB_M56_ITSCAN_MSG4B3_VAR 	DB_M56_ITSCAN_MSG4B3_TYPE
#define DB_M56_ITSCAN_MSG4C3_VAR 	DB_M56_ITSCAN_MSG4C3_TYPE

#define DB_M56_ITSCAN_MSG484_VAR 	DB_M56_ITSCAN_MSG484_TYPE
#define DB_M56_ITSCAN_MSG494_VAR 	DB_M56_ITSCAN_MSG494_TYPE
#define DB_M56_ITSCAN_MSG4A4_VAR 	DB_M56_ITSCAN_MSG4A4_TYPE
#define DB_M56_ITSCAN_MSG4B4_VAR 	DB_M56_ITSCAN_MSG4B4_TYPE
#define DB_M56_ITSCAN_MSG4C4_VAR 	DB_M56_ITSCAN_MSG4C4_TYPE

#define DB_M56_ITSCAN_MSG485_VAR 	DB_M56_ITSCAN_MSG485_TYPE
#define DB_M56_ITSCAN_MSG495_VAR 	DB_M56_ITSCAN_MSG495_TYPE
#define DB_M56_ITSCAN_MSG4A5_VAR 	DB_M56_ITSCAN_MSG4A5_TYPE
#define DB_M56_ITSCAN_MSG4B5_VAR 	DB_M56_ITSCAN_MSG4B5_TYPE
#define DB_M56_ITSCAN_MSG4C5_VAR 	DB_M56_ITSCAN_MSG4C5_TYPE

#define DB_M56_ITSCAN_MSG486_VAR 	DB_M56_ITSCAN_MSG486_TYPE
#define DB_M56_ITSCAN_MSG496_VAR 	DB_M56_ITSCAN_MSG496_TYPE
#define DB_M56_ITSCAN_MSG4A6_VAR 	DB_M56_ITSCAN_MSG4A6_TYPE
#define DB_M56_ITSCAN_MSG4B6_VAR 	DB_M56_ITSCAN_MSG4B6_TYPE
#define DB_M56_ITSCAN_MSG4C6_VAR 	DB_M56_ITSCAN_MSG4C6_TYPE

#define DB_M56_ITSCAN_MSG487_VAR 	DB_M56_ITSCAN_MSG487_TYPE
#define DB_M56_ITSCAN_MSG497_VAR 	DB_M56_ITSCAN_MSG497_TYPE
#define DB_M56_ITSCAN_MSG4A7_VAR 	DB_M56_ITSCAN_MSG4A7_TYPE
#define DB_M56_ITSCAN_MSG4B7_VAR 	DB_M56_ITSCAN_MSG4B7_TYPE
#define DB_M56_ITSCAN_MSG4C7_VAR 	DB_M56_ITSCAN_MSG4C7_TYPE

#define DB_M56_ITSCAN_MSG488_VAR 	DB_M56_ITSCAN_MSG488_TYPE
#define DB_M56_ITSCAN_MSG498_VAR 	DB_M56_ITSCAN_MSG498_TYPE
#define DB_M56_ITSCAN_MSG4A8_VAR 	DB_M56_ITSCAN_MSG4A8_TYPE
#define DB_M56_ITSCAN_MSG4B8_VAR 	DB_M56_ITSCAN_MSG4B8_TYPE
#define DB_M56_ITSCAN_MSG4C8_VAR 	DB_M56_ITSCAN_MSG4C8_TYPE

#define MASK_b0	 0x01
#define MASK_b01 0x03
#define MASK_b02 0x07
#define MASK_b03 0x0F
#define MASK_b04 0x1F
#define MASK_b07 0xFF
#define MASK_b1	 0x02
#define MASK_b12 0x06
#define MASK_b2	 0x04
#define MASK_b23 0x0C
#define MASK_b3	 0x08
#define MASK_b34 0x18
#define MASK_b4	 0x10
#define MASK_b45 0x30
#define MASK_b47 0xF0
#define MASK_b5	 0x20
#define MASK_b6	 0x40
#define MASK_b67 0xC0
#define MASK_b7	 0x80
#define M56_IGNITION_MASK 0X01

/*******************************************************************************
 *      m56_steering
 *      Message ID      0x002
 *      Transmitted every 10 ms
 *
 *	steering_angle
 *      Byte Position   0-1
 *      Bit Position    0-15
 *      Bit Length      16
 *
 *	steering_velocity
 *      Byte Position   2-3
 *      Bit Position    0-7
 *      Bit Length      8
 *
 *	message_counter
 *      Byte Position   4
 *      Bit Position    3
 *      Bit Length      4
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float steering_angle;
	float steering_velocity;
	unsigned char message_counter;
} m56_steering_t;

static inline void get_m56_steering(unsigned char *data, m56_steering_t *p) {
	p->steering_angle = ((signed short)((data[0] + (data[1] << 8)))) * 
		steering_angle_res;
	p->steering_velocity = ((unsigned char)data[2]) * steering_velocity_res;
	p->message_counter = data[4] & MASK_b03;
}

/*******************************************************************************
 *      m56_gear
 *      Message ID      0x174
 *      Transmitted every 10 ms
 *
 *	current_gear
 *      Byte Position   3
 *      Bit Position    0-3
 *      Bit Length      4
 *
 *	next_gear
 *      Byte Position   3
 *      Bit Position    4-7
 *      Bit Length      4
 *
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char current_gear;
	unsigned char next_gear;
} m56_gear_t;

static inline void get_m56_gear(unsigned char *data, m56_gear_t *p) {
	p->current_gear = data[3] & MASK_b03;
	p->next_gear = (data[3] & MASK_b47) >> 4;
}

/*******************************************************************************
 *      m56_engine_rpm
 *      Message ID      0x180
 *      Transmitted every 10 ms
 *
 *	engine_rpm
 *      Byte Position   0-1
 *      Bit Position    0-15
 *      Bit Length      16
 *
 *	mean_effective_torque
 *      Byte Position   2-3
 *      Bit Position    0-11
 *      Bit Length      12
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float engine_rpm;
	float mean_effective_torque;
} m56_engine_rpm_t;

static inline void get_m56_engine_rpm(unsigned char *data, m56_engine_rpm_t *p) {
	p->engine_rpm = ((signed short)((data[0] << 8) + data[1])) * rpm_res;
	p->mean_effective_torque = (((unsigned short)(((data[2] << 4) + ((data[3]& MASK_b47) >> 4)))) * mean_eff_tq_res) - mean_eff_tq_off;
}

/*******************************************************************************
 *      m56_its_alive
 *      Message ID      0x1c3
 *      Transmitted every 10 ms
 *
 *	its_target_pressure
 *      Byte Position   0-1
 *      Bit Position    0-15
 *      Bit Length      16
 *
 *	its_alive_flag
 *      Byte Position   1
 *      Bit Position    4
 *      Bit Length      1
 *
 *	acc_request_flag
 *      Byte Position   1
 *      Bit Position    3
 *      Bit Length      1
 *
 *	message_counter
 *      Byte Position   5
 *      Bit Position    1
 *      Bit Length      2
 *
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float its_target_pressure;
	unsigned char its_alive_flag;
	unsigned char acc_request_flag;
	unsigned char message_counter;
} m56_its_alive_t;

static inline void get_m56_its_alive(unsigned char *data, m56_its_alive_t *p) {
        p->its_target_pressure = ((unsigned short)((data[0] << 3) + (data[1] * MASK_b02))) * its_target_pressure_res;
        p->its_alive_flag = (data[1] & MASK_b4) >> 4;
        p->acc_request_flag = (data[1] & MASK_b3) >> 3;
        p->message_counter = data[5] & MASK_b01;
}

/*******************************************************************************
 *      m56_pedal_position
 *      Message ID      0x239
 *      Transmitted every 20 ms
 *
 *	acc_inhibit
 *      Byte Position   2
 *      Bit Position    7
 *      Bit Length      1
 *
 *	acc_control_requested
 *      Byte Position   2
 *      Bit Position    5
 *      Bit Length      1
 *
 *	temporary_accel_flag
 *      Byte Position   2
 *      Bit Position    2
 *      Bit Length      1
 *
 *	resume_sw
 *      Byte Position   3
 *      Bit Position    4
 *      Bit Length      1
 *
 *	acc_set_sw
 *      Byte Position   3
 *      Bit Position    3
 *      Bit Length      1
 *
 *	following_dist_sw	
 *      Byte Position   3
 *      Bit Position    2
 *      Bit Length      1
 *
 *	cancel_sw
 *      Byte Position   3
 *      Bit Position    1
 *      Bit Length      1
 *
 *	main_sw
 *      Byte Position   3
 *      Bit Position    0
 *      Bit Length      1
 *
 *	acc_can_fail_flag
 *      Byte Position   4
 *      Bit Position    7
 *      Bit Length      1
 *
 *	brake_nc_sw
 *      Byte Position   4
 *      Bit Position    6
 *      Bit Length      1
 *
 *	brake_no_sw
 *      Byte Position   4
 *      Bit Position    5
 *      Bit Length      1
 *
 *	message_counter
 *      Byte Position   4
 *      Bit Position    1
 *      Bit Length      2
 *
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float pedal_position;
	unsigned char acc_inhibit;
	unsigned char acc_control_requested;
	unsigned char temporary_accel_flag;
	unsigned char resume_sw;
	unsigned char acc_set_sw;
	unsigned char following_dist_sw;
	unsigned char cancel_sw;
	unsigned char main_sw;
	unsigned char acc_can_fail_flag;
	unsigned char brake_nc_sw;
	unsigned char brake_no_sw;
	unsigned char message_counter;
} m56_pedal_position_t;

static inline void get_m56_pedal_position(unsigned char *data, m56_pedal_position_t *p) {
	p->pedal_position = (unsigned char)data[0] * pedal_pos_res;
	p->acc_inhibit = (data[2] & MASK_b7) >> 7;
	p->acc_control_requested = (data[2] & MASK_b5) >> 5;
	p->temporary_accel_flag = (data[2] & MASK_b2) >> 2;
	p->resume_sw = (data[3] & MASK_b4) >> 4;
	p->acc_set_sw = (data[3] & MASK_b3) >> 3;
	p->following_dist_sw = (data[3] & MASK_b2) >> 2;
	p->cancel_sw = (data[3] & MASK_b1) >> 1;
	p->main_sw = data[3] & MASK_b0;
	p->acc_can_fail_flag = (data[4] & MASK_b7) >> 7;
	p->brake_nc_sw = (data[4] & MASK_b6) >> 6;
	p->brake_no_sw = (data[4] & MASK_b5) >> 5;
	p->message_counter = data[4] & MASK_b01;
}

/*******************************************************************************
 *      m56_wheel_speed_front
 *      Message ID      0x284
 *      Transmitted every 20 ms
 *
 *      wheel_speed_front_right
 *      Byte Position   0-1
 *      Bit Position    0-15
 *      Bit Length      16
 *
 *      wheel_speed_front_left
 *      Byte Position   2-3
 *      Bit Position    0-15
 *      Bit Length      16
 *
 *      vehicle_speed_copy
 *      Byte Position   4-5
 *      Bit Position    0-15
 *      Bit Length      16
 *
 *      message_counter
 *      Byte Position   6
 *      Bit Position    7
 *      Bit Length      8
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float wheel_speed_front_right;
	float wheel_speed_front_left;
	float vehicle_speed_copy;
	unsigned char message_counter;
} m56_wheel_speed_front_t;

static inline void get_m56_wheel_speed_front(unsigned char *data, m56_wheel_speed_front_t *p) {
	p->wheel_speed_front_right = ((unsigned short)(((data[0] << 8) + data[1]))) * wheel_speed_res;
	p->wheel_speed_front_left = ((unsigned short)(((data[2] << 8) + data[3]))) * wheel_speed_res;
	p->vehicle_speed_copy = ((unsigned short)(((data[4] << 8) + data[5]))) * vehicle_speed_res;
	p->message_counter = data[6];
}

/*******************************************************************************
 *      m56_wheel_speed_rear
 *      Message ID      0x285
 *      Transmitted every 20 ms
 *
 *      wheel_speed_front_right
 *      Byte Position   0-1
 *      Bit Position    0-15
 *      Bit Length      16
 *
 *      wheel_speed_front_left
 *      Byte Position   2-3
 *      Bit Position    0-15
 *      Bit Length      16
 *
 *      message_counter
 *      Byte Position   6
 *      Bit Position    7
 *      Bit Length      8
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float wheel_speed_rear_right;
	float wheel_speed_rear_left;
	unsigned char message_counter;
} m56_wheel_speed_rear_t;

static inline void get_m56_wheel_speed_rear(unsigned char *data, m56_wheel_speed_rear_t *p) {
	p->wheel_speed_rear_right = ((unsigned short)((data[0] << 8) + data[1])) * wheel_speed_res;
	p->wheel_speed_rear_left = ((unsigned short)((data[2] << 8) + data[3])) * wheel_speed_res;
	p->message_counter = data[6];
}

/*******************************************************************************
 *      m56_acceleration
 *      Message ID      0x292
 *      Transmitted every 20 ms
 *
 *      long_accel_proc_02
 *      Byte Position   0
 *      Bit Position    0-7
 *      Byte Position   1
 *      Bit Position    4-7
 *      Bit Length      12
 *
 *      transverse_accel_proc_02
 *      Byte Position   1
 *      Bit Position    0-3
 *      Byte Position   2
 *      Bit Position    0-7
 *      Bit Length      12
 *
 *      yaw_rate_02
 *      Byte Position   3
 *      Bit Position    0-7
 *      Byte Position   4
 *      Bit Position    4-7
 *      Bit Length      12
 *
 *      message_counter
 *      Byte Position   7
 *      Bit Position    1
 *      Bit Length      2
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float long_accel_proc_02;
	float transverse_accel_proc_02;
	float yaw_rate_02;
	unsigned char pressure_sensor_02;
	unsigned char message_counter;
} m56_acceleration_t;

static inline void get_m56_acceleration(unsigned char *data, m56_acceleration_t *p) {
	p->long_accel_proc_02 = (((unsigned short)((data[0] << 4) + (data[1] >> 4))) * acceleration_res) + acceleration_offset;
	p->transverse_accel_proc_02 = (((unsigned short)(((data[1] & MASK_b03) << 8) + data[2])) * acceleration_res) + acceleration_offset;
	p->yaw_rate_02 = (((unsigned short)((data[3] << 4) + (data[4] >> 4))) * yaw_rate_res) + yaw_rate_offset;
	p->pressure_sensor_02 = data[6];
	p->message_counter = data[7] & MASK_b01;
}

/*******************************************************************************
 *      m56_acc_status
 *      Message ID      0x2aa
 *      Transmitted every 20 ms
 *
 *	estimated_pressure_value
 *      Byte Position   0
 *      Bit Position    7
 *      Bit Length      8
 *
 *	release_sw
 *      Byte Position   1
 *      Bit Position    4
 *      Bit Length      1
 *
 *	pbfs_nc
 *      Byte Position   1
 *      Bit Position    3
 *      Bit Length      1
 *
 *	pbfs_no
 *      Byte Position   1
 *      Bit Position    2
 *      Bit Length      1
 *
 *	acc_enable
 *      Byte Position   1
 *      Bit Position    1
 *      Bit Length      1
 *
 *	acc_status
 *      Byte Position   2
 *      Bit Position    5
 *      Bit Length      1
 *
 *	acc_alive
 *      Byte Position   2
 *      Bit Position    1
 *      Bit Length      1
 *
 *	message_counter
 *      Byte Position   6
 *      Bit Position    3
 *      Bit Length      4
 *
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float estimated_pressure_value;
	unsigned char release_sw;
	unsigned char pbfs_nc;
	unsigned char pbfs_no;
	unsigned char acc_enable;
	unsigned char acc_status;
	unsigned char acc_alive;
	unsigned char message_counter;
} m56_acc_status_t;

static inline void get_m56_acc_status(unsigned char *data, m56_acc_status_t *p) {
        p->estimated_pressure_value = ((unsigned short)(((data[0] << 3) + (data[1] & MASK_b02)))) * estimated_pressure_res;
        p->release_sw = (data[1] & MASK_b4) >> 4;
        p->pbfs_nc = (data[1] & MASK_b3) >> 3;
        p->pbfs_no = (data[1] & MASK_b2) >> 2;
        p->acc_enable = (data[1] & MASK_b1) >> 1;
        p->acc_status = (data[2] & MASK_b5) >> 5;
        p->acc_alive = (data[2] & MASK_b1) >> 1;
        p->message_counter = data[6] & MASK_b03;
}

/*******************************************************************************
 *      m56_eng_tq_acc_and_brake_flags
 *      Message ID      0x2b0
 *      Transmitted every 10 ms
 *
 *	target_engine_torque_main_cpu
 *      Byte Position   0-1
 *      Bit Position    0-7,0-3
 *      Bit Length      12
 *
 *	target_engine_torque_sub_cpu
 *      Byte Position   1-2
 *      Bit Position    4-7,0-7
 *      Bit Length      12
 *
 *	driver_brake_nc
 *      Byte Position   3
 *      Bit Position    7
 *      Bit Length      1
 *
 *	driver_brake_no
 *      Byte Position   3
 *      Bit Position    6
 *      Bit Length      1
 *
 *	acc_main_sw
 *      Byte Position   3
 *      Bit Position    5
 *      Bit Length      1
 *
 *	od_off_flag
 *      Byte Position   3
 *      Bit Position    1
 *      Bit Length      1
 *
 *	acc_fail_flag
 *      Byte Position   3
 *      Bit Position    0
 *      Bit Length      1
 *
 *	control_autostop_flag
 *      Byte Position   4
 *      Bit Position    7
 *      Bit Length      1
 *
 *	acc_active_flag_for_ecm
 *      Byte Position   4
 *      Bit Position    6
 *      Bit Length      1
 *
 *	acc_cruise_flag
 *      Byte Position   4
 *      Bit Position    5
 *      Bit Length      1
 *
 *	virtual_accelerator_angle
 *      Byte Position   5
 *      Bit Position    0-7
 *      Bit Length      8
 *
 *	message_counter
 *      Byte Position   6
 *      Bit Position    4-7
 *      Bit Length      4
 *
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float target_engine_torque_main_cpu;
	float target_engine_torque_sub_cpu;
	unsigned char driver_brake_nc;
	unsigned char driver_brake_no;
	unsigned char acc_main_sw;
	unsigned char od_off_flag;
	unsigned char acc_fail_flag;
	unsigned char control_autostop_flag;
	unsigned char acc_active_flag_for_ecm;
	unsigned char acc_cruise_flag;
	float virtual_accelerator_angle;
	unsigned char message_counter;
} m56_eng_tq_acc_and_brake_flags_t;

static inline void get_m56_eng_tq_acc_and_brake_flags(unsigned char *data, 
	m56_eng_tq_acc_and_brake_flags_t *p) {

        p->target_engine_torque_main_cpu = 
		((signed short)((data[0] + ((data[1] & MASK_b47) << 4)))) * 
			targ_eng_tq_res;
        p->target_engine_torque_sub_cpu = 
		((signed short)((data[1] & MASK_b03) + (data[2] << 4))) * 
			targ_eng_tq_res;
        p->driver_brake_nc = (data[3] & MASK_b7) >> 7;
        p->driver_brake_no = (data[3] & MASK_b6) >> 6;
        p->acc_main_sw = (data[3] & MASK_b5) >> 5;
        p->od_off_flag = (data[3] & MASK_b1) >> 1;
        p->acc_fail_flag = data[3] & MASK_b0;
        p->control_autostop_flag = (data[4] & MASK_b7) >> 7;
        p->acc_active_flag_for_ecm = (data[4] & MASK_b6) >> 6;
        p->acc_cruise_flag = (data[4] & MASK_b5) >> 5;
        p->virtual_accelerator_angle = ((unsigned char)(data[5])) * virtual_accelerator_angle_res;
        p->message_counter = (data[6] & MASK_b47) >> 4;
}


/*******************************************************************************
 *      m56_dashboard_indicators
 *      Message ID      0x2b3
 *      Transmitted every 20 ms
 *
 *	main_sw
 *      Byte Position   0
 *      Bit Position    7
 *      Bit Length      1
 *
 *	target_lock
 *      Byte Position   0
 *      Bit Position    5
 *      Bit Length      1
 *
 *	target_approach_warning
 *      Byte Position   0
 *      Bit Position    4
 *      Bit Length      2
 *
 *	blink_at_target_icon
 *      Byte Position   0
 *      Bit Position    2
 *      Bit Length      1
 *
 *	segment_car_space
 *      Byte Position   0
 *      Bit Position    1
 *      Bit Length      2
 *
 *	oneself
 *      Byte Position   1
 *      Bit Position    7
 *      Bit Length      1
 *
 *	auto_brake
 *      Byte Position   1
 *      Bit Position    6
 *      Bit Length      1
 *
 *	dash_dash_indicator_signal
 *      Byte Position   1
 *      Bit Position    5
 *      Bit Length      1
 *
 *	kph_indicator_signal
 *      Byte Position   1
 *      Bit Position    4
 *      Bit Length      1
 *
 *	acc_buzzer_signal
 *      Byte Position   1
 *      Bit Position    1
 *      Bit Length      1
 *
 *	pbs2_warning
 *      Byte Position   1
 *      Bit Position    0
 *      Bit Length      1
 *
 *	speed_set_driver
 *      Byte Position   2
 *      Bit Position    7
 *      Bit Length      8
 *
 *	acc_buzzer_3rd
 *      Byte Position   3
 *      Bit Position    6
 *      Bit Length      1
 *
 *	acc_buzzer_2nd
 *      Byte Position   3
 *      Bit Position    5
 *      Bit Length      1
 *
 *	booster_active_reverse_bit
 *      Byte Position   3
 *      Bit Position    3
 *      Bit Length      1
 *
 *	booster_active
 *      Byte Position   3
 *      Bit Position    2
 *      Bit Length      1
 *
 *	pbs2_off
 *      Byte Position   3
 *      Bit Position    1
 *      Bit Length      1
 *
 *	acc_bulb_check
 *      Byte Position   3
 *      Bit Position    0
 *      Bit Length      1
 *
 *	acc_system_fail_1_invert
 *      Byte Position   4
 *      Bit Position    7
 *      Bit Length      1
 *
 *	acc_system_fail_1
 *      Byte Position   4
 *      Bit Position    6
 *      Bit Length      1
 *
 *	trouble_trigger_code
 *      Byte Position   5
 *      Bit Position    7
 *      Bit Length      8
 *
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char main_sw;
	unsigned char target_lock;
	unsigned char target_approach_warning;
	unsigned char blink_at_target_icon;
	unsigned char segment_car_space;
	unsigned char oneself;
	unsigned char auto_brake;
	unsigned char dash_dash_indicator_signal;
	unsigned char kph_indicator_signal;
	unsigned char acc_buzzer_signal;
	unsigned char pbs2_warning;
	unsigned char speed_set_driver;
	unsigned char acc_buzzer_3rd;
	unsigned char acc_buzzer_2nd;
	unsigned char booster_active_reverse_bit;
	unsigned char booster_active;
	unsigned char pbs2_off;
	unsigned char acc_bulb_check;
	unsigned char acc_system_fail_1_invert;
	unsigned char acc_system_fail_1;
	unsigned char trouble_trigger_code;
} m56_dashboard_indicators_t;

static inline void get_m56_dashboard_indicators(unsigned char *data, 
	m56_dashboard_indicators_t *p) {

        p->main_sw = (data[0] & MASK_b7) >> 7;
        p->target_lock = (data[0] & MASK_b5) >> 5;
        p->target_approach_warning = (data[0] & MASK_b34) >> 3;
        p->blink_at_target_icon = (data[0] & MASK_b2) >> 2;
        p->segment_car_space = data[0] & MASK_b01;
        p->oneself = (data[1] & MASK_b7) >> 7;
        p->auto_brake = (data[1] & MASK_b6) >> 6;
        p->dash_dash_indicator_signal = (data[1] & MASK_b5) >> 5;
        p->kph_indicator_signal = (data[1] & MASK_b4) >> 4;
        p->acc_buzzer_signal = (data[1] & MASK_b1) >> 1;
        p->pbs2_warning = data[1] & MASK_b0;
        p->speed_set_driver = data[2];
        p->acc_buzzer_3rd = (data[3] & MASK_b6) >> 6;
        p->acc_buzzer_2nd = (data[3] & MASK_b5) >> 5;
        p->booster_active_reverse_bit = (data[3] & MASK_b3) >> 3;
        p->booster_active = (data[3] & MASK_b2) >> 2;
        p->pbs2_off = (data[3] & MASK_b1) >> 1;
        p->acc_bulb_check = data[3] & MASK_b0;
        p->acc_system_fail_1_invert = (data[4] & MASK_b7) >> 7;
        p->acc_system_fail_1 = (data[4] & MASK_b6) >> 6;
        p->trouble_trigger_code = data[5];
}

/*******************************************************************************
 *      m56_abs_status
 *      Message ID      0x354
 *      Transmitted every 40 ms
 *
 *      message_counter
 *      Byte Position   5
 *      Bit Position    4
 *      Bit Length      2
 *
 *      abs_malfunction
 *      Byte Position   6
 *      Bit Position    7
 *      Bit Length      1
 *
 *      abs_in_regulation
 *      Byte Position   6
 *      Bit Position    6
 *      Bit Length      1
 *
 *      close_active_brake_switch_abs
 *      Byte Position   6
 *      Bit Position    5
 *      Bit Length      1
 *
*/

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
        unsigned char message_counter;
        unsigned char abs_malfunction;
        unsigned char abs_in_regulation;
        unsigned char close_active_brake_switch_abs;
} m56_abs_status_t;


static inline void get_m56_abs_status(unsigned char *data, 
	m56_abs_status_t *p) {

        p->message_counter = (data[5] & MASK_b34) >> 3;
        p->abs_malfunction = (data[6] & MASK_b7) >> 7;
        p->abs_in_regulation = (data[6] & MASK_b6) >> 6;
        p->close_active_brake_switch_abs = (data[6] & MASK_b45) >> 4;
}

/*******************************************************************************
 *      m56_turn_switch_status 
 *      Message ID      0x358
 *      Transmitted every 100 ms + event
 *
 *      turn_switch_status
 *      Byte Position   2
 *      Bit Position    2
 *      Bit Length      2
 *
*/

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
        unsigned char turn_switch_status;
} m56_turn_switch_status_t;

static inline void get_m56_turn_switch_status(unsigned char *data, m56_turn_switch_status_t *p) {
        p->turn_switch_status = (data[2] & MASK_b12) >> 1;
}

/*******************************************************************************
 *      m56_atcvt (Automatic Transmission Continuously Variable Transmission)
 *      Message ID      0x421
 *      Transmitted every 60 ms + event
 *
 *      virtual_gear
 *      Byte Position   0
 *      Bit Position    7
 *      Bit Length      8
 *
*/

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
        unsigned char virtual_gear;
} m56_atcvt_t;

static inline void get_m56_atcvt(unsigned char *data, m56_atcvt_t *p) {
        p->virtual_gear = data[0] & MASK_b04;
}

/*******************************************************************************
 *      m56_transmission_mode
 *      Message ID      0x5b0
 *      Transmitted every 100 ms
 *
 *      snow_mode_sw_status
 *      Byte Position   0
 *      Bit Position    7
 *      Bit Length      2
 *
 *      eco_mode_sw_status
 *      Byte Position   0
 *      Bit Position    5
 *      Bit Length      2
 *
 *      standard_mode_sw_status
 *      Byte Position   0
 *      Bit Position    3
 *      Bit Length      2
 *
 *      sport_mode_sw_status
 *      Byte Position   0
 *      Bit Position    1
 *      Bit Length      2
 *
*/

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
        unsigned char snow_mode_sw_status;
        unsigned char eco_mode_sw_status;
        unsigned char standard_mode_sw_status;
        unsigned char sport_mode_sw_status;
} m56_transmission_mode_t;

static inline void get_m56_transmission_mode(unsigned char *data, 
	m56_transmission_mode_t *p) {

        p->snow_mode_sw_status = (data[0] & MASK_b67) >> 6;
        p->eco_mode_sw_status = (data[0] & MASK_b45) >> 4;
        p->standard_mode_sw_status = (data[0] & MASK_b23) >> 2;
        p->sport_mode_sw_status = data[0] & MASK_b01;
}


/*******************************************************************************
 *      m56_front_wiper_status
 *      Message ID      0x625
 *      Transmitted every 100 ms + event
 *
 *      front_wiper_status
 *      Byte Position   2
 *      Bit Position    3
 *      Bit Length      2
 *
*/

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
        unsigned char front_wiper_status;
} m56_front_wiper_status_t;

static inline void get_m56_front_wiper_status(unsigned char *data, 
	m56_front_wiper_status_t *p) {

        p->front_wiper_status = (data[2] & MASK_b23) >> 2;
}

/*******************************************************************************
 *      m56_lidar_target
 *      Message ID      0x52b
 *      Transmitted every 100 ms
 *
 *	distance_to_target
 *      Byte Position   0-1
 *      Bit Position    0-15
 *      Bit Length      16
 *
 *	relative_speed_to_target
 *      Byte Position   2-3
 *      Bit Position    0-15
 *      Bit Length      16
 *
 *	object_type
 *      Byte Position   4
 *      Bit Position    1
 *      Bit Length      1
 *
 *	object_data_valid
 *      Byte Position   4
 *      Bit Position    0
 *      Bit Length      1
 *
*/

typedef struct {
        int ts_ms;
        unsigned char two_message_periods;
        unsigned int message_timeout_counter;
	float distance_to_target;
	float relative_speed_to_target;
        unsigned char object_type;
        unsigned char object_data_valid;
} m56_lidar_target_t;


static inline void get_m56_lidar_target(unsigned char *data, 
	m56_lidar_target_t *p) {

        p->distance_to_target = ((unsigned short)((data[0] + (data[1] << 8)))) * lidar_res;
        p->relative_speed_to_target = ((signed short)((data[2] + (data[3] << 8)))) * lidar_res;
        p->object_type = (data[4] & MASK_b1) >> 1;
        p->object_data_valid = data[4] & MASK_b0;
}

/*******************************************************************************
 *      m56_yaw_rate
 *      Message ID      0x52c
 *      Transmitted every 100 ms
 *
 *	yaw_rate
 *      Byte Position   0-1
 *      Bit Position    0-15
 *      Bit Length      16
 *
 *	yaw_rate_sensor_value
 *      Byte Position   5-6
 *      Bit Position    0-15
 *      Bit Length      16
 *
*/

typedef struct {
        int ts_ms;
        unsigned char two_message_periods;
        unsigned int message_timeout_counter;
	float yaw_rate;
	float yaw_rate_sensor_value;
} m56_yaw_rate_t;


static inline void get_m56_yaw_rate(unsigned char *data, 
	m56_yaw_rate_t *p) {

        p->yaw_rate = ((signed short)((data[0] + (data[1] << 8)))) * yaw_rate_sensor_res;
        p->yaw_rate_sensor_value = ((signed short)((data[5] + (data[6] << 8)))) * yaw_rate_sensor_res;
}

/*******************************************************************************
 *      m56_lidar_status
 *      Message ID      0x52d
 *      Transmitted every 100 ms
 *
 *	laser_operating_flag
 *      Byte Position   1
 *      Bit Position    4
 *      Bit Length      1
 *
 *	laser_fail
 *      Byte Position   1
 *      Bit Position    0
 *      Bit Length      1
 *
*/

typedef struct {
        int ts_ms;
        unsigned char two_message_periods;
        unsigned int message_timeout_counter;
        unsigned char laser_operating_flag;
        unsigned char laser_fail;
} m56_lidar_status_t;


static inline void get_m56_lidar_status(unsigned char *data, 
	m56_lidar_status_t *p) {

        p->laser_operating_flag = (data[1] & MASK_b4) >> 4;
        p->laser_fail = data[1] & MASK_b0;
}

typedef struct {
	unsigned char ignition_status;
} m56_ignition_status_t;

/*
** printcan.c - prints 8-byte CAN message to stdout
*/
int printcan(db_komodo_t *db_kom);

/* TODO
** printmsg - prints parsed contents of M56 CAN message to stdout
*/
int printmsg(db_komodo_t *db_kom);

void check_msg_timeout(int curr_ts_ms, int *prev_ts_ms,
        unsigned char *two_message_periods,
        unsigned int *message_timeout_counter);

/*
** Communication data between vehicles
** 
** DNE491 - Silver M56-S
** DNC304 - Black exterior, gray interior
** PRO4 -   Black exterior, black interior M56-S
*/ 
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID;
	unsigned char MSGCNT_01;
	float v_VSP_491;
	float VSPCOMN_491;
	float ACVCOMO_491;
} m56_vdne491_m210_t;
    
static inline void get_m56_vdne491_m210(unsigned char *data, 
	m56_vdne491_m210_t *p) {
	p->ID = data[0];
	p->MSGCNT_01 = data[1];
	p->v_VSP_491 = (float)(0.1 * (data[2] + (data[3] << 8)));
	p->VSPCOMN_491 = (float)(0.1 * (data[4] + (data[5] << 8)));
	p->ACVCOMO_491 = (float)(0.1 * (data[6] + (data[7] << 8)));
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID;
	unsigned char MSGCNT_02;
	float XG_491;
	float vDISTANCE_491;
	float vVR_491;
	unsigned char fBRAKE_SE_491;
	unsigned char fACCEL_SE_491;
	unsigned char fACC_CRUISE_491;
	unsigned char fSPORTSMODESW_491;
	unsigned char fAUTOMODESW_491;
	unsigned char fSTATE_LOCK_491;
	unsigned char fACC_LMT_CACC_491;
} m56_vdne491_m211_t;
    
static inline void get_m56_vdne491_m211(unsigned char *data, 
	m56_vdne491_m211_t *p) {
	p->ID = data[0];
	p->MSGCNT_02 = data[1];
	p->XG_491 = (float)(0.1 * (data[2]));
	p->vDISTANCE_491 = (float)(0.1 * (data[3] + (data[4] << 8)));
	p->vVR_491 = (float)(0.1 * (data[5] + (data[6] << 8)));
        p->fBRAKE_SE_491 = data[7] & MASK_b0;
        p->fACCEL_SE_491 = data[7] & MASK_b1 >> 1;
        p->fACC_CRUISE_491 = data[7] & MASK_b2 >> 2;
        p->fSPORTSMODESW_491 = data[7] & MASK_b3 >> 3;
        p->fAUTOMODESW_491 = data[7] & MASK_b4 >> 4;
        p->fSTATE_LOCK_491 = data[7] & MASK_b5 >> 5;
        p->fACC_LMT_CACC_491 = data[7] & MASK_b6 >> 6;
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID;
	unsigned char MSGCNT_03;
	float vSET_VSP_491;
} m56_vdne491_m212_t;
    
static inline void get_m56_vdne491_m212(unsigned char *data, 
	m56_vdne491_m212_t *p) {
	p->ID = data[0];
	p->MSGCNT_03 = data[1];
	p->vSET_VSP_491 = (float)(0.1 * (data[2]));
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID;
	unsigned char MSGCNT_04;
} m56_vdne491_m213_t;
    
    
static inline void get_m56_vdne491_m213(unsigned char *data, 
	m56_vdne491_m213_t *p) {
	p->ID = data[0];
	p->MSGCNT_04 = data[1];
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID;
	unsigned char MSGCNT01_PRO4;
	float v_VSP_PRO4;
	float VSPCOMN_PRO4;
	float ACVCOMO_PRO4;
} m56_vpro4_m214_t;
    
static inline void get_m56_vpro4_m214(unsigned char *data, 
	m56_vpro4_m214_t *p) {
	p->ID = data[0];
	p->MSGCNT01_PRO4 = data[1];
	p->v_VSP_PRO4 = (float)(0.1 * (data[2]) + (data[3] << 8));
	p->VSPCOMN_PRO4 = (float)(0.1 * (data[4] + (data[5] << 8)));
	p->ACVCOMO_PRO4 = (float)(0.1 * (data[6] + (data[7] << 8)));
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID;
	unsigned char MSGCNT_02_PRO4;
	float XG_PRO4;
	float vDISTANCE_PRO4;
	float vVR_PRO4;
	unsigned char fBRAKE_SE_PRO4;
	unsigned char fACCEL_SE_PRO4;
	unsigned char fACC_CRUISE_PRO4;
	unsigned char fSPORTSMODESW;
	unsigned char fAUTOMODESW;
	unsigned char fSTATE_LOCK_PRO4;
	unsigned char fACC_LMT_CACC_PRO4;
} m56_vpro4_m215_t;
    
static inline void get_m56_vpro4_m215(unsigned char *data, 
	m56_vpro4_m215_t *p) {
	p->ID = data[0];
	p->MSGCNT_02_PRO4 = data[1];
	p->XG_PRO4 = (float)(0.1 * (data[2]));
	p->vDISTANCE_PRO4 = (float)(0.1 * (data[3] + (data[4] << 8)));
	p->vVR_PRO4 = (float)(0.1 * (data[5] + (data[6] << 8)));
        p->fBRAKE_SE_PRO4 = data[7] & MASK_b0;
        p->fACCEL_SE_PRO4 = data[7] & MASK_b1 >> 1;
        p->fACC_CRUISE_PRO4 = data[7] & MASK_b2 >> 2;
        p->fSPORTSMODESW = data[7] & MASK_b3 >> 3;
        p->fAUTOMODESW = data[7] & MASK_b4 >> 4;
        p->fSTATE_LOCK_PRO4 = data[7] & MASK_b5 >> 5;
        p->fACC_LMT_CACC_PRO4 = data[7] & MASK_b6 >> 6;
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID;
	unsigned char MSGCNT_03_PRO4;
	float vSET_VSP_PRO4;
} m56_vpro4_m216_t;
    
static inline void get_m56_vpro4_m216(unsigned char *data, 
	m56_vpro4_m216_t *p) {
	p->ID = data[0];
	p->MSGCNT_03_PRO4 = data[1];
	p->vSET_VSP_PRO4 = (float)(0.1 * (data[2]));
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID;
	unsigned char MSGCNT_04;
} m56_vpro4_m217_t;
    
static inline void get_m56_vpro4_m217(unsigned char *data, 
	m56_vpro4_m217_t *p) {
	p->ID = data[0];
	p->MSGCNT_04 = data[1];
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID_01_304;
	unsigned char MSGNCT_01_304;
	float v_VSP_304;
	float VSPCOMN_304;
	float ACVCOMO_304;
} m56_vdnc304_m218_t;
    
static inline void get_m56_vdnc304_m218(unsigned char *data, 
	m56_vdnc304_m218_t *p) {
	p->ID_01_304 = data[0];
	p->MSGNCT_01_304 = data[1];
	p->v_VSP_304 = (float)(0.1 * (data[2]) + (data[3] << 8));
	p->VSPCOMN_304 = (float)(0.1 * (data[4] + (data[5] << 8)));
	p->ACVCOMO_304 = (float)(0.1 * (data[6] + (data[7] << 8)));
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID_02_304;
	unsigned char MSGCNT_02_304;
	float XG_304;
	float vDISTANCE_304;
	float vVR_304;
	unsigned char fBRAKE_SE_304;
	unsigned char fACCEL_SE_304;
	unsigned char fACC_CRUISE_304;
	unsigned char fSPORTSMODESW;
	unsigned char fAUTOMODESW;
	unsigned char fSTATE_LOCK_304;
	unsigned char fACC_LMT_CACC_304;
} m56_vdnc304_m219_t;
    
static inline void get_m56_vdnc304_m219(unsigned char *data, 
	m56_vdnc304_m219_t *p) {
	p->ID_02_304 = data[0];
	p->MSGCNT_02_304 = data[1];
	p->XG_304 = (float)(0.1 * (data[2]));
	p->vDISTANCE_304 = (float)(0.1 * (data[3] + (data[4] << 8)));
	p->vVR_304 = (float)(0.1 * (data[5] + (data[6] << 8)));
        p->fBRAKE_SE_304 = data[7] & MASK_b0;
        p->fACCEL_SE_304 = data[7] & MASK_b1 >> 1;
        p->fACC_CRUISE_304 = data[7] & MASK_b2 >> 2;
        p->fSPORTSMODESW = data[7] & MASK_b3 >> 3;
        p->fAUTOMODESW = data[7] & MASK_b4 >> 4;
        p->fSTATE_LOCK_304 = data[7] & MASK_b5 >> 5;
        p->fACC_LMT_CACC_304 = data[7] & MASK_b6 >> 6;
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID_03_304;
	unsigned char MSGCNT_03_304;
	float vSET_VSP_304;
} m56_vdnc304_m21a_t;
    
static inline void get_m56_vdnc304_m21a(unsigned char *data, 
	m56_vdnc304_m21a_t *p) {
	p->ID_03_304 = data[0];
	p->MSGCNT_03_304 = data[1];
	p->vSET_VSP_304 = (float)(0.1 * (data[2]));
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID_04_304;
	unsigned char MSGCNT_04_304;
} m56_vdnc304_m21b_t;
    
static inline void get_m56_vdnc304_m21b(unsigned char *data, 
	m56_vdnc304_m21b_t *p) {
	p->ID_04_304 = data[0];
	p->MSGCNT_04_304 = data[1];
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID_01_PRO4_2;
	unsigned char MSGNCT_01_PRO4;
	float v_VSP_PRO4_2;
	float VSPCOMN_PRO4_2;
	float ACVCOMO_PRO4_2;
} m56_vpro4_m21c_t;
    
static inline void get_m56_vpro4_m21c(unsigned char *data, 
	m56_vpro4_m21c_t *p) {
	p->ID_01_PRO4_2 = data[0];
	p->MSGNCT_01_PRO4 = data[1];
	p->v_VSP_PRO4_2 = (float)(0.1 * (data[2]) + (data[3] << 8));
	p->VSPCOMN_PRO4_2 = (float)(0.1 * (data[4] + (data[5] << 8)));
	p->ACVCOMO_PRO4_2 = (float)(0.1 * (data[6] + (data[7] << 8)));
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID_02_PRO4_2;
	unsigned char MSGCNT_02_PRO4_2;
	float XG_PRO4_2;
	float vDISTANCE_PRO4_2;
	float vVR_PRO4_2;
	unsigned char fBRAKE_SE_PRO4_2;
	unsigned char fACCEL_SE_PRO4_2;
	unsigned char fACC_CRUISE_PRO4_2;
	unsigned char fSPORTSMODESW;
	unsigned char fAUTOMODESW;
	unsigned char fSTATE_LOCK_PRO4_2;
	unsigned char fACC_LMT_CACC_PRO4_2;
} m56_vpro4_m21d_t;
    
static inline void get_m56_vpro4_m21d(unsigned char *data, 
	m56_vpro4_m21d_t *p) {
	p->ID_02_PRO4_2 = data[0];
	p->MSGCNT_02_PRO4_2 = data[1];
	p->XG_PRO4_2 = (float)(0.1 * (data[2]));
	p->vDISTANCE_PRO4_2 = (float)(0.1 * (data[3] + (data[4] << 8)));
	p->vVR_PRO4_2 = (float)(0.1 * (data[5] + (data[6] << 8)));
        p->fBRAKE_SE_PRO4_2 = data[7] & MASK_b0;
        p->fACCEL_SE_PRO4_2 = data[7] & MASK_b1 >> 1;
        p->fACC_CRUISE_PRO4_2 = data[7] & MASK_b2 >> 2;
        p->fSPORTSMODESW = data[7] & MASK_b3 >> 3;
        p->fAUTOMODESW = data[7] & MASK_b4 >> 4;
        p->fSTATE_LOCK_PRO4_2 = data[7] & MASK_b5 >> 5;
        p->fACC_LMT_CACC_PRO4_2 = data[7] & MASK_b6 >> 6;
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID_03_PRO4_2;
	unsigned char MSGCNT_03_PRO4_2;
	float vSET_VSP_PRO4_2;
} m56_vpro4_m21e_t;
    
static inline void get_m56_vpro4_m21e(unsigned char *data, 
	m56_vpro4_m21e_t *p) {
	p->ID_03_PRO4_2 = data[0];
	p->MSGCNT_03_PRO4_2 = data[1];
	p->vSET_VSP_PRO4_2 = (float)(0.1 * (data[2]));
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID_04_PRO4_2;
	unsigned char MSGCNT_04_PRO4_2;
} m56_vpro4_m21f_t;
    
static inline void get_m56_vpro4_m21f(unsigned char *data, 
	m56_vpro4_m21f_t *p) {
	p->ID_04_PRO4_2 = data[0];
	p->MSGCNT_04_PRO4_2 = data[1];
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	//From ADAS - Fanping wants this   
	float vACC_COM_LMT_z0;
	float vMDISTANCE_ADAS;
	float vvPRECEDING_SPEED_ADAS32;
	unsigned char fSTATE_LOCK_ADAS;
} m56_adas_289_t;
    
static inline void get_m56_adas_289(unsigned char *data, 
	m56_adas_289_t *p) {
	p->vACC_COM_LMT_z0 = 0.1 * data[0];
	p->vMDISTANCE_ADAS = (float)(0.1 * (data[2]) + (data[3] << 8));
	p->vvPRECEDING_SPEED_ADAS32 = 
		(float)(0.1 * (data[4] + (data[5] << 8)));
	p->fSTATE_LOCK_ADAS = data[6] & MASK_b0;
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	//From ADAS - Fanping wants this   
	float vVSPCOMN;
	float vACVCOMO;
} m56_adas_28a_t;
    
static inline void get_m56_adas_28a(unsigned char *data, 
	m56_adas_28a_t *p) {
	p->vVSPCOMN = (float)(0.1 * (data[0]) + (data[1] << 8));
	p->vACVCOMO = (float)(0.1 * (data[2]) + (data[3] << 8));
}

    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char hosttx_msgcnt_id200;

	//my current speed
	float hosttx_curr_spd_vsp_491;

	//my target speed, no cars ahead
	float hosttx_target_spd_vspcomn_491;

	//my target speed, distance ahead controlled because of cars ahead
	float hosttx_dist_ctl_target_spd_acvcomo_491;

	//my acceleration
	float hosttx_acceleration_xg_491;
} m56_m200_t;
    
static inline void get_m56_m200(unsigned char *data, 
	m56_m200_t *p) {
	p->hosttx_msgcnt_id200 = data[0];
	p->hosttx_curr_spd_vsp_491 = (float)(0.1 * ((data[1]) + (data[2] << 8)));
	p->hosttx_target_spd_vspcomn_491 = (float)(0.1 * ((data[3]) + (data[4] << 8)));
	p->hosttx_dist_ctl_target_spd_acvcomo_491 = (float)(0.1 * ((data[5]) + (data[6] << 8)));
	p->hosttx_acceleration_xg_491 = (float)(0.01 * (signed char)data[7]);
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char hosttx_msgcnt_id201;

	//distance to previous car
	float hosttx_prev_spd_mdistance_491;

	//relative speed to previous car
	float hosttx_relative_spd_vr_491;

	//Driver brake status
	unsigned char hosttx_brake_sw_491;

	//Accelerator switch status
	unsigned char hosttx_accel_sw_491;

	//set speed
	float hosttx_setvsp_491;

} m56_m201_t;
    
static inline void get_m56_m201(unsigned char *data, 
	m56_m201_t *p) {
	p->hosttx_msgcnt_id201 = data[0];
	p->hosttx_prev_spd_mdistance_491 = (float)(0.1 * ((data[1]) + (data[2] << 8)));
	p->hosttx_relative_spd_vr_491 = (float)(0.1 * ((data[3]) + (data[4] << 8)));
	p->hosttx_brake_sw_491 = data[5] & MASK_b0;
	p->hosttx_accel_sw_491 = (data[5] & MASK_b1) >> 1;
	p->hosttx_setvsp_491 = (float)(0.1 * ((data[6]) + (data[7] << 8)));
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char hosttx_msgcnt_id202;
} m56_m202_t;
    
static inline void get_m56_m202(unsigned char *data, 
	m56_m202_t *p) {
	p->hosttx_msgcnt_id202 = data[0];
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float yaw_rate;
	unsigned char couple_prec_veh;
	unsigned char couple_follow_veh;
} m56_m203_t;
    
static inline void get_m56_m203(unsigned char *data, 
	m56_m203_t *p) {
	p->yaw_rate = (float)(0.1 * ((data[0]) + (data[1] << 8)));
	p->couple_prec_veh = (data[2] & MASK_b47) >> 4;
	p->couple_follow_veh = data[2] & MASK_b03;
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char hosttx_host_veh_ctr4;

	//GPS range to preceding vehicle
	float hosttx_gps_range_prev_veh;

	//Tracking status (0=idle, 1=detecting, 2=tracking, 3=coupling, 0xF=invalid)
	unsigned char hosttx_tracking_status;

	// Vehicle position type (0=stand alone vehicle, 1=head of train, 
	// 2=tail 0f train, 3=middle vehicle of train, 0xf=invalid)
	unsigned char hosttx_veh_position_type;

	// Forward sequence number (0=head vehicle of train, 
	// 0x01-0xFE=following vehicles, 0xFF=invalid)
	unsigned char hosttx_veh_fwd_seq_num;

	// Backward sequence number (0=tail vehicle of train, 
	// 0x01-0xFE=preceding vehicles, 0xFF=invalid)
	unsigned char hosttx_veh_backwd_seq_num;
} m56_m650_t;
    
static inline void get_m56_m650(unsigned char *data, 
	m56_m650_t *p) {
	p->hosttx_host_veh_ctr4 = data[0];
	p->hosttx_gps_range_prev_veh = (float)(0.1 * ((signed short)((data[1]) + (data[2] << 8))));
	p->hosttx_tracking_status = data[3] & MASK_b03;
	p->hosttx_veh_position_type = (data[3] & MASK_b47) >> 4;
	p->hosttx_veh_fwd_seq_num = data[4];
	p->hosttx_veh_backwd_seq_num = data[5];
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char hosttx_host_gps_ctr6;

	//GPS latitude
	float hosttx_gps_latitude;

	//GPS latitude accuracy
	float hosttx_gps_lat_accuracy;

} m56_m651_t;
    
static inline void get_m56_m651(unsigned char *data, 
	m56_m651_t *p) {
	p->hosttx_host_gps_ctr6 = data[0];
	p->hosttx_gps_latitude = ((signed int)( (data[1] << 24)+ (data[2] << 16) + (data[3] << 8) + data[4] ))/(3600*256.0);
	p->hosttx_gps_lat_accuracy = (float)( 0.1 * ((signed short)( (data[5] << 8) + data[6] )));
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char hosttx_host_gps_ctr7;

	//GPS longitude
	float hosttx_gps_longitude;

	//GPS longitude accuracy
	float hosttx_gps_long_accuracy;

} m56_m652_t;
    
static inline void get_m56_m652(unsigned char *data, 
	m56_m652_t *p) {
	p->hosttx_host_gps_ctr7 = data[0];
	p->hosttx_gps_longitude = ((signed int)( (data[1] << 24)+ (data[2] << 16) + (data[3] << 8) + data[4] ))/(3600*256.0);
	p->hosttx_gps_long_accuracy = (float)( 0.1 * ((signed short)( (data[5] << 8) + data[6] )));
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char hosttx_host_gps_ctr8;

	//GPS altitude
	float hosttx_gps_altitude;

	//GPS altitude accuracy
	float hosttx_gps_alt_accuracy;

} m56_m653_t;
    
static inline void get_m56_m653(unsigned char *data, 
	m56_m653_t *p) {
	p->hosttx_host_gps_ctr8 = data[0];
	p->hosttx_gps_altitude = (float)( 0.01 * ((signed int)( (data[1] << 24)+ (data[2] << 16) + (data[3] << 8) + data[4] )));
	p->hosttx_gps_alt_accuracy = (float)( 0.01 * ((signed short)( (data[5] << 8) + data[6] )));
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char hosttx_host_gps_ctr9;

	//GPS heading
	float hosttx_gps_heading;

	//GPS heading accuracy
	float hosttx_gps_heading_accuracy;

	//GPS speed
	float hosttx_gps_speed;
} m56_m654_t;
    
static inline void get_m56_m654(unsigned char *data, 
	m56_m654_t *p) {
	p->hosttx_host_gps_ctr9 = data[0];
	p->hosttx_gps_heading = (float)( 0.1 * ((signed short)( (data[1] << 8) + data[2] )));
	p->hosttx_gps_heading_accuracy = (float)( 0.1 * ((signed short)( (data[3] << 8) + data[4] )));
	p->hosttx_gps_speed = (float)( 0.1 * ( (data[5] << 8) + data[6] ));
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char hosttx_host_gps_ctr10;

	unsigned char hosttx_gps_num_sat_in_use;
	unsigned char hosttx_gps_num_sat_in_view;
	float hosttx_gps_hdop;
	float hosttx_gps_pdop;
	unsigned short hosttx_gps_fix_status;
} m56_m655_t;
    
static inline void get_m56_m655(unsigned char *data, 
	m56_m655_t *p) {
	p->hosttx_host_gps_ctr10 = data[0];
	p->hosttx_gps_num_sat_in_use = data[1];
	p->hosttx_gps_num_sat_in_view = data[2];
	p->hosttx_gps_hdop = (float)( 0.1 * data[3]);
	p->hosttx_gps_pdop = (float)( 0.1 * data[4]);
	p->hosttx_gps_fix_status = (float)((data[5] << 8) + data[6]);
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char hosttx_host_gps_ctr11;

	unsigned short hosttx_gps_ts_year;
	unsigned char hosttx_gps_ts_month;
	unsigned char hosttx_gps_ts_day;
	unsigned char hosttx_gps_ts_hour;
	unsigned char hosttx_gps_ts_minute;
	unsigned char hosttx_gps_ts_second;
} m56_m656_t;
    
static inline void get_m56_m656(unsigned char *data, 
	m56_m656_t *p) {
	p->hosttx_host_gps_ctr11 = data[0];
	p->hosttx_gps_ts_year = (data[1] << 8) + data[2];
	p->hosttx_gps_ts_month = data[3];
	p->hosttx_gps_ts_day = data[4];
	p->hosttx_gps_ts_hour = data[5];
	p->hosttx_gps_ts_minute = data[6];
	p->hosttx_gps_ts_second = data[7];
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char hosttx_host_gps_ctr12;

	unsigned short hosttx_gps_ts_millisecond;
} m56_m657_t;
    
static inline void get_m56_m657(unsigned char *data, 
	m56_m657_t *p) {
	p->hosttx_host_gps_ctr12 = data[0];
	p->hosttx_gps_ts_millisecond = (data[1] << 8) + data[2];
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char hosttx_host_gps_ctr13;
} m56_m658_t;
    
static inline void get_m56_m658(unsigned char *data, 
	m56_m658_t *p) {
	p->hosttx_host_gps_ctr13 = data[0];
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char keepalive_mabx2wsu_1;
	unsigned char keepalive_mabx2wsu_2;
	unsigned char keepalive_mabx2wsu_3;
	unsigned char keepalive_mabx2wsu_4;
	unsigned char keepalive_mabx2wsu_5;
	unsigned char keepalive_mabx2wsu_6;
} m56_m710_t;
    
static inline void get_m56_m710(unsigned char *data, 
	m56_m710_t *p) {
	p->keepalive_mabx2wsu_1 = data[0];
	p->keepalive_mabx2wsu_2 = data[1];
	p->keepalive_mabx2wsu_3 = data[2];
	p->keepalive_mabx2wsu_4 = data[3];
	p->keepalive_mabx2wsu_5 = data[4];
	p->keepalive_mabx2wsu_6 = data[5];
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char keepalive_echo_wsu2mabx_1;
	unsigned char keepalive_echo_wsu2mabx_2;
	unsigned char keepalive_echo_wsu2mabx_3;
	unsigned char keepalive_echo_wsu2mabx_4;
	unsigned char keepalive_echo_wsu2mabx_5;
	unsigned char keepalive_echo_wsu2mabx_6;
	unsigned short wsu_id;
} m56_m711_t;
    
static inline void get_m56_m711(unsigned char *data, 
	m56_m711_t *p) {
	p->keepalive_echo_wsu2mabx_1 = data[0];
	p->keepalive_echo_wsu2mabx_2 = data[1];
	p->keepalive_echo_wsu2mabx_3 = data[2];
	p->keepalive_echo_wsu2mabx_4 = data[3];
	p->keepalive_echo_wsu2mabx_5 = data[4];
	p->keepalive_echo_wsu2mabx_6 = data[5];
	p->wsu_id = (data[6] << 8) + data[7];
}

typedef struct {

	// Typedef for messages for n-th preceding vehicle, where n=3 for 
	// 1 car ahead, n=4 for 2 cars ahead, etc. until n=7 for
	// 5 cars ahead.  So for data from 1 car ahead, we get message
	// number 0x430, for 2 cars ahead we get message number 0x440, and
	// so forth until we get message number 0x470 for 5 cars ahead

	//This also works for the n-th following vehicle, where n=8 for
	//1 car behind, n=9 for 2 cars behind, etc., until n=C for
	//5 cars behind. So for data from 1 car behind, we get message
	// number 0x480, for 2 cars behind we get message number 0x490, and
	// so forth until we get message number 0x4C0 for 5 cars behind 

	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char msgcnt_id200;

	//Current speed received from n cars ahead
	float host_rx_vsp_491;

	//Target speed received from n cars ahead, distance not controlled
	float host_rx_vspcomn_491;

	//Target speed received from n cars ahead, distance controlled
	float host_rx_acvcomo_491;

	//Current acceleration received from n cars ahead
	float host_rx_xg_491;
} m56_m4n0_t;
    
static inline void get_m56_m4n0(unsigned char *data, 
	m56_m4n0_t *p) {
	p->msgcnt_id200 = data[0];
	p->host_rx_vsp_491 = (float)(0.1 * ((data[2] << 8) + data[1]));
	p->host_rx_vspcomn_491 = (float)(0.1 * ((data[4] << 8) + data[3]));
	p->host_rx_acvcomo_491 = (float)(0.1 * ((data[6] << 8) + data[5]));
	p->host_rx_xg_491 = (float)(0.01 * data[7]);
}

typedef struct {

	// Typedef for messages for n-th preceding vehicle, where n=3 for 
	// 1 car ahead, n=4 for 2 cars ahead, etc. until n=7 for
	// 5 cars ahead.  So for data from 1 car ahead, we get message
	// number 0x431, for 2 cars ahead we get message number 0x441, and
	// so forth until we get message number 0x471 for 5 cars ahead

	//This also works for the n-th following vehicle, where n=8 for
	//1 car behind, n=9 for 2 cars behind, etc., until n=C for
	//5 cars behind. So for data from 1 car behind, we get message
	// number 0x480, for 2 cars behind we get message number 0x490, and
	// so forth until we get message number 0x4C0 for 5 cars behind 

	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char msgcnt_id201;

	//Distance received from n cars ahead
	float host_rx_mdistance_491;

	//Speed received from n cars ahead
	float host_rx_vr_491;

	//Brake switch status received from n cars ahead
	unsigned char host_rx_brake_sw_491;

	//Accelerator switch status received from n cars ahead
	unsigned char host_rx_accel_sw_491;

	//Set speed received from n cars ahead
	float host_rx_setvsp_491;

} m56_m4n1_t;
    
static inline void get_m56_m4n1(unsigned char *data, 
	m56_m4n1_t *p) {
	p->msgcnt_id201 = data[0];
	p->host_rx_mdistance_491 = (float)(0.1 * ((data[2] << 8) + data[1]));
	p->host_rx_vr_491 = (float)(0.1 * ((data[4] << 8) + data[3]));
	p->host_rx_brake_sw_491 = data[5] & MASK_b0;
	p->host_rx_accel_sw_491 = (data[5] & MASK_b1) >> 1;
	p->host_rx_setvsp_491 = (float)(0.1 * ((data[7] << 8) + data[6]));
}

typedef struct {

	// Typedef for messages for n-th preceding vehicle, where n=3 for 
	// 1 car ahead, n=4 for 2 cars ahead, etc. until n=7 for
	// 5 cars ahead.  So for data from 1 car ahead, we get message
	// number 0x432, for 2 cars ahead we get message number 0x442, and
	// so forth until we get message number 0x472 for 5 cars ahead

	//This also works for the n-th following vehicle, where n=8 for
	//1 car behind, n=9 for 2 cars behind, etc., until n=C for
	//5 cars behind. So for data from 1 car behind, we get message
	// number 0x481, for 2 cars behind we get message number 0x491, and
	// so forth until we get message number 0x4C1 for 5 cars behind 

	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char msgcnt_id202;
} m56_m4n2_t;
    
static inline void get_m56_m4n2(unsigned char *data, 
	m56_m4n2_t *p) {
	p->msgcnt_id202 = data[0];
}

typedef struct {

	// Typedef for messages for n-th preceding vehicle, where n=3 for 
	// 1 car ahead, n=4 for 2 cars ahead, etc. until n=7 for
	// 5 cars ahead.  So for data from 1 car ahead, we get message
	// number 0x433, for 2 cars ahead we get message number 0x443, and
	// so forth until we get message number 0x473 for 5 cars ahead

	//This also works for the n-th following vehicle, where n=8 for
	//1 car behind, n=9 for 2 cars behind, etc., until n=C for
	//5 cars behind. So for data from 1 car behind, we get message
	// number 0x483, for 2 cars behind we get message number 0x493, and
	// so forth until we get message number 0x4C3 for 5 cars behind 

	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char msgcnt_n;

	//GPS range to n cars ahead
	float host_rx_gps_range;

	//Tracking status received from n cars ahead
	//0=idle, 1=detecting, 2=tracking, 3=coupling, 0xF=invalid
	unsigned char host_rx_gps_tracking_status;

	//Vehicle position type received from n cars ahead
	//0=standalone vehicle, 1=head of train, 2=tail of train,
	//3=middle vehicle of train, 0xF=invalid
	unsigned char host_rx_gps_veh_pos_type;

	//Forward sequence number received from n cars ahead
	//0=head vehicle of train, 1-0xFE=following vehicles,
	//0xFF=invalid
	unsigned char host_rx_fwd_seq_num;

	//Backward sequence number received from n cars ahead
	//0=tail vehicle of train, 1-0xFE=preceding vehicles,
	//0xFF=invalid
	unsigned char host_rx_backwd_seq_num;


} m56_m4n3_t;
    
static inline void get_m56_m4n3(unsigned char *data, 
	m56_m4n3_t *p) {
	p->msgcnt_n = data[0];
	p->host_rx_gps_range = (float)(0.1 * ((data[1] << 8) + data[2]));
	p->host_rx_gps_tracking_status = data[3] & MASK_b03;
	p->host_rx_gps_veh_pos_type = (data[3] & MASK_b47) >> 4;
	p->host_rx_fwd_seq_num = data[4];
	p->host_rx_backwd_seq_num = data[5];
}

typedef struct {

	// Typedef for messages for n-th preceding vehicle, where n=3 for 
	// 1 car ahead, n=4 for 2 cars ahead, etc. until n=7 for
	// 5 cars ahead.  So for data from 1 car ahead, we get message
	// number 0x434, for 2 cars ahead we get message number 0x444, and
	// so forth until we get message number 0x474 for 5 cars ahead

	//This also works for the n-th following vehicle, where n=8 for
	//1 car behind, n=9 for 2 cars behind, etc., until n=C for
	//5 cars behind. So for data from 1 car behind, we get message
	// number 0x484, for 2 cars behind we get message number 0x494, and
	// so forth until we get message number 0x4C4 for 5 cars behind 

	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char msgcnt_n;

	//WSU ID from n cars ahead
	unsigned short host_rx_wsu_id;

	//Percent channel busy received from n cars ahead
	unsigned char host_rx_chanbusy;

	//RSS in dBm received from n cars ahead
	float host_rx_rss;

	//RxPktPER% received from n cars ahead
	//I assume this is a percentage of packets received
	float host_rx_pkt_pct;
} m56_m4n4_t;
    
static inline void get_m56_m4n4(unsigned char *data, 
	m56_m4n4_t *p) {
	p->msgcnt_n = data[0];
	p->host_rx_wsu_id = (data[1] << 8) + data[2];
	p->host_rx_chanbusy = data[3];
	p->host_rx_rss = (float)(0.1 * ((data[4] << 8) + data[5]));
	p->host_rx_pkt_pct = (float)(0.1 * ((data[6] << 8) + data[7]));
}

typedef struct {

	// Typedef for messages for n-th preceding vehicle, where n=3 for 
	// 1 car ahead, n=4 for 2 cars ahead, etc. until n=7 for
	// 5 cars ahead.  So for data from 1 car ahead, we get message
	// number 0x435, for 2 cars ahead we get message number 0x445, and
	// so forth until we get message number 0x475 for 5 cars ahead

	//This also works for the n-th following vehicle, where n=8 for
	//1 car behind, n=9 for 2 cars behind, etc., until n=C for
	//5 cars behind. So for data from 1 car behind, we get message
	// number 0x485, for 2 cars behind we get message number 0x495, and
	// so forth until we get message number 0x4C5 for 5 cars behind 

	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char msgcnt_n;

	//GPS latitude received from n cars ahead
	float host_rx_gps_latitude;

	//GPS heading received from n cars ahead
	float host_rx_gps_heading;

} m56_m4n5_t;
    
static inline void get_m56_m4n5(unsigned char *data, 
	m56_m4n5_t *p) {
	p->msgcnt_n = data[0];
	p->host_rx_gps_latitude = ((float)((signed int)((data[1] << 24) + 
		(data[2] << 16) + (data[3] << 8) + data[4] ))) / (3600*256.0);
	p->host_rx_gps_heading = (float)(0.1 * ((signed short)((data[5] << 8) + data[6] )) );
}

typedef struct {

	// Typedef for messages for n-th preceding vehicle, where n=3 for 
	// 1 car ahead, n=4 for 2 cars ahead, etc. until n=7 for
	// 5 cars ahead.  So for data from 1 car ahead, we get message
	// number 0x436, for 2 cars ahead we get message number 0x446, and
	// so forth until we get message number 0x476 for 5 cars ahead

	//This also works for the n-th following vehicle, where n=8 for
	//1 car behind, n=9 for 2 cars behind, etc., until n=C for
	//5 cars behind. So for data from 1 car behind, we get message
	// number 0x486, for 2 cars behind we get message number 0x496, and
	// so forth until we get message number 0x4C6 for 5 cars behind 

	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char msgcnt_n;

	//GPS longitude received from n cars ahead
	float host_rx_gps_longitude;

	//GPS speed received from n cars ahead
	float host_rx_gps_speed;

} m56_m4n6_t;
    
static inline void get_m56_m4n6(unsigned char *data, 
	m56_m4n6_t *p) {
	p->msgcnt_n = data[0];
	p->host_rx_gps_longitude = ((float)((signed int)((data[1] << 24) + 
		(data[2] << 16) + (data[3] << 8) + data[4] ))) / (3600*256.0);
	p->host_rx_gps_speed = (float)(0.1 * ((signed short)((data[5] << 8) + data[6] )) );
}

typedef struct {

	// Typedef for messages for n-th preceding vehicle, where n=3 for 
	// 1 car ahead, n=4 for 2 cars ahead, etc. until n=7 for
	// 5 cars ahead.  So for data from 1 car ahead, we get message
	// number 0x437, for 2 cars ahead we get message number 0x447, and
	// so forth until we get message number 0x477 for 5 cars ahead

	//This also works for the n-th following vehicle, where n=8 for
	//1 car behind, n=9 for 2 cars behind, etc., until n=C for
	//5 cars behind. So for data from 1 car behind, we get message
	// number 0x487, for 2 cars behind we get message number 0x497, and
	// so forth until we get message number 0x4C7 for 5 cars behind 

	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char msgcnt_n;

	//GPS altitude received from n cars ahead
	float host_rx_gps_altitude;
} m56_m4n7_t;
    
static inline void get_m56_m4n7(unsigned char *data, 
	m56_m4n7_t *p) {
	p->msgcnt_n = data[0];
	p->host_rx_gps_altitude = (float)(0.01 * ((signed int)((data[1] << 24) + 
		(data[2] << 16) + (data[3] << 8) + data[4] )) );
}

typedef struct {

	// Typedef for messages for n-th preceding vehicle, where n=3 for 
	// 1 car ahead, n=4 for 2 cars ahead, etc. until n=7 for
	// 5 cars ahead.  So for data from 1 car ahead, we get message
	// number 0x438, for 2 cars ahead we get message number 0x448, and
	// so forth until we get message number 0x478 for 5 cars ahead

	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char msgcnt_n;

	//GPS timestamp milliseconds, received from n cars ahead
	unsigned short host_rx_gps_ts_millisecond;

	//GPS range to host vehicle received from n cars ahead
	float host_rx_gps_range2host;

	//Relative position to host vehicle received from n cars ahead
	//0x00=unclassified, 0x01=ahead, 0x02=behind, 0x03=oncoming, 
	//0x04=ahead left, 0x05=ahead right, 0x06=behind left, 
	//0x07=behind right, 0x08=oncoming left, 0x09=oncoming right, 
	//0x0A=ahead far left, 0X0B=ahead far right, 0x0C=behind far left, 
	//0x0D=behind far right, 0x0E=oncoming far left, 
	//0x0F=oncoming far right, 0x10=intersecting left
	//0x11=intersecting right
	unsigned char host_rx_gps_relpos2host;
} m56_m4n8_t;
    
static inline void get_m56_m4n8(unsigned char *data, 
	m56_m4n8_t *p) {
	p->msgcnt_n = data[0];
	p->host_rx_gps_ts_millisecond = (data[1] << 8) + data[2];
	p->host_rx_gps_range2host = (float)(0.1 * ((data[3] << 8) + data[4]));
	p->host_rx_gps_relpos2host = data[5];
}

//test
