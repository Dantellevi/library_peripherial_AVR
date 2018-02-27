/*
 * MCP4921.h
 *
 * Created: 11.01.2018 17:57:31
 *  Author: Dante_L_Levi
 */ 


#ifndef MCP4921_H_
#define MCP4921_H_


#include "Main.h"


unsigned int MCP_4921_Convert_Data(float X, float Vref);
void MCP4921_Sent_Data(unsigned int h);


#endif /* MCP4921_H_ */