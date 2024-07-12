#include "BinarySearch.h"

BinarySearchTree::~BinarySearchTree()
{
	
}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node(key);

	if (_root == nullptr) {
		_root = newNode;
		return;
	}

	Node* node = _root;
	Node* parent = nullptr;

	while (true)
	{
		if (node == nullptr)
			break;

		parent = node;
		if (key < node->key) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}

	newNode->parent = parent;
	if (key < parent->key) {
		parent->left = newNode;
	}
	else {
		parent->right = newNode;
	}
}

void BinarySearchTree::PrintTree(Node* node)
{
	if (node == nullptr)
		return;

	//Tree의 전위순회 : 부모 - 왼쪽 자식들 - 오른쪽 자식들
	//Tree의 중위순회 : 왼쪽 자식들 - 부모 - 오른쪽 자식들
	//Tree의 후위순회 : 왼쪽 자식들 - 오른쪽 자식들 - 부모

	cout << node->key << endl;
	PrintTree(node->left);
	PrintTree(node->right);
}

Node* BinarySearchTree::Search(Node* node, int key)
{
	if (node == nullptr)
		return nullptr;

	if (node->key == key)
		return node;

	if (key < node->key)
		Search(node->left, key);
	else
		Search(node->right, key);
}

Node* BinarySearchTree::Min(Node* node)
{
	if (node == nullptr)
		return nullptr;

	if(node->left != nullptr)
		return Min(node->left);

	return node;
}

Node* BinarySearchTree::Max(Node* node)
{
	if (node == nullptr)
		return nullptr;

	if (node->right != nullptr)
		return Max(node->right);

	return node;
}

Node* BinarySearchTree::Privious(Node* node)
{
	if (node == nullptr)
		return nullptr;

	if (node->left == nullptr)
		return node;

	auto result = Max(node->left);

	if (result == nullptr)
		return node->parent;

	return result;
}

Node* BinarySearchTree::Next(Node* node)
{
	if(node == nullptr)
		return nullptr;

	if (node->right == nullptr)
		return node;

	auto result = Min(node->right);

	if (result == nullptr)
		return node->parent;

	return result;
}

void BinarySearchTree::Delete(Node* node)
{
	if (node == nullptr)
		return;

	if (node->left == nullptr)
		Replace(node, node->right);
	else if (node->right == nullptr)
		Replace(node, node->left);
	else
	{
		Node* prev = Privious(node);
		node->key = prev->key;
		node->data = prev->data;

		Delete(prev);
	}

}

void BinarySearchTree::Replace(Node* node1, Node* node2)
{
	//node1이 root일 때, 그냥 교환해버리기
	if (node1->parent == nullptr)
		_root = node2;

	else if (node1 == node2->parent->left)
	{
		node1->parent->left = node2;
	}
	else
	{
		node1->parent->right = node2;
	}

	if (node2 != nullptr)
		node2->parent = node1->parent;

	delete node1;
}
