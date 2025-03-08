#pragma once

#define DllImport   __declspec( dllimport )
#include <Windows.h>
#include "Inforluckybox.h"
#include <iostream>
#include "dllmain.h"
#include <time.h>
#include <Windows.h>
#include <tchar.h>
#include <WS2tcpip.h>
#include "ConnectSqlServer.h"
#include "Log.h"


DllImport BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwreason, LPVOID lpRevered);

DWORD WINAPI MainThread(LPVOID param);