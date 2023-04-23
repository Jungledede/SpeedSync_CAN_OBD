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

/// @brief Read Speed of the engine and vehicule from CAN.
/// @param psEngineRPM int16_t pointer. Scalled value in RPM.
/// @param pbVehiculeSpeed byte pointer. Scalled value in kph.
void GetSpeeds(int16_t *psEngineRPM, byte *pbVehiculeSpeed)
{
// SG_ S1_PID_0C_EngineRPM m12 : 31|16@0+ (0.25,0) [0|16383.75] "rpm" Vector__XXX
// SG_ S1_PID_0D_VehicleSpeed m13 : 31|8@0+ (1,0) [0|255] "km/h" Vector__XXX
    
    byte buf[8] = {0x00};
    byte len;
    byte index;

//check if engine rpm and vehicule speed are supported
    buf[0] = PID_ENGINE_PRM;
    buf[1] = PID_VEHICLE_SPEED;
    len = 2;

    CAN.sendMsgBuf(CAN_ID_PID_RQT,CAN_STDID,len,buf);
    CAN.readMsgBuf(&len,buf);

    if (len > 0)
    {
        //Seek the result buffer to find the IDs. 
        //The OBD std is not clear if result are sent in the requested order.
        //Since IDs are put before the value, we are looking for them.
        for(index = 0; index < len; index++)
        {
            if (buf[index] == PID_ENGINE_PRM)
            {
                *psEngineRPM = (int16_t)buf[index+1] / 4;
                index += SIZEOF_SHORT;
            }

            if (buf[index] == PID_VEHICLE_SPEED)
            {
                
                *pbVehiculeSpeed = buf[index+1];
                index += SIZEOF_BYTE; //To have the index go over the data. Allow next loop to seek for the next IDs
            }
        }
    }
    else //we did not receive answer from ECU
    {
        Serial.print("Error on get speeds from CAN\n");
    }

}

/// @brief Get the Engine Oil Temperature
/// @param pbTemp byte pointer of the temp scalled in Deg C
void GetOilTemp(byte *pbTemp)
{
// SG_ S1_PID_5C_EngineOilTemp m92 : 31|8@0+ (1,-40) [-40|215] "degC" Vector__XXX
    byte buf[8] = {0x00};
    byte len;
    byte index;

//check if engine rpm and vehicule speed are supported
    buf[0] = PID_ENGINE_OIL_TEMP;
    len = 1;

    CAN.sendMsgBuf(CAN_ID_PID_RQT,CAN_STDID,len,buf);
    CAN.readMsgBuf(&len,buf);

    if (len > 0)
    {
        //Seek the result buffer to find the IDs. 
        //The OBD std is not clear if result are sent in the requested order.
        //Since IDs are put before the value, we are looking for them.
        for(index = 0; index < len; index++)
        {
            if (buf[index] == PID_ENGINE_OIL_TEMP)
            {
                
                *pbTemp = (byte)buf[index+1] - (byte)40;
                break;
            }
        }
    }
    else //we did not receive answer from ECU
    {
        Serial.print("Error on get Oil Temp from CAN\n");
    }
}

/// @brief Get the Engine Water Temperature
/// @param pbTemp byte pointer of the temp scalled in Deg C
void GetWaterTemp(byte *pbTemp)
{
// SG_ S1_PID_05_EngineCoolantTemp m5 : 31|8@0+ (1,-40) [-40|215] "degC" Vector__XXX
    byte buf[8] = {0x00};
    byte len;
    byte index;

//check if engine rpm and vehicule speed are supported
    buf[0] = PID_ENGINE_COOLANT_TEMP;
    len = 1;

    CAN.sendMsgBuf(CAN_ID_PID_RQT,CAN_STDID,len,buf);
    CAN.readMsgBuf(&len,buf);

    if (len > 0)
    {
        //Seek the result buffer to find the IDs. 
        //The OBD std is not clear if result are sent in the requested order.
        //Since IDs are put before the value, we are looking for them.
        for(index = 0; index < len; index++)
        {
            if (buf[index] == PID_ENGINE_COOLANT_TEMP)
            {
                
                *pbTemp = (byte)buf[index+1] - (byte)40;
                break;
            }
        }
    }
    else //we did not receive answer from ECU
    {
        Serial.print("Error on get Water Temp from CAN\n");
    }

}