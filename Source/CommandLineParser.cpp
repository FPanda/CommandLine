// CommandLineParser is a tool to support intelligent parser command line options.
// It's familiar with OptionParser in Python
//------------------------------------
// VERSION 0.01 FPanda 2015.07.23
//------------------------------------
// This version's purpose is to parser the xml which user defined and parse the command line options based on the xml.
// I consider to use tinyxml-2 to parse xml. I'll finish this part in this weekend.

#include "include/Common.h"
#include "include/ParameterHandler.h"
#include "include/CommandLineParser.h"
#include "include/XmlParser.h"

typedef struct funcName2FuncAddr {
	char funcName[MAX_FUNC_NAME_SIZE];
	CMD_PROC_FUNC func;
	struct funcName2FuncAddr* next_ptr;
}FUNCNAME2FUNCADDR, *PFUNCNAME2FUNCADDR;

static PCMD2PROCFUNC g_Cmd2ProcFuncTbl = NULL;
static char* g_commandDelimeter = NULL;
static PFUNCNAME2FUNCADDR g_funcName2Func = NULL;
static PINPUT_CMD g_consoleInput = NULL;

int initilize( const char* const filePath, const char* const commandDelimeter ) {
	// Initilize command delimeter
	g_commandDelimeter = (char*)malloc((MAX_INPUT_CMD_DELIMETER_SIZE+1)*sizeof(char));
	memset(g_commandDelimeter, 0x00, (MAX_INPUT_CMD_DELIMETER_SIZE+1)*sizeof(char));
	memcpy(g_commandDelimeter, commandDelimeter, (MAX_INPUT_CMD_DELIMETER_SIZE+1)*sizeof(char));
	// To prevent from string overflow
	g_commandDelimeter[MAX_INPUT_CMD_DELIMETER_SIZE] = '\0';

	// Initilize user defined command detail info by xml
	loadXmlFile(filePath);

	parseXmlFile(g_Cmd2ProcFuncTbl, strlen(g_commandDelimeter));

	// Initilize handle function list
	g_funcName2Func = NULL;

	return 0;
}

int getAllInputCmdList(int argc, char* argv[], PINPUT_CMD &consoleInput = g_consoleInput) {
	return splitInputParamFromConsole(argc, argv, consoleInput, g_commandDelimeter);
}

CMD_PROC_FUNC findHandleInTbl(const char* func) {
	for( PFUNCNAME2FUNCADDR ptr = g_funcName2Func; ptr; ptr = ptr->next_ptr ) {
		if( strlen(func) != strlen(ptr->funcName) ) {
			continue;
		}
		if( 0 == memcmp(ptr->funcName, func, strlen(ptr->funcName)) ) {
			return ptr->func;
		}
	}
	return NULL;
}

PCMD2PROCFUNC findCmdInTbl(const char* cmd) {
	for( PCMD2PROCFUNC ptr = g_Cmd2ProcFuncTbl; ptr; ptr = ptr->nextPointer ) {
		if( strlen(cmd) != (strlen(ptr->cmd)+strlen(g_commandDelimeter)) ) {
			continue;
		}
		if( 0 == memcmp(ptr->cmd, cmd+strlen(g_commandDelimeter), strlen(ptr->cmd)) ) {
			return ptr;
		}
	}
	return NULL;
}

int countParamNums(const PCMD_PARAM params) {
	int cnt = 0;
	for( PCMD_PARAM ptr = params; ptr; ptr = ptr->p_nextParam ) {
		cnt++;
	}
	return cnt;
}

int processAllInputCmd(PINPUT_CMD const consoleInput = g_consoleInput) {
	for( PINPUT_CMD ptr = consoleInput; NULL != ptr; ptr = ptr->p_nextCmd ) {
		PCMD2PROCFUNC handler = findCmdInTbl(ptr->cmd);
		if( NULL == handler ) {
			continue;	
		}
		else {
			if( handler->paramNum == countParamNums(ptr->params) ) {
				CMD_PROC_FUNC func = findHandleInTbl(handler->func);

				if( NULL == func ) {
					continue;
				}

				(*func)(ptr->params, NULL, NULL);
			}
		}
	}
	return 0;
}

void freeInputCmdList(PINPUT_CMD &consoleInput) {
	PINPUT_CMD tmpInput = NULL;
	PINPUT_CMD freeInput = NULL;

	if( NULL != consoleInput ) {
		tmpInput = (consoleInput)->p_nextCmd;
		free(consoleInput);

		while(tmpInput != NULL) {
			freeInput = tmpInput;
			tmpInput = tmpInput->p_nextCmd;
			free(freeInput);
		}
	}

	consoleInput = NULL;

	return;
}

void freeRegistFuncList(PFUNCNAME2FUNCADDR &funcTbl) {
	PFUNCNAME2FUNCADDR tmpInput = NULL;
	PFUNCNAME2FUNCADDR freeInput = NULL;

	if( NULL != funcTbl ) {
		tmpInput = (funcTbl)->next_ptr;
		free(funcTbl);

		while(tmpInput != NULL) {
			freeInput = tmpInput;
			tmpInput = tmpInput->next_ptr;
			free(freeInput);
		}
	}

	funcTbl = NULL;
}

int deinitilize(PINPUT_CMD &consoleInput = g_consoleInput) {
	if( NULL != g_commandDelimeter ) {
		free(g_commandDelimeter);
	}

	closeXmlFile(g_Cmd2ProcFuncTbl);

	freeRegistFuncList(g_funcName2Func);

	freeInputCmdList(consoleInput);

	return 0;
}

CMDPARSER_EXPORT int initilizeS( const char* const commandDelimeter ) {
	return initilize(NULL, commandDelimeter);
}

CMDPARSER_EXPORT int initilizeA( const char* const filePath, const char* const commandDelimeter ) {
	return initilize(filePath, commandDelimeter);
}

CMDPARSER_EXPORT  int getAllInputCmdListS(int argc, char* argv[], PINPUT_CMD &consoleInput) {
	return getAllInputCmdList(argc,argv,consoleInput);
}

CMDPARSER_EXPORT  int getAllInputCmdListA(int argc, char* argv[]) {
	return getAllInputCmdList(argc,argv);
}

CMDPARSER_EXPORT int processAllInputCmdS(PINPUT_CMD const consoleInput) {
	return processAllInputCmd(consoleInput);
}

CMDPARSER_EXPORT int processAllInputCmdA(void) {
	return processAllInputCmd();
}

CMDPARSER_EXPORT  int registHandlFunctionByName(const char* functionName, unsigned int functionNameLen, void* funcPointer) {
	if( functionNameLen > MAX_FUNC_NAME_SIZE + 1 ) {
		return -1;
	}

	if( NULL == funcPointer ) {
		return -1;
	}

	PFUNCNAME2FUNCADDR tmpNode = (PFUNCNAME2FUNCADDR)malloc(sizeof(FUNCNAME2FUNCADDR));

	if( NULL == tmpNode ) {
		return -1;
	}

	memset(tmpNode, 0x00, sizeof(FUNCNAME2FUNCADDR));

	memcpy(tmpNode->funcName, functionName, functionNameLen);

	tmpNode->funcName[MAX_FUNC_NAME_SIZE-1] = '\0';

	tmpNode->func = (CMD_PROC_FUNC)(funcPointer);

	if( NULL == g_funcName2Func ) {
		g_funcName2Func = tmpNode;
	}
	else {
		PFUNCNAME2FUNCADDR prePtr = NULL;
		for(PFUNCNAME2FUNCADDR ptr = g_funcName2Func; ptr; ptr=ptr->next_ptr ) {
			prePtr = ptr;
		}
		
		if( NULL != prePtr ) {
			prePtr->next_ptr = tmpNode;
		}
	}

	return 0;
};

CMDPARSER_EXPORT int deinitilizeS(PINPUT_CMD &consoleInput) {
	return deinitilize(consoleInput);
}

CMDPARSER_EXPORT int deinitilizeA(void) {
	return deinitilize();
}
