// TestDll.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Source/include/Common.h"
#include "../Source/include/CommandLineParser.h"

#pragma comment(lib, "../Debug/CommandLineParser.lib")

int main(int argc, char* argv[])
{
	PINPUT_CMD input = NULL;
	initilize(NULL,"-");
	getAllInputCmdList(argc, argv, &input);
	return 0;
}

