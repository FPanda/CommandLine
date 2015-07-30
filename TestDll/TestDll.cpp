// TestDll.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Source/include/Common.h"
#include "../Source/include/CommandLineParser.h"

#pragma comment(lib, "../Debug/CommandLineParser.lib")

bool testFunc(PCMD_PARAM const inputParam, void* reserved, char* errMsg) {
	return false;
}

int main(int argc, char* argv[])
{
	const int testArgc = 5;
	char* testArgv[testArgc] = {0};
	testArgv[0] = "-f";
	testArgv[1] = "-f";
	testArgv[2] = "test";
	testArgv[3] = "my test";
	testArgv[4] = "-m";
	initilizeA("..\\Source\\test.xml","-");
	registHandlFunctionByName("testFunc",sizeof("testFunc"), testFunc);
	getAllInputCmdListA(testArgc, testArgv);
	processAllInputCmdA();
	deinitilizeA();
	return 0;
}

