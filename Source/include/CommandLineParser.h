#ifndef _COMMAND_LINE_PARSER_H_
#define _COMMAND_LINE_PARSER_H_
#include "include\Common.h"

// Using this function before doing anything with this dynamic library.
// Input:
//		char * filePath: The path to the xml file which user defined
//
// Output:
//		return 0 if it success, others if it failed
int __stdcall Initilize(char* filePath = NULL);


// Using this function before dispatch dynamic library.
// Input:
//		void
//
// Output:
//		return 0 if it success, others if it failed
int __stdcall Deinitilize(void);

#endif