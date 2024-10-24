#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>
#include <concurrent_priority_queue.h>

using namespace std;


//�켱���� ť
// 1. ��������Ʈ��
// 2. �θ� �׻� �ڽĺ��� ũ��.(�ִ���)
template <typename T, typename Container = vector<T>, typename Pred = less<T>>
class Priority_queue {
	Container _container;

public:
	void push(const T& value)
	{
		_container.push_back(value);
		int now = _container.size() - 1;

		while (true)
		{
			if (now <= 0)
				break;

			int parent = (now - 1) / 2;
			//�ڽ��� �θ𺸴� ���� => �� �ٲ�
			if (_container[parent] > _container[now]) break;

			//�ڽ��� �θ𺸴� ŭ
			std::swap(_container[now], _container[parent]);
			now = parent;
		}
	}

	void pop()
	{
		_container[0] = _container.back();
		_container.pop_back();

		int now = 0;

		while (true)
		{
			int leftChild = now * 2 + 1;
			int rightChild = now * 2 + 2;

			//�ڽ��� ���� ��Ȳ
			if (leftChild >= (int)_container.size()) {
				break;
			}

			int next = now;

			//leftChild, rightChild�� ���ϸ鼭 ���� �� ū ������ Ȯ��
			if (_container[next] < _container[leftChild]) {
				next = leftChild;
			}
			//rightChild�� ��ȿ���� Ȯ��
			if (rightChild < (int)_container.size() && _container[next] < _container[rightChild]) {
				next = rightChild;
			}
			if (next == now)
				break;

			std::swap(_container[now], _container[next]);
			now = next;
		}
	}

	const T& top()
	{
		return _container[0];
	}

	bool empty()
	{
		return _container.empty();
	}
};

int main()
{
	Priority_queue<int> pq;

	pq.push(100);
	pq.push(120);
	pq.push(10);
	pq.push(1);
	pq.push(167);
	pq.push(12);
	pq.push(180);
	pq.push(90);
	pq.push(500);
	pq.push(720);

	//n������ m�� ��ŭ�� �����ϰ� �ʹ�.
	// => partial_sort  =>  m * log n
	while (true)
	{
		if (pq.empty())break;

		int top = pq.top();
		cout << top << endl;

		pq.pop();
	}

	return 0;
}