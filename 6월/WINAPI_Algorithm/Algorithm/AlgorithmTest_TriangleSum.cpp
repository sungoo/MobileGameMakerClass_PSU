#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> Triang;
vector<vector<int>> cache = vector<vector<int>>(501, vector<int>(501, -1));

int DP_BottomUp(int posY, int posX)
{
    //기저사항
    if (posY == 0 && posX == 0)
    {
        return Triang[0][0];
    }
    if (posY < 0 || posX<0 || posX>posY)
        return -1;

    //메모이제이션
    int& ref = cache[posY][posX];
    if (ref != -1)
        return ref;

    //풀이
    return ref = max(DP_BottomUp(posY - 1, posX), DP_BottomUp(posY - 1, posX - 1)) + Triang[posY][posX];
}

int DP_TopDown(int posY, int posX)
{
    if (posY == Triang.size() - 1)
        return Triang[posY][posX];

    int& ref = cache[posY][posX];

    if (ref != -1)
        return ref;

    return ref = max(DP_TopDown(posY + 1, posX), DP_TopDown(posY + 1, posX + 1))
        + Triang[posY][posX];
}

int solution(vector<vector<int>> triangle) {
    Triang = triangle;

    int y = triangle.size() - 1;
    int answer = 0;

    for (int x = 0; x <= y; x++)
    {
        answer = max(answer, DP_BottomUp(y, x));
    }

    //answer = DP_TopDown(0, 0);

    return answer;
}