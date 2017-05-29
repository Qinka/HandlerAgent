// HandleAgent.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define HREAL_EXE_EXTENSION ".hreal.exe"
#define HREAL_EXE_EXTENSION_LENGTH (strlen(HREAL_EXE_EXTENSION)+1)


int  main(int argc, char *argv[]) {
	char *realname;
	realname = strrchr(argv[0], 0x5C);
	for (int i = 0; i<strlen(realname); i++)
		realname[i] = realname[i + 1];
	printf_s("%s",realname);
	if (strcmp(realname, "HandlerAgent.exe")) {
		// Create new process
		*(strrchr(realname, 0x2E)) = '\0';
		int otherlen = 0;
		for (int i = 1;i < argc;++i)
			otherlen += strlen(argv[i]) + 2;
		int reallen = strlen(realname) + HREAL_EXE_EXTENSION_LENGTH + otherlen;
		char *realprogname = new char[reallen];
		TCHAR *realprognameA = new TCHAR[reallen];
		strcpy_s(realprogname, strlen(realname)+1, realname);
		strcpy_s(&realprogname[strlen(realname)], HREAL_EXE_EXTENSION_LENGTH, HREAL_EXE_EXTENSION);
		for (int i = 1;i < argc;++i) {
			strcat_s(realprogname, reallen, " ");
			strcat_s(realprogname, reallen, argv[i]);
		}
		int tmplen = MultiByteToWideChar(CP_ACP, 0, realprogname, strlen(realprogname) + 1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, realprogname, strlen(realprogname) + 1, realprognameA, tmplen);
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		si.lpReserved = NULL;
		si.lpDesktop = NULL;
		si.lpTitle = NULL;
		si.dwX = 0;
		si.dwY = 0;
		si.dwXSize = 0;
		si.dwYSize = 0;
		si.dwXCountChars = 500;
		si.dwYCountChars = 500;
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_HIDE;
		si.cbReserved2 = 0;
		si.lpReserved2 = NULL;
		si.hStdInput = stdin;
		si.hStdOutput = stdout;
		si.hStdError = stderr;
		ZeroMemory(&pi, sizeof(pi));
		bool is = CreateProcess(NULL, realprognameA, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		if (is) {
			WaitForSingleObject(pi.hProcess, INFINITE);
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}
		delete realprogname;
	}
    return 0;
}

