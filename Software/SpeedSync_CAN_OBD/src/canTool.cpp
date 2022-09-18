#include "mainHeader.h"

void set_mask_filt() 
{
    /*
        set mask, set both the mask to 0x3ff
    */
    CAN.init_Mask(0, 0, 0x7FC);
    CAN.init_Mask(1, 0, 0x7FC);

    /*
        set filter, we can receive id from 0x04 ~ 0x09
    */
    CAN.init_Filt(0, 0, CAN_ID_PID_RSP);
    CAN.init_Filt(1, 0, CAN_ID_PID_RSP);

    CAN.init_Filt(2, 0, CAN_ID_PID_RSP);
    CAN.init_Filt(3, 0, CAN_ID_PID_RSP);
    CAN.init_Filt(4, 0, CAN_ID_PID_RSP);
    CAN.init_Filt(5, 0, CAN_ID_PID_RSP);

}

boolean checkPID()
{
    byte buf[8] = {0x00};
    byte len = 0;

//check if engine rpm and vehicule speed are supported
    buf[0] = PID_SUPORTED_01_20;
    len = 1;

    CAN.sendMsgBuf(CAN_ID_PID_RQT,CAN_STDID,len,buf);
    CAN.readMsgBuf(&len,buf);

    if (len > 0)
    {
// do mask on answer on DATA_B (cf std), want PID 0x0C and 0x0D, mask 0x00011000
        fTempWaterAvailable     = buf[DATA_A] & 0b00010000; //PID_05_EngineCoolantTemp
        fSpeedEngineAvailable   = buf[DATA_B] & 0b00001000; //PID_0C_EngineRPM
        fSpeedVehileAvailable   = buf[DATA_B] & 0b00010000; //PID_0D_VehicleSpeed
    }
    else //we did not receive answer from ECU
    {
        return false;
    }
    
//Check if oil temperature is supported    
    buf[0] = PID_SUPORTED_41_60;
    len = 1;

    CAN.sendMsgBuf(CAN_ID_PID_RQT,CAN_STDID,len,buf);
    CAN.readMsgBuf(&len,buf);

    if (len > 0)
    {
        fTempOilAvailable   = buf[DATA_B] & 0b00001000; //PID_5C_EngineOilTemp
    }
    else //we did not receive answer from ECU
    {
        return false;
    }

  return true;
}

boolean checkDTC()
{
    return true;
}