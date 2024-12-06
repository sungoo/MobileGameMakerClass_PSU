#pragma once

#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#pragma comment(lib, "ServerCore\\Debug\\ServerCore.lib")
//#pragma comment(lib, "Protobuf\\Debug\\ServerCore.lib")
#else
#pragma comment(lib, "ServerCore\\Release\\ServerCore.lib")
//#pragma comment(lib, "Protobuf\\Release\\ServerCore.lib")
#endif // _DEBUG


#include "CorePch.h"
