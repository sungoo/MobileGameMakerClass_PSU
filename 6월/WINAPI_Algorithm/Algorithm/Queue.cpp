#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

// queue : 줄 세우기(게임에서 큐 돌린다)
// FIFO : First In First Out
//

template <typename T, typename Container = list<T>>
class Queue {
	
	Container values;
	
public:
	void push(const T& val) {
		values.push_back(val);
	}
	void pop() {
		values.pop_front();
	}
	bool empty() {
		return values.size() == 0;
	}
	const T& front() {
		return values.front();
	}
};

int main() {

	Queue<int, list<int>> q;

	q.push(51);
	q.push(2);
	q.push(12);
	q.push(89);

	while (true)
	{
		if (q.empty() == true)
			break;

		cout << q.front() << endl;
		q.pop();
	}

	return 0;
}