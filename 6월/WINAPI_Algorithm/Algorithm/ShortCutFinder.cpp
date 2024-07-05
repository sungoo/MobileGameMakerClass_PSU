#include <iostream>
#include<vector>
using namespace std;

struct position {
    int _y = 0;
    int _x = 0;

    position(int y, int x) {
        _y = y;
        _x = x;
    }

    bool operator==(const position& other) {
        return this->_y == other._y && this->_x == other._x;
    }
    bool operator!=(const position& other) {
        return !(this->_y == other._y && this->_x == other._x);
    }
};

position errorPos(-1, -1);

int solution(vector<vector<int> > maps)
{
    int mapHeight = maps.size();
    int mapWidth = maps[0].size();
    int N = mapHeight * mapWidth;

    position start(0, 0);

    vector<vector<bool>> discovered(
        mapHeight,
        vector<bool>(mapWidth, false)
    );
    vector<vector<position>> parent(
        mapHeight,
        vector<position>(mapWidth, errorPos)
    );
    vector<position> que;
    que.push_back(start);
    int answer = 0;
    //BFS
    discovered[0][0] = true;
    int pop = 0;

    while (true) {
        if (pop >= que.size()) break;

        position here = que[pop];
        pop++;

        cout << here._x << ", " << here._y << " visited" << endl;

        for (int thereY = 0; thereY < mapHeight-1; thereY++) {
            for (int thereX = 0; thereX < mapWidth-1; thereX++) {
                if (maps[thereY][thereX] == 0 || 
                    maps[thereY+1][thereX] == 0 || 
                    maps[thereY][thereX+1] == 0)
                    continue;
                if (discovered[thereY][thereX] == true || 
                    discovered[thereY + 1][thereX] == true || 
                    discovered[thereY][thereX + 1] == true)
                    continue;

                position newPos(thereY, thereX);

                que.push_back(newPos);
                discovered[thereY][thereX] = true;
                parent[thereY][thereX] = here;
                cout << thereY << ", " << thereX << "discovered!" << endl;
            }
        }
    }
    //EdgeCount

    bool found = false;
    int edges = 0;
    position goalPos(mapHeight - 1, mapWidth - 1);
    position acent(mapHeight - 1, mapWidth - 1);

    if (parent[acent._y][acent._x] == errorPos) {
        edges = -1;
    }
    else {
        while (true) {
            if (found) break;

            acent = parent[acent._y][acent._x];

            if (acent == position(4, 4))
                found = true;
            edges++;
        }
    }
    answer = edges;

    return answer;
}

int main() {

    vector<vector<int>> maps(5, vector<int>(5, 0));
    maps[0][0] = 1;
    //maps[1][0] = 1;
    maps[1][1] = 1;
    maps[1][2] = 1;
    maps[2][0] = 1;
    maps[3][0] = 1;
    maps[3][1] = 1;
    //maps[4][0] = 1;
    //maps[4][1] = 1;
    maps[4][2] = 1;
    maps[4][3] = 1;

    maps[4][4] = 1;

    int result = solution(maps);

    cout << result << endl;

    return 0;
}