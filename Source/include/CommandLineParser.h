#ifndef _COMMAND_LINE_PARSER_H_
#define _COMMAND_LINE_PARSER_H_
#include "include\Common.h"

// Using this function before doing anything with this dynamic library.
// Input:
//		const char* const filePath: The path to the xml file which user defined
//		const char* const commandDelimeter: This will be added before command name you defined in the xml automatically
//
// Output:
//		return 0 if it success, others if it failed
int __stdcall Initilize(const char* const filePath, const char* const commandDelimeter);


// Using this function before dispatch dynamic library.
// Input:
//		void
//
// Output:
//		return 0 if it success, others if it failed
int __stdcall Deinitilize(void);

#endif