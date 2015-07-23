#ifndef _CMD_LINE_PARSER_PARAMATER_HANDLER_H_
#define _CMD_LINE_PARSER_PARAMATER_HANDLER_H_

#include "Common.h"

// Define the max size of one input param
#define MAX_INPUT_PARAM_SIZE	1024
// Define the max size of one command
#define MAX_INPUT_CMD_SIZE		64

#define COMMAND_TAG_CHAR		"-"

// This struct is used to store the input param information from console
typedef struct InputParam
{
	std::string strCmd;
	std::list<std::string> paramList;
	InputParam() {strCmd.clear();paramList.clear();}
}INPUT_PARAM, *PINPUT_PARAM;

typedef std::list<INPUT_PARAM> InputParamList;

// This function is used to convert input param list from console to the struct we want
bool SplitInputParamFromConsole(int argc, char* argv[], InputParamList & consoleInput);

// This function aims to process all the option inputed by user
bool ProcessAllTheInputCmd(InputParamList const & consoleInput);


#endif