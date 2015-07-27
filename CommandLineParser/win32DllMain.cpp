#include "windows.h"
#include "..\Source\include\Common.h"

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// TODO
		break;
	case DLL_PROCESS_DETACH:
		// TODO
		break;
	case DLL_THREAD_ATTACH:
		// TODO
		break;
	case DLL_THREAD_DETACH:
		// TODO
		break;
	default:
		return FALSE;
	}

	return TRUE;
}