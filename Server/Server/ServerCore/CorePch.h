#pragma once

#include "Types.h"
#include <algorithm>
#include <future>

#include <Windows.h>
#include <iostream>

using namespace std;

//Network
#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "SocketUtility.h"

//CORE
#include "CoreTLS.h"
#include "CoreGlobal.h"
#include "CoreMacro.h"
#include "MyContainer.h"

//Multi Thread
#include "ThreadManager.h"
#include "Lock.h"

//Memory
#include "Memory.h"
#include "MemoryPool.h"

// MyNetwork
#include "SendBuffer.h"
#include "Session.h"