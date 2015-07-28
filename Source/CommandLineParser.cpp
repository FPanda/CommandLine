// CommandLineParser is a tool to support intelligent parser command line options.
// It's familiar with OptionParser in Python
//------------------------------------
// VERSION 0.01 FPanda 2015.07.23
//------------------------------------
// This version's purpose is to parser the xml which user defined and parse the command line options based on the xml.
// I consider to use tinyxml-2 to parse xml. I'll finish this part in this weekend.

#include "include/common.h"
#include "include/ParameterHandler.h"
#include "include/CommandLineParser.h"

static char* g_commandDelimeter = NULL;

CMDPARSER_EXPORT int initilize( const char* const filePath, const char* const commandDelimeter ) {
	g_commandDelimeter = (char*)malloc((MAX_INPUT_CMD_DELIMETER_SIZE+1)*sizeof(char));
	memset(g_commandDelimeter, 0x00, (MAX_INPUT_CMD_DELIMETER_SIZE+1)*sizeof(char));
	memcpy(g_commandDelimeter, commandDelimeter, (MAX_INPUT_CMD_DELIMETER_SIZE+1)*sizeof(char));
	// To prevent from string overflow
	g_commandDelimeter[MAX_INPUT_CMD_DELIMETER_SIZE] = '\0';

	return 0;
}

CMDPARSER_EXPORT  int getAllInputCmdList(int argc, char* argv[], PINPUT_CMD* consoleInput) {
	return splitInputParamFromConsole(argc, argv, consoleInput, g_commandDelimeter);
}

CMDPARSER_EXPORT  int deinitilize(PINPUT_CMD* consoleInput) {
	if( NULL != g_commandDelimeter ) {
		free(g_commandDelimeter);
	}

	PINPUT_CMD tmpInput = NULL;
	PINPUT_CMD freeInput = NULL;

	if( NULL != *consoleInput ) {
		tmpInput = (*consoleInput)->p_nextCmd;
		free(consoleInput);

		while(tmpInput != NULL) {
			freeInput = tmpInput;
			tmpInput = tmpInput->p_nextCmd;
			free(freeInput);
		}
	}

	*consoleInput = NULL;

	return 0;
}
