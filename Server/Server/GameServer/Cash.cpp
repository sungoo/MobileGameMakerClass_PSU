#include "pch.h"
#include "AccountManager.h"
#include "UserManager.h"

//캐시
// - CPU에 있는 임시 저장 공간
// - 코어 마다 있다(L1, L2), 아닌 것도 있다.(L3)
// 
// - 캐시 철학
// -- Temporal Locality : 시간적 지역 -> '방금' 본 메모리에서 또 다시 접근할 일이 생길 것 같다.
// --  Spatial Locality : 공간적 지역 -> 봤던 메모리 '주변'에서 또 접근할 일이 생길 것 같다.
// => 메모리 탐색 최소화 전략
//

int32 buffer[10000][10000];

int main()
{
	memset(buffer, 0, sizeof(buffer));

	{
		uint32 start = GetTickCount64();

		int64 sum = 0;
		for (int32 i = 0; i < 10000; i++)
		{
			for (int32 j = 0; j < 10000; j++)
			{
				//일렬로 확인
				sum += buffer[i][j];
			}
		}

		uint32 end = GetTickCount64();

		cout << "Elipsed Time : " << end - start << endl;
	}

	{
		uint32 start = GetTickCount64();

		int64 sum = 0;
		for (int32 i = 0; i < 10000; i++)
		{
			for (int32 j = 0; j < 10000; j++)
			{
				//왔다갔다 확인
				sum += buffer[j][i];
			}
		}

		uint32 end = GetTickCount64();

		cout << "Elipsed Time : " << end - start << endl;
	}
	return 0;
}