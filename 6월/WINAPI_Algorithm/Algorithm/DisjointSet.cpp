#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>
#include <concurrent_priority_queue.h>

using namespace std;

struct User {
	int _guildID;
};

void GuildSystem() {
	vector<User> users;

	for (int i = 0; i < 1000; i++) {
		User user;
		user._guildID = i;

		users.push_back(user);
	}
////1번 유저가 5번 유저를 길드로 초대한다.
//	users[5]._guildID = users[1]._guildID;
////guildID가 2인 애들이 1로 합쳐진다.
//	for (auto& user : users) {
//		if (user._guildID == 2)
//			user._guildID = 1;
//	}
}

class Naive_DisjointSet 
{
public:
	Naive_DisjointSet(int n) {
		_parent = vector<int>(n, 0);

		for (int i = 0; i < n; i++) {
			_parent[i] = i;
		}
	}

	int FindLeader(int u) {
		if (u == _parent[u])
			return u;

		int parent = _parent[u];
		return FindLeader(parent);
	}

	void Merge(int u, int v) {
		int uLeader = FindLeader(u);
		int vLeader = FindLeader(v);

		if (uLeader == vLeader)
			return;

		_parent[vLeader] = uLeader;
	}
private:
	vector<int> _parent;
};

class DisjointSet {
public:
	DisjointSet(int n)
	{
		_parent = vector<int>(n, 0);
		_rank = vector<int>(n, 1);

		for (int i = 0; i < n; i++) {
			_parent[i] = i;
		}
	}

	int FindLeader(int u)
	{
		if (u == _parent[u])
			return u;

		int parent = _parent[u];
		return FindLeader(parent);
	}

	void Merge(int u, int v) {
		int uLeader = FindLeader(u);
		int vLeader = FindLeader(v);

		if (uLeader == vLeader)
			return;

		if (_rank[uLeader] > _rank[vLeader])
		{
			std::swap(uLeader, vLeader);
		}

		_parent[uLeader] = vLeader;

		if (_rank[uLeader] == _rank[vLeader])
			_rank[vLeader]++;
	}

private:
	vector<int> _parent;
	vector<int> _rank;
};

int main() {
	DisjointSet set(10);

	set.Merge(2, 3);
	set.Merge(0, 5);
	set.Merge(8, 0);
	set.Merge(4, 9);
	set.Merge(3, 9);

	cout << set.FindLeader(3);

	return 0;
}