#ifndef _CANTOOL_H_
#define _CANTOOL_H_


void set_mask_filt();
boolean checkPID();
boolean checkDTC();


//OBD stuff

// The request ID is common. But depending of the vehicule, the ECU that answer can difer and have ID between 7E0 and 7E8.
#define CAN_ID_PID_RQT          0x7DF
#define CAN_ID_PID_RSP          0x7E8

//First block 00->1F
#define PID_SUPORTED_01_20      0x00 //SG_ S1_PID_00_PIDsSupported_01_20 m0 : 31|32@0+ (1,0) [0|4294967295] "" Vector__XXX
#define PID_ENGINE_COOLANT_TEMP 0x05 // SG_ S1_PID_05_EngineCoolantTemp m5 : 31|8@0+ (1,-40) [-40|215] "degC" Vector__XXX
#define PID_ENGINE_PRM          0x0C //SG_ S1_PID_0C_EngineRPM m12 : 31|16@0+ (0.25,0) [0|16383.75] "rpm" Vector__XXX
#define PID_VEHICLE_SPEED       0x0D //SG_ S1_PID_0D_VehicleSpeed m13 : 31|8@0+ (1,0) [0|255] "km/h" Vector__XXX

//Second block
#define PID_SUPORTED_21_40  0x20 //SG_ S1_PID_20_PIDsSupported_21_40 m32 : 31|32@0+ (1,0) [0|4294967295] "" Vector__XXX

//Third block
#define PID_SUPORTED_41_60  0x40//SG_ S1_PID_40_PIDsSupported_41_60 m64 : 31|32@0+ (1,0) [0|4294967295] "" Vector__XXX
#define PID_ENGINE_OIL_TEMP 0x5C//SG_ S1_PID_5C_EngineOilTemp m92 : 31|8@0+ (1,-40) [-40|215] "degC" Vector__XXX

//Fourth block
#define PID_SUPORTED_61_80  0x60//SG_ S1_PID_60_PIDsSupported_61_80 m96 : 31|32@0+ (1,0) [0|4294967295] "" Vector__XXX

//payload location name according to the OBD std
#define DATA_A 0
#define DATA_B 1
#define DATA_C 2



#endif