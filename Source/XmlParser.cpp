#include "include/Common.h"
#include "include/tinyxml2.h"

using namespace tinyxml2;

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

int ParseXmlFile(void) {
	XMLError err = XML_NO_ERROR;

	const XMLElement* handler = NULL;

	// First element will be [arguments]
	// It doesn't contain any text
	handler = g_xmlDoc->RootElement();

	if( NULL == handler ) {
		return -1;
	}

	return err;
}