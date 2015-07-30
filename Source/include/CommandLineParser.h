#ifndef _COMMAND_LINE_PARSER_H_
#define _COMMAND_LINE_PARSER_H_
#include "Common.h"

#ifdef _WIN32
#define CMDPARSER_EXPORT
#else
#define CMDPARSER_EXPORT    __attribute__ ((visibility("default")))
#endif

// Using this function before doing anything with this dynamic library.
// This is simple mode function
// Input:
//		const char* const commandDelimeter: This will be added before command name you defined in the xml automatically
//
// Output:
//		return 0 if it success, others if it failed
CMDPARSER_EXPORT int initilizeS(const char* const commandDelimeter);

// Using this function before doing anything with this dynamic library.
// This is an automatic mode function
// Input:
//		const char* const filePath: The path to the xml file which user defined
//		const char* const commandDelimeter: This will be added before command name you defined in the xml automatically
//
// Output:
//		return 0 if it success, others if it failed
CMDPARSER_EXPORT int initilizeA(const char* const filePath, const char* const commandDelimeter);

// Using this function to get split command and its params returned by a list
// This is simple mode function
// Input:
//		int argc: input agurment numbers input by main function
//		char* argv[]: input agurments input by main function
//		PINPUT_CMD &consoleInput: A referenece which will return by function contains the split command and its params (this param is not necessary)
//
// Output:
//		return 0 if it success, others if it failed
CMDPARSER_EXPORT  int getAllInputCmdListS(int argc, char* argv[], PINPUT_CMD &consoleInput);

// Using this function to get split command and its params returned by a list
// This is an automatic mode function
// Input:
//		int argc: input agurment numbers input by main function
//		char* argv[]: input agurments input by main function
//
// Output:
//		return 0 if it success, others if it failed
CMDPARSER_EXPORT  int getAllInputCmdListA(int argc, char* argv[]);

// Using this function to regist handle functions by its function name
// Input:
//		const char* functionName: regist handle function name
//		unsigned int functionNameLen: function name size
//		void* funcPointer: the address of handle function
//
// Output:
//		return 0 if it success, others if it failed
CMDPARSER_EXPORT  int registHandlFunctionByName(const char* functionName, unsigned int functionNameLen, void* funcPointer);

// Using this function to process all cmd by the rule defined by xml file user sepecified and input cmd splited by getAllInputCmdList
// This is simple mode function
// Input:
//		PINPUT_CMD const consoleInput: User input command line arguments returned by getAllInputCmdList (this param is not necessary)
//
// Output:
//		return 0 if it success, others if it failed
CMDPARSER_EXPORT int processAllInputCmdS(PINPUT_CMD const consoleInput);

// Using this function to process all cmd by the rule defined by xml file user sepecified and input cmd splited by getAllInputCmdList
// This is an automatic mode function
// Input:
//		void
//
// Output:
//		return 0 if it success, others if it failed
CMDPARSER_EXPORT int processAllInputCmdA(void);

// Using this function before dispatch dynamic library.
// This is simple mode function
// Input:
//		PINPUT_CMD &consoleInput: User input command line arguments returned by getAllInputCmdList
//
// Output:
//		return 0 if it success, others if it failed
CMDPARSER_EXPORT int deinitilizeS(PINPUT_CMD &consoleInput);

// Using this function before dispatch dynamic library.
// This is an automatic mode function
// Input:
//		void
//
// Output:
//		return 0 if it success, others if it failed
CMDPARSER_EXPORT int deinitilizeA(void);

#endif
