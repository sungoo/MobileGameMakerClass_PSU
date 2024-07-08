#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <time.h>
#include <stack>
#include <queue>

using namespace std;

#include "Types.h"

// FrameWork
#include "Framework/Vector2.h"
#include "Framework/Line.h"
#include "Framework/Collider.h"
#include "Framework/RectCollider.h"
#include "Framework/CircleCollider.h"

// Program
#include "Program/Program.h"

// Scene
#include "Scene/Scene.h"
#include "Scene/PaintScene.h"

extern Vector2 mousePos;
extern HWND hWnd;