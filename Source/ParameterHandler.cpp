#include "include/ParameterHandler.h"
// ParameterHandler is used to parser all the arguments input by user

bool splitInputParamFromConsole(int argc, char* argv[], PINPUT_CMD* consoleInput, const char* const cmdTag)
{
	if( consoleInput == NULL ) {
		return false;
	}

	if( *consoleInput != NULL ) {
		return false;
	}

	PINPUT_CMD preCmdNode = NULL;
	PCMD_PARAM preParamNode = NULL;

	// Ignore first element since it's program's name
	for(int i = 1; i < argc; i++)
	{
		if( strlen(argv[i]) > MAX_INPUT_PARAM_SIZE ) {
			printf("Invalid input param, since this param size is too long: %s \r\n", argv[i]);
			return false;
		}
		
		// If this param is command tag char
		if( 0 == memcmp(argv[i], cmdTag, strlen(cmdTag)) )
		{
			PINPUT_CMD pCmdNode = (PINPUT_CMD)malloc(sizeof(INPUT_CMD));
			memset(pCmdNode, 0x00, sizeof(INPUT_CMD));

			memcpy(pCmdNode->cmd, argv[i], strlen(argv[i]));

			if( *consoleInput == NULL ) {
				*consoleInput = pCmdNode;
			}
			else {
				preCmdNode->p_nextCmd = pCmdNode;
			}

			preCmdNode = pCmdNode;
			pCmdNode = NULL;
		}
		else
		{
			// If it's null means it's a invalid unknow meaning string
			if( preCmdNode != NULL )
			{
				PCMD_PARAM pParamNode = (PCMD_PARAM)malloc(sizeof(CMD_PARAM));
				memset(pParamNode, 0x00, sizeof(CMD_PARAM));

				memcpy(pParamNode->param, argv[i], strlen(argv[i]));

				if( preCmdNode->params == NULL ) {
					preCmdNode->params = pParamNode;
				}
				else {
					preParamNode->p_nextParam = pParamNode;
				}

				preParamNode = pParamNode;
				pParamNode = NULL;
			}
		}
	}

	if( *consoleInput == NULL )
	{
		return false;
	}

	return true;
}