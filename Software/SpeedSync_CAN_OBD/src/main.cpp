#include "mainHeader.h"

void setup()
{
  // put your setup code here, to run once:

// Init flags 
  fInitOK = false;
  fTempWaterAvailable = false;
  fTempOilAvailable = false;
  fSpeedEngineAvailable = false;
  fSpeedVehileAvailable = false;
  
//start the serial com for debug and futur usage, like retreive the DTC or just plug the PC while driving for logging, but don't wait for it to run in stand alone.
  Serial.begin(115200);
  Serial.print("Booting Up, hello world, this will be fun, or not..\n");

// init CAN hardware by setting mask
  set_mask_filt();
  Serial.print("Set Mask done\n");

//check if engine rpm and vehicule speed are supported. (check for oil/water temps ad uses it later if available)
  if (checkPID())
  {
    fInitOK = true;

  }
  else
  {
    fInitOK = false;
  }

//check for DTC
  checkDTC();

}



void loop()
{
  if (fInitOK)
  {
  // put your main code here, to run repeatedly:

  //read ice rpm and vehicule speed
  // request both PID in the same message to gain perf (as indicated in std page 40.)
  //compute ratio
  //check ratio from table if match
  //display matching result
  //de temps en temps ajouter la demande pour température eau/huile

  }
}