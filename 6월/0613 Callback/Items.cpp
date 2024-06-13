#include <iostream>

using namespace std;

struct Item
{
	int price;
	int tier;
	int atk;

	Item():price(0), tier(0), atk(0){}

	void PrintItem() {
		cout << "Price : " << price << endl;
		cout << "Tier : " << tier << endl;
		cout << "atk : " << atk << endl;
	}
};

//함수로 찾는 방법
Item* FindItem_Price(Item* arr, int size, int price) {
	//매개변수 price에 맞는 아이템을 찾아서, return.
	//만약 없다면 nullptr 반환

	Item* result = nullptr;

	for (int i = 0; i < size; i++) {
		if ((arr + i)->price == price)
			result = (arr + i);
	}
	return result;
}
////////////////////////////////////////////////////////////////
//함수 포인터를 이용해서 찾는 방법
Item* FindItem_FuncPtr(Item* arr, int size, bool(*func)(const Item&)) {
	Item* result = nullptr;

	for (int i = 0; i < size; i++) {
		if (func(arr[i]))
			result = &arr[i];
	}
	return result;
}
bool FindItemPtr_Price(const Item& item) {
	if (item.price == 10000)
		return true;
	return false;
}
bool FindItemPtr_Tier(const Item& item) {
	if (item.tier == 1)
		return true;
	return false;
}
////////////////////////////////////////////////////////////////
//함수 객체로 찾는 방법
struct Finder {
	int itemPrice;
	int itemTier;
	int itemAtk;

	bool operator()(const Item& item) {
		if (itemPrice == item.price)
			return true;
		return false;
	}
};

Item* FindItem_Functor(Item* arr, int size, Finder finder) {

	Item* result = nullptr;
	for (int i = 0; i < size; i++) {
		if (finder(arr[i]))
			result = &arr[i];
	}
	return result;
}

int main() {
	Item items[10];
	for (int i = 0; i < 10; i++) {
		items[i].price = 500 * (i + 1) * 3;
		items[i].tier = (10 - i);
		items[i].atk = 10 * (i + 1);
	}

	Item* findItem = FindItem_Price(items, 10, 9000);
	if (findItem != nullptr)
		findItem->PrintItem();

	findItem = nullptr;
	findItem = FindItem_FuncPtr(items, 10, &FindItemPtr_Price);
	findItem = FindItem_FuncPtr(items, 10, &FindItemPtr_Tier);

	Finder finder;
	finder.itemPrice = 3000;
	findItem = nullptr;
	findItem = FindItem_Functor(items, 10, finder);
	if (findItem != nullptr)
		findItem->PrintItem();

	return 0;
}