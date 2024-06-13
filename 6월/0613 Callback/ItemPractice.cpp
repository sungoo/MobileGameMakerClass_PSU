#include <iostream>

using namespace std;

struct Item
{
	int price;
	int tier;
	int atk;

	Item() :price(0), tier(0), atk(0) {}

	void PrintItem() {
		cout << "Price : " << price << endl;
		cout << "Tier : " << tier << endl;
		cout << "atk : " << atk << endl;
	}
};

//함수로 찾는 방법
Item* FindItem_Price_Func(Item* arr, int size, int price) {
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
bool Ptr_Price(const Item& item) {
	if (item.price == 10000)
		return true;
	return false;
}
bool Ptr_Tier(const Item& item) {
	if (item.tier == 8)
		return true;
	return false;
}
////////////////////////////////////////////////////////////////
//함수 객체로 찾는 방법
struct Finder {
	int itemPrice;
	int itemTier;
	int itemAtk;

	Finder():itemPrice(0), itemTier(0), itemAtk(0){}

	bool* operator()(const Item& item) {

		bool finding[3] = { false };

		if (itemPrice == item.price)
			finding[0] = true;
		if (itemTier == item.tier)
			finding[1] = true;
		if (itemAtk == item.atk)
			finding[2] = true;
		return finding;
	}
};

struct FinderTA {
	int itemPrice;
	int itemTier;
	int itemAtk;

	FinderTA() :itemPrice(0), itemTier(0), itemAtk(0) {}

	bool* operator()(const Item& item) {

		bool finding[3] = { false };

		//if (itemPrice == item.price)
			finding[0] = true;
		if (itemTier == item.tier)
			finding[1] = true;
		if (itemAtk == item.atk)
			finding[2] = true;
		return finding;
	}
};

struct FinderPT {
	int itemPrice;
	int itemTier;
	int itemAtk;

	FinderPT() :itemPrice(0), itemTier(0), itemAtk(0) {}

	bool* operator()(const Item& item) {

		bool finding[3] = { false };

		if (itemPrice == item.price)
			finding[0] = true;
		if (itemTier == item.tier)
			finding[1] = true;
		//if (itemAtk == item.atk)
			finding[2] = true;
		return finding;
	}
};

template<typename I, typename T>
I* FindItem_Functor(I* arr, int size, T finder) {

	I* result = nullptr;
	for (int i = 0; i < size; i++) {
		if (finder(arr[i])[0] && finder(arr[i])[1] && finder(arr[i])[2])
			result = &arr[i];
	}
	return result;
}
//Item* FindItem_FunctorPT(Item* arr, int size, Finder finder) {
//
//	Item* result = nullptr;
//	for (int i = 0; i < size; i++) {
//		if (finder(arr[i])[0] && finder(arr[i])[1])
//			result = &arr[i];
//	}
//	return result;
//}

int main() {
	Item items[10];
	for (int i = 0; i < 10; i++) {
		items[i].price = 500 * (i + 1) * 3;
		items[i].tier = (10 - i);
		items[i].atk = 10 * (i + 1);
	}

	Item* findItem = nullptr;

	//함수 포인터를 사용해서
	//Tier가 8인 애를 찾아서 출력
	findItem = FindItem_FuncPtr(items, 10, Ptr_Tier);
	if (findItem != nullptr)
		findItem->PrintItem();

	cout << endl;
	//함수 객체를 사용해서
	//Price가 9000이고, tier가 5인 거 찾기
	findItem = nullptr;
	FinderPT findPT;
	findPT.itemPrice = 9000;
	findPT.itemTier = 5;
	findItem = FindItem_Functor(items, 10, findPT);
	if (findItem != nullptr)
		findItem->PrintItem();

	cout << endl;
	//함수 객체를 사용해서
	//price = 3000, tier = 9, atk = 20 찾기
	findItem = nullptr;
	Finder find;
	find.itemPrice = 3000;
	find.itemTier = 9;
	find.itemAtk = 20;
	findItem = FindItem_Functor(items, 10, find);
	if (findItem != nullptr)
		findItem->PrintItem();

	cout << endl;
	//함수 객체 탬플릿을 사용해서 tier = 9, atk =  20 찾기
	findItem = nullptr;
	FinderTA findTA;
	findTA.itemTier = 9;
	findTA.itemAtk = 20;
	findItem = FindItem_Functor(items, 10, findTA);
	if (findItem != nullptr)
		findItem->PrintItem();

	return 0;
}