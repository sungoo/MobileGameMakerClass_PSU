#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

vector<string> babble = {
        "aya",
        "ye",
        "woo",
        "ma"
};
vector<string> argument;

vector<bool> visited(4, false);
unordered_map<string, string> canBabble;

//babble을 이용해서 만들 수 있는 단어 다 만들기
//총 만들 수 있는 단어는 64가지.

void DFS(int here, string word)
{
    visited[here] = true;
    word += babble[here];

    canBabble[word] = here;

    for (int there = 0; there < 4; there++) {
        if (here == there)
            continue;
        if (visited[there])
            continue;

        DFS(there, word);
    }

    visited[here] = false;
}

void DFS_ALL() {
    for (int i = 0; i < 4; i++) {
        DFS(i, "");
    }
}

// babbling_len은 배열 babbling의 길이입니다.
// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int solution(vector<string> babbling) {
    int answer = 0;

    DFS_ALL();

    for (auto word : babbling) {
        if (canBabble.count(word) != 0)
            answer++;
    }
    return answer;
}

int main() {
    const int len = 5;
    vector<string> babbleing = {
        "ayaye", "uuuma", "ye", "yemawoo", "ayaa"
    };

    cout << solution(babbleing) << endl;
}