#include <iostream>
#include <vector>
#define MAPX 5
#define MAPY 5
using namespace std;

struct Vec2
{
    int y;
    int x;

    Vec2(int y, int x):y(y), x(x){}

    Vec2 operator+(const Vec2& other) {
        return Vec2(y + other.y, x + other.x);
    }

    bool operator==(const Vec2& other) {
        return y == other.y && x == other.x;
    }
    bool operator!=(const Vec2& other) {
        return y != other.y || x != other.x;
    }
};

Vec2 frontPos[4] = {
    Vec2{1, 0},
    Vec2{0, 1 },
    Vec2{-1,0},
    Vec2{0,-1 }
};

vector<vector<int> > Maps =
vector<vector<int>>(MAPY, vector<int>(MAPX, 0));

vector<vector<bool>> discovered =
vector<vector<bool>>(MAPY, vector<bool>(MAPX, false));

vector<vector<Vec2>> parent =
vector<vector<Vec2>>(MAPY, vector<Vec2>(MAPX, Vec2(-1, -1)));

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

void BFS(vector<vector<int> > maps, Vec2 start, Vec2 end) {
    discovered[start.y][start.x] = true;
    parent[start.y][start.x] = start;

    vector<Vec2> q;
    q.push_back(start);
    int pop = 0;

    while (true)
    {
        if (pop >= q.size())break;

        Vec2 here = q[pop];
        pop++;

        //이동한 칸이 도착지점인가
        if (here == end) {
            break;
        }

        for (int i = 0; i < 4; i++) {
            Vec2 there = here + frontPos[i];
            //이동한 칸이 범위 밖이면 다시 돌리기
            if ((there.y < 0 || there.y >= MAPY) || (there.x < 0 || there.x >= MAPX))
                continue;
            //이동한 칸이 이동 가능인가
            if (maps[there.y][there.x] == 0)
                continue;//이동불가

            //이동한 칸이 이미 들렀던 칸인가
            if (discovered[there.y][there.x])
                continue;


            q.push_back(there);
            discovered[there.y][there.x] = true;
            parent[there.y][there.x] = here;
            
        }
    }
}

int solution(vector<vector<int> > maps)
{
    //이동거리 최솟값 구하기
    //막혀있으면 -1 리턴
    int answer = 0;
    Vec2 start = Vec2(0, 0);
    Vec2 end = Vec2(maps.size()-1, maps[0].size()-1);

    BFS(maps, start, end);

    bool found = false;
    Vec2 acent = end;

    if (parent[acent.y][acent.x] == Vec2(-1, -1))
        answer = -1;
    else {
        while (true)
        {
            answer++;
            if (found) break;

            acent = parent[acent.y][acent.x];
            if (acent == start)
                found = true;
        }
    }

    return answer;
}

int main() {
    CreateMaps();

    int answer = solution(Maps);

    cout << answer << endl;
}