#include "include\ParameterHandler.h"

// This is defined for cmd process function
typedef bool (*CMD_PROC_FUNC)(std::list<std::string> const & inputParam, std::string & errMsg);

// This is defined for cmd and its process function
typedef struct Cmd2ProcFunc
{
	char cmd[MAX_INPUT_CMD_SIZE];
	CMD_PROC_FUNC pFunc;
}CMD2PROCFUNC;

// pre define the proc function here
bool helpFunc(std::list<std::string> const & inputParam, std::string & errMsg);
bool uncompressFunc(std::list<std::string> const & inputParam, std::string & errMsg);

Cmd2ProcFunc const g_Cmd2ProcFuncTbl[] =
{
	{"", helpFunc},
	{"-h", helpFunc},
	{"-help", helpFunc},
	{"-f", uncompressFunc},
};

bool SplitInputParamFromConsole(int argc, char* argv[], InputParamList & consoleInput)
{
	PINPUT_PARAM pInputParam = NULL;
	INPUT_PARAM tempParam;
	const std::string strCommandTag = COMMAND_TAG_CHAR;

	// Ignore first element since it's program's name
	for(int i = 1; i < argc; i++)
	{
		if( strlen(argv[i]) > MAX_INPUT_PARAM_SIZE ) {
			printf("Invalid input param, since this param size is too long: %s \r\n", argv[i]);
			return false;
		}
		
		// If this param is command tag char
		if( 0 == memcmp(argv[i], strCommandTag.c_str(), strCommandTag.size()) )
		{
			if( pInputParam != NULL )
			{
				consoleInput.push_back(*pInputParam);
			}

			tempParam = InputParam();

			pInputParam = &tempParam;

			pInputParam->strCmd.assign(argv[i]);
		}
		else
		{
			if( pInputParam != NULL )
			{
				pInputParam->paramList.push_back(std::string(argv[i]));
			}
		}
	}

	if( pInputParam != NULL )
	{
		consoleInput.push_back(*pInputParam);
	}

	if( consoleInput.empty() )
	{
		printf("Unknow option.\r\nTry VIPackageHandler.exe -help/-h for more information\r\n");
		return false;
	}

	return true;
}

// This function is used to find the cmd and its proccess function in the pre defined table
CMD_PROC_FUNC FindInCmd2ProcFuncTbl(std::string const & cmd)
{
	for(int i = 0; i < sizeof(g_Cmd2ProcFuncTbl); ++i)
	{
		if( 0 == memcmp(g_Cmd2ProcFuncTbl[i].cmd,cmd.c_str(),cmd.size()) )
		{
			return g_Cmd2ProcFuncTbl[i].pFunc;
		}
	}

	return NULL;
}

// Process all the option inputed by the user, order by the input order
bool ProcessAllTheInputCmd(InputParamList const & consoleInput)
{
	CMD_PROC_FUNC pProcFunc = NULL;
	std::string errMsg;

	for( InputParamList::const_iterator iter = consoleInput.begin(); iter != consoleInput.end(); ++iter )
	{
		pProcFunc = FindInCmd2ProcFuncTbl(iter->strCmd);

		if( pProcFunc == NULL )
		{
			printf("Unknow option: %s\r\nTry VIPackageHandler.exe -help/-h for more information\r\n", iter->strCmd.c_str());
			return false;
		}

		if( !(*pProcFunc)(iter->paramList,errMsg) )
		{
			printf("%s\r\n",errMsg.c_str());
			return false;
		}
	}

	return true;
}

// Main implement of help option
bool helpFunc(std::list<std::string> const & inputParam, std::string & errMsg)
{
	printf("usage: VIPackageHandler.exe [option] [arg]\r\n");
	printf("Options and arguments:\r\n");
	printf("-f [source vi package file path] [dest uncompress file path]\r\n");
	printf("This option is used to uncompress a vip file from src file path to dst file path\r\n");
	printf("eg: VIPackageHandler.exe -f \"C:\\\" \"D:\\\"\r\n");
	return true;
}

bool uncompressFunc(std::list<std::string> const & inputParam, std::string & errMsg)
{
	return true;
}
