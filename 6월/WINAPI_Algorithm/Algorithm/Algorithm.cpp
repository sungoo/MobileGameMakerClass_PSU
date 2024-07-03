#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>

using namespace std;

//stack : 팬케이크
// FILO : First Input Last Out
//

class Stack {

    vector<int> vals;

public:

    void Push(const int& val) {
        vals.push_back(val);
    }
    void Pop() {
        vals.pop_back();
    }
    int Top() {
        return vals.back();
    }
    bool Empty() {
        return vals.empty();
    }
};

int main()
{
    Stack s;

    s.Push(1);
    s.Push(2);
    s.Push(3);
    s.Push(4);

    while (true)
    {
        if (s.Empty())
            break;

        cout << s.Top() << endl;

        s.Pop();
    }

    return 0;
}
