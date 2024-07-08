#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

// 선형자료형 : vector, list, stack, queue
// 비선형자료형 : graph, tree
// 
// Tree
// 1. 계층구조를 표현할 때 자주 쓰인다.
// -> 부모 노드와 자식 노드가 서로 이어져있다.
// Root Node : 최상위 부모 -> 모든 트리에는 단 하나의 루트노드만이 존재
// Leaf Node : 최하위 자식
// 2. 트리는 잘라도 트리
// -> 서브트리
// -> 재귀적으로 자식을 타고 들어갈 수 있다.
// 
// 트리의 종류
// 1. 이진트리
// 2. 포화이진트리
// 3. 완전이진트리
// 4. 이진탐색트리
//

struct Node
{
	vector<Node*> _child;
	string _data;

	Node(){}
	Node(const string& data) : _data(data){}
};

Node* CreateTree() {
	Node* root = new Node("개발부");
	{
		Node* node1 = new Node("프로그래밍팀");
		root->_child.push_back(node1);
		{
			Node* _node1 = new Node("엔진프로그래밍");
			node1->_child.push_back(_node1);

			Node* _node2 = new Node("클라이언트프로그래밍");
			node1->_child.push_back(_node2);

			Node* _node3 = new Node("서버프로그래밍");
			node1->_child.push_back(_node3);
		}

		Node* node2 = new Node("기획팀");
		root->_child.push_back(node2);
		{
			Node* _node1 = new Node("레벨디자인");
			node2->_child.push_back(_node1);

			Node* _node2 = new Node("스토리");
			node2->_child.push_back(_node2);

			Node* _node3 = new Node("시스템");
			node2->_child.push_back(_node3);
		}

		Node* node3 = new Node("아트팀");
		root->_child.push_back(node3);
		{
			{
				Node* _node1 = new Node("배경");
				node3->_child.push_back(_node1);

				Node* _node2 = new Node("모델링");
				node3->_child.push_back(_node2);

				Node* _node3 = new Node("일러스트");
				node3->_child.push_back(_node3);
			}
		}
	}

	return root;
}

void PrintTree(Node* root, int depth) 
{
	for (int i = 0; i < depth; i++) {
		cout << " - ";
	}

	cout << root->_data << endl;

	//트리를 재귀호출로 순회하는 방법
	for (auto child : root->_child) {
		PrintTree(child, depth + 1);
	}
}

int main() {

	Node* root = CreateTree();

	PrintTree(root, 0);

	return 0;
}