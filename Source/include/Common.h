#ifndef _COMMAND_LINE_PARSER_COMMON_H_
#define _COMMAND_LINE_PARSER_COMMON_H_

#include "memory.h"
#include "stdio.h"

// Macros
#define MAXCMDLENGTH					1024
// Define the max size of one input param
#define MAX_INPUT_PARAM_SIZE			1024
// Define the max size of one command
#define MAX_INPUT_CMD_SIZE				64
// Define the max size of a command delimeter
#define MAX_INPUT_CMD_DELIMETER_SIZE	2
// Define the max size of error message
#define MAX_ERROR_MSG_LENGTH			512

// This struct is used to store parameters of one command
typedef struct CmdParam {
	// One parameter information
	char param[MAX_INPUT_PARAM_SIZE];
	// Point to next parameter since one command may contain several parameters
	struct CmdParam* p_nextParam;
	CmdParam(void):p_nextParam(NULL) {memset(param, 0x00, MAX_INPUT_PARAM_SIZE*sizeof(char));}
}CMD_PARAM,*PCMD_PARAM;

// This struct is used to store the input command information from console
typedef struct InputCmd {
	// One command information
	char cmd[MAX_INPUT_CMD_SIZE];
	// Header of a list of parameters
	PCMD_PARAM params;
	// Point to next command in the list
	struct InputCmd* p_nextCmd;
	InputCmd(void):params(NULL),p_nextCmd(NULL) {memset(cmd, 0x00, MAX_INPUT_CMD_SIZE*sizeof(char));}
}INPUT_CMD, *PINPUT_CMD;

// This is defined for cmd process function
typedef bool (*CMD_PROC_FUNC)(PCMD_PARAM const inputParam, void* reserved, char* errMsg);

#endif
