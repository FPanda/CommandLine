#include "include/Common.h"
#include "include/tinyxml2.h"
#include "include/XmlParser.h"

using namespace tinyxml2;

#define ROOT_ELEMENT_NAME		"arguments"
#define MAIN_NODE_NAME			"command"
#define NODE_CMD_NAME			"commandname"
#define NODE_PARAM_NUM_NAME		"parameternumber"
#define NODE_HANDLE_FUNC_NAME	"handler"
#define NODE_DESCRIP_NAME		"description"

XMLDocument* g_xmlDoc = NULL;

int loadXmlFile(const char* const filePath) {
	XMLError err = XML_NO_ERROR;

	g_xmlDoc = new XMLDocument();

	if( NULL == g_xmlDoc ) {
		return -1;
	}

	err = g_xmlDoc->LoadFile(filePath);

	return err;
}

int parseCommandStructure(PCMD2PROCFUNC &cmdTbl, const XMLElement* hCommandNode) {
	const XMLElement* name = hCommandNode->FirstChildElement();

	if( NULL == name ) {
		return -1;
	}

	if( 0 != memcmp(name->Value(), NODE_CMD_NAME, strlen(NODE_CMD_NAME)) ) {
		// Unknow command name element
		return -1;
	}
	
	const char* cmd = name->GetText();

	if( strlen(cmd) + 1 > MAX_INPUT_CMD_SIZE ) {
		return -1;
	}

	const XMLElement* paramNum = name->NextSiblingElement();

	if( NULL == paramNum ) {
		return -1;
	}

	if( 0 != memcmp(paramNum->Value(), NODE_PARAM_NUM_NAME, strlen(NODE_PARAM_NUM_NAME)) ) {
		// Unknow param name element
		return -1;
	}

	int iParamNum = 0;

	if( 0 != paramNum->QueryIntText(&iParamNum) ) {
		return -1;
	}

	const XMLElement* funcName = paramNum->NextSiblingElement();

	if( NULL == funcName ) {
		return -1;
	}

	if( 0 != memcmp(funcName->Value(), NODE_HANDLE_FUNC_NAME, strlen(NODE_HANDLE_FUNC_NAME)) ) {
		// Unknow handle name element
		return -1;
	}

	const char* func = funcName->GetText();

	if( strlen(cmd) + 1 > MAX_FUNC_NAME_SIZE ) {
		return -1;
	}

	const XMLElement* description = funcName->NextSiblingElement();

	if( NULL == description ) {
		return -1;
	}

	if( 0 != memcmp(description->Value(), NODE_DESCRIP_NAME, strlen(NODE_DESCRIP_NAME)) ) {
		// Unknow description name element
		return -1;
	}

	const char* decb = description->GetText();

	if( strlen(decb) + 1 > MAX_DESCRIB_SIZE ) {
		return -1;
	}

	PCMD2PROCFUNC pCmd2Func = (PCMD2PROCFUNC)malloc(sizeof(CMD2PROCFUNC));

	*pCmd2Func = CMD2PROCFUNC();

	if( pCmd2Func == NULL ) {
		return -1;
	}

	memcpy(pCmd2Func->cmd, cmd, strlen(cmd));

	pCmd2Func->paramNum = iParamNum;

	memcpy(pCmd2Func->func, func, strlen(func));

	memcpy(pCmd2Func->decb, decb, strlen(decb));

	if( cmdTbl == NULL ) {
		cmdTbl = pCmd2Func;
	}
	else {
		cmdTbl->nextPointer = pCmd2Func;

		cmdTbl = pCmd2Func;
	}

	return 0;
}

int parseXmlFile(PCMD2PROCFUNC &cmdTbl) {
	int err = XML_NO_ERROR;

	const XMLElement* handler = NULL;

	// First element will be [arguments]
	// It doesn't contain any text
	handler = g_xmlDoc->RootElement();

	if( NULL == handler ) {
		return -1;
	}

	if( 0 != memcmp(handler->Value(), ROOT_ELEMENT_NAME, strlen(ROOT_ELEMENT_NAME)) ) {
		// Unknow root element
		return -1;
	}

	const XMLElement* hCommandNode = handler->FirstChildElement();

	if( NULL == hCommandNode ) {
		return -1;
	}

	if( 0 != memcmp(hCommandNode->Value(), MAIN_NODE_NAME, strlen(MAIN_NODE_NAME)) ) {
		// Unknow command element
		return -1;
	}

	err = parseCommandStructure(cmdTbl,hCommandNode);

	PCMD2PROCFUNC tmpTblPointer = NULL;

	if( 0 == err ) {
		tmpTblPointer = cmdTbl;
	}
	else {
		return -1;
	}

	hCommandNode = hCommandNode->NextSiblingElement();

	while( NULL != hCommandNode ) {
		if( 0 != memcmp(hCommandNode->Value(), MAIN_NODE_NAME, strlen(MAIN_NODE_NAME)) ) {
			// Unknow command element
			hCommandNode = NULL;
			continue;
		}
		
		if( 0 != parseCommandStructure(tmpTblPointer, hCommandNode) ) {
			hCommandNode = NULL;
			continue;			
		}

		hCommandNode = hCommandNode->NextSiblingElement();
	};

	return err;
}

int closeXmlFile(PCMD2PROCFUNC &cmdTbl) {
	PCMD2PROCFUNC tmpInput = NULL;
	PCMD2PROCFUNC freeInput = NULL;

	if( NULL != cmdTbl ) {
		tmpInput = cmdTbl->nextPointer;
		free(cmdTbl);

		while(tmpInput != NULL) {
			freeInput = tmpInput;
			tmpInput = tmpInput->nextPointer;
			free(freeInput);
		}
	}

	cmdTbl = NULL;
	return 0;
}
