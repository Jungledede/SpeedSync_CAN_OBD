// Author : Jungledede
// mainHeader.h: one big header to rules them all
// history:
// V 1.0.0  2020/06/06 Jungledede   Init


#ifndef _MAINHEADER_H_
#define _MAINHEADER_H_

#include <Arduino.h>

//Not need here, 'cause all ready call in the main can lib. Just need to have the lib src files available in the project folder.
//#include "SPI.h" 

//#include "CurieBLE.h"

#include "can-serial.h"
#include "canTool.h"


#define CAN_2515
// #define CAN_2518FD

// Set SPI CS Pin according to your hardware

#if defined(SEEED_WIO_TERMINAL) && defined(CAN_2518FD)
// For Wio Terminal w/ MCP2518FD RPi Hat：
// Channel 0 SPI_CS Pin: BCM 8
// Channel 1 SPI_CS Pin: BCM 7
// Interupt Pin: BCM25
const int SPI_CS_PIN  = BCM8;
const int CAN_INT_PIN = BCM25;
#else

// For Arduino MCP2515 Hat:
// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;
const int CAN_INT_PIN = 2;
#endif


#ifdef CAN_2518FD
#include "mcp2518fd_can.h"
mcp2518fd CAN(SPI_CS_PIN); // Set CS pin
#endif

#ifdef CAN_2515
#include "mcp2515_can.h"
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
#endif


unsigned char PID_INPUT;
unsigned char getPid;

bool fInitOK;
bool fTempWaterAvailable;
bool fTempOilAvailable;
bool fSpeedEngineAvailable;
bool fSpeedVehileAvailable;

#endif