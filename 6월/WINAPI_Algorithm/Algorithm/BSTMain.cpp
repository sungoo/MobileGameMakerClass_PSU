#include <unordered_map>

#include "BinarySearch.h"

//해시테이블 : 메모리를 주고 탐색 시간을 취한다.
// 탐색 : 상수 ...해쉬충돌로 인한 체이닝에 따라 달라진다.
// 삽입 : 상수
// 충돌, 체이닝

//해쉬테이블 vs 자가균형이진탐색트리
// 해쉬함수 후 충돌이 많이 일어날 경우 ... 자가균형이진탐색트리 승
// 충돌이 적을 경우 ... 해쉬테이블 승
//

int main() {
#pragma region BST
	BinarySearchTree bst;
	bst.Insert(50);
	bst.Insert(40);
	bst.Insert(70);
	bst.Insert(30);
	bst.Insert(45);

	bst.PrintTree(bst._root);
	Node* node = bst.Search(bst._root, 70);

	if (node == nullptr)
		cout << "No valiable node" << endl;
	else
		cout << node->key << " : " << node->data << endl;

	auto minNode = bst.Min(bst._root);
	cout << minNode->key << endl;
	auto maxNode = bst.Max(bst._root);
	cout << maxNode->key << endl;
#pragma endregion

	unordered_map<int, int> um;

	um[5] = 1;

	return 0;
}