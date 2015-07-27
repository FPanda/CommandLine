#ifndef _CMD_LINE_PARSER_PARAMATER_HANDLER_H_
#define _CMD_LINE_PARSER_PARAMATER_HANDLER_H_

#include "Common.h"
#include "tinyxml2.h"

// This function is used to convert input param list from console to the struct we want
bool splitInputParamFromConsole(int argc, char* argv[], PINPUT_CMD* consoleInput, const char* const cmdTag);

// This function aims to process all the option inputed by user
bool processAllTheInputCmd(PINPUT_CMD const consoleInput);


#endif