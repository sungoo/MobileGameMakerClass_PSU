#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool Func(const int& val) {
	if (val > 15)
		return true;
	return false;
}

void X3(int& val) {
	val *= 3;
}

struct Item {
	int price = 0;
	int atk = 0;
	int tier = 0;

	//�񱳸� ���� �񱳿����� �����ε� : ��ü���������δ� ������..
	/*bool operator<(Item a){
		return this->tier < a.tier;
	}*/
};

int main() {

	vector<int> mVec;

	mVec.push_back(3);
	mVec.push_back(1);
	mVec.push_back(1);
	mVec.push_back(9);
	mVec.push_back(11);

	mVec.push_back(21);
	mVec.push_back(4);
	mVec.push_back(6);
	mVec.push_back(8);
	mVec.push_back(1);
#pragma region Algorithm
	//1_ 1�� �ִ��� ã��. �׸��� index Ȥ�� iterator�ڸ� ��ȯ
	int index = 0;
	for (index; index < mVec.size(); index++) {
		if (mVec[index] == 1) break;
	}
	if (index == mVec.size())
		cout << "�ε����� 1 �߰� ����." << endl;
	else
		cout << "�ε����� 1 �߰�. ��ġ : " << index+1 << endl;
	
	vector<int>::iterator mit = mVec.begin();
	for (mit; mit != mVec.end(); mit++) {
		if (*mit == 1) break;
	}
	if (mit == mVec.end())
		cout << "���ͷ����ͷ� 1 �߰� ����." << endl;
	else
		cout << "���ͷ����ͷ� 1 �߰�. ��ġ : " << &*mit << endl;

	mit = std::find(mVec.begin(), mVec.end(), 1);
	if (mit != mVec.end())
		cout << *mit << endl;
	//2_ 15���� ū ���� �ִ��� ã�� index Ȥ�� iterator �ڸ� ��ȯ
	struct Finder_1 {
		bool operator()(const int& val) {
			if (val > compareNum)
				return true;
			return false;
		}
		int compareNum = 0;
	};
	Finder_1 finder_1;

	finder_1.compareNum = 15;
	mit = std::find_if(mVec.begin(), mVec.end(), finder_1);//find_if�� �����Լ��� �����Լ��� ���� �� ����
	cout << *mit << endl;

	//3_ ��� ���� 50���� ������ bool�� �˸���
	struct Finder_2
	{
		bool operator()(const int& val) {
			if (val < compareNum)
				return true;
			return false;
		}
		int compareNum = 0;
	};
	Finder_2 finder_2;
	finder_2.compareNum = 50;

	bool istrue = std::all_of(mVec.begin(), mVec.end(), finder_2);
	if (istrue)
		cout << "��� ���� 50���� ����" << endl;
	else
		cout << "50 �̻��� ���� ����" << endl;

	//4_ �ϳ��� 30���� ū ���� �ִ��� bool�� �˸���
	finder_1.compareNum = 30;
	istrue = std::any_of(mVec.begin(), mVec.end(), finder_1);
	if (istrue)
		cout << "30���� ū ���� ����" << endl;
	else
		cout << "30���� ū ���� ����" << endl;

	//5_ ���Ұ� 3�� ���ҵ��� ������ �˾Ƴ���
	
	int cnt = std::count(mVec.begin(), mVec.end(), 3);
	cout << "3�� ������ ���� : " << cnt << endl;

	//6_ ���Ұ� 5 �̻��� ���� ������ �˾Ƴ���
	finder_1.compareNum = 4;
	cnt = std::count_if(mVec.begin(), mVec.end(), finder_1);
	cout << "5 �̻� ������ ���� : " << cnt << endl;

	//7_ ��� ���ҿ� 3 ���ϱ�
	cout << "��� ���� 3 ���ϱ�" << endl;
	for_each(mVec.begin(), mVec.end(), X3);
	
	for (mit = mVec.begin(); mit != mVec.end(); mit++) {
		cout << *mit << ' ';
	}
	cout << endl;

	//8_ �ߺ� ���� �����ϱ�
	cout << "�ߺ� ���� ����" << endl;
	
	//unique�� �����ϰ� �����
	std::sort(mVec.begin(), mVec.end());
	auto it = std::unique(mVec.begin(), mVec.end());

	for (mit = mVec.begin(); mit != it; mit++) {
		cout << *mit << ' ';
	}
	cout << endl;

	//9_ ���Ұ� 12�� �� �����
	cout << "remove 12" << endl;
	it = std::remove(mVec.begin(), mVec.end(), 12);
	for (mit = mVec.begin(); mit != it; mit++) {
		cout << *mit << ' ';
	}
	cout << endl;

	//10_ ���Ұ� 10���� ������ �����
	finder_2.compareNum = 10;
	cout << "remove x < 10" << endl;
	it = std::remove_if(mVec.begin(), mVec.end(), finder_2);
	for (mit = mVec.begin(); mit != it; mit++) {
		cout << *mit << ' ';
	}
	cout << endl;

	//�˰������ ���� ���� ���ͷ����ͷ� 11�����

	for (mit = mVec.begin(); mit != mVec.end(); mit++) {
		if (*mit == 11) {
			mit = mVec.erase(mit) - 1;//11�� ����� �� �ڸ��� ����� 21�� ����Ű�� �� => -1�ؼ� 21�� �ٽ��ѹ� üũ�ϰ� �Ѿ�� �ϱ�
			continue;
		}
	}
	
	for (mit = mVec.begin(); mit != mVec.end(); mit++) {
		cout << *mit << ' ';
	}
	cout << endl;
#pragma endregion
	//////////////////////////////////////////////////////////////////
	//Sort
	vector<Item> items;
	items.resize(mVec.size());

	for (int i = 0; i < items.size(); i++) {
		items[i].tier = 21 - mVec[i];
		items[i].atk = mVec[i] * 3;
		items[i].price = mVec[i] * 100;
	}
	//items �� ������������ tier ����
	struct Srt {
		bool operator()(const Item& a, const Item& b) {
			return a.tier < b.tier;
		}
	};
	Srt st;
	std::sort(items.begin(), items.end(), st);

	return 0;
}