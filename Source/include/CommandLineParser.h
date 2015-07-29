#ifndef _COMMAND_LINE_PARSER_H_
#define _COMMAND_LINE_PARSER_H_
#include "Common.h"

#ifdef _WIN32
#define CMDPARSER_EXPORT
#else
#define CMDPARSER_EXPORT    __attribute__ ((visibility("default")))
#endif

// Using this function before doing anything with this dynamic library.
// Input:
//		const char* const filePath: The path to the xml file which user defined
//		const char* const commandDelimeter: This will be added before command name you defined in the xml automatically
//
// Output:
//		return 0 if it success, others if it failed
CMDPARSER_EXPORT int initilize(const char* const filePath, const char* const commandDelimeter);


// Using this function to get split command and its params returned by a list
// Input:
//		int argc: input agurment numbers input by main function
//		char* argv[]: input agurments input by main function
//		PINPUT_CMD &consoleInput: A referenece which will return by function contains the split command and its params
//
// Output:
//		return 0 if it success, others if it failed
CMDPARSER_EXPORT  int getAllInputCmdList(int argc, char* argv[], PINPUT_CMD &consoleInput);

// Using this function to process all cmd by the rule defined by xml file user sepecified and input cmd splited by getAllInputCmdList
// Input:
//		PINPUT_CMD const consoleInput: User input command line arguments returned by getAllInputCmdList
//
// Output:
//		return 0 if it success, others if it failed
CMDPARSER_EXPORT int processAllInputCmd(PINPUT_CMD const consoleInput);


// Using this function before dispatch dynamic library.
// Input:
//		PINPUT_CMD &consoleInput: User input command line arguments returned by getAllInputCmdList
//
// Output:
//		return 0 if it success, others if it failed
CMDPARSER_EXPORT int deinitilize(PINPUT_CMD &consoleInput);

#endif
