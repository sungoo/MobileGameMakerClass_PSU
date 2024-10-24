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

//babble�� �̿��ؼ� ���� �� �ִ� �ܾ� �� �����
//�� ���� �� �ִ� �ܾ�� 64����.

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

// babbling_len�� �迭 babbling�� �����Դϴ�.
// �Ķ���ͷ� �־����� ���ڿ��� const�� �־����ϴ�. �����Ϸ��� ���ڿ��� �����ؼ� ����ϼ���.
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