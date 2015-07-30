#ifndef _CMD_LINE_PARSER_XML_PARSER_H_
#define _CMD_LINE_PARSER_XML_PARSER_H_

// This is defined for cmd and its process function
typedef struct Cmd2ProcFunc
{
	char cmd[MAX_INPUT_CMD_SIZE];
	char decb[MAX_DESCRIB_SIZE];
	char func[MAX_FUNC_NAME_SIZE];
	int paramNum;
	struct Cmd2ProcFunc* nextPointer;
	Cmd2ProcFunc(void):paramNum(0),nextPointer(NULL)
	{
		memset(cmd,0x00,MAX_INPUT_CMD_SIZE*sizeof(char));
		memset(decb,0x00,MAX_DESCRIB_SIZE*sizeof(char));
		memset(func,0x00,MAX_FUNC_NAME_SIZE*sizeof(char));
	}
}CMD2PROCFUNC, *PCMD2PROCFUNC;

int loadXmlFile(const char* const filePath);

int parseXmlFile(PCMD2PROCFUNC &cmdTbl, int delimeterSize);

int closeXmlFile(PCMD2PROCFUNC &cmdTbl);

#endif
