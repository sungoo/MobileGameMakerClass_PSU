#include <iostream>
#include <vector>
#define MAPX 5
#define MAPY 5
using namespace std;

vector<vector<int> > Maps =
vector<vector<int>>(MAPY, vector<int>(MAPX, 0));

vector<vector<bool>>(MAPY, vector<bool>(MAPX, false));

void CreateMaps() {
    Maps[0][0] = 1;
    //Maps[0][1] = 1;
    Maps[0][2] = 1;
    Maps[0][3] = 1;
    Maps[0][4] = 1;

    Maps[1][0] = 1;
    //Maps[1][1] = 1;
    Maps[1][2] = 1;
    //Maps[1][3] = 1;
    Maps[1][4] = 1;

    Maps[2][0] = 1;
    //Maps[2][1] = 1;
    Maps[2][2] = 1;
    Maps[2][3] = 1;
    Maps[2][4] = 1;

    Maps[3][0] = 1;
    Maps[3][1] = 1;
    Maps[3][2] = 1;
    //Maps[3][3] = 1;
    Maps[3][4] = 1;

    //Maps[4][0] = 1;
    //Maps[4][1] = 1;
    //Maps[4][2] = 1;
    //Maps[4][3] = 1;
    Maps[4][4] = 1;
}

int solution(vector<vector<int> > maps)
{
    //이동거리 최솟값 구하기
    //막혀있으면 -1 리턴

    int answer = 0;
    return answer;
}

int main() {
    CreateMaps();

    cout << solution(Maps) << endl;
}