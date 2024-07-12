#include "BinarySearch.h"

int main() {
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

	cout << bst.Next(bst._root)->key << endl;
	cout << bst.Privious(bst._root)->key << endl;
	cout << bst.Privious(bst.Search(bst._root, 45))->key << endl;

	return 0;
}