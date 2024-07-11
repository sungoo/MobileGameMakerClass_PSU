#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

//Heap Sort
// ��Ʈ���� �ϳ��� �� ����ְ� �ϳ��� �̾Ƴ��°�.

//Quick Sort
// ��� �ð� ���⵵ : N x log N
// �־� �ð� ���⵵ : N x N
//

int Partition(vector<int>& v, int left, int right) {
    int pivot = v[left];
    int lowIndex = left + 1;
    int hightIndex = right;

    while (true)
    {
        if (lowIndex > hightIndex)
            break;
        //lowindex�� �׻� pivot���� �۾ƾ��Ѵ�.
        //������ ���� index�� Ȯ���Ѵ�.
        while (lowIndex<=right && pivot>=v[lowIndex])
        {
            lowIndex++;
        }
        //highindex�� �׻� pivot���� Ŀ���Ѵ�.
        //ũ�� ���� index�� Ȯ���Ѵ�.
        while (hightIndex>=left+1 && pivot<=v[hightIndex])
        {
            hightIndex--;
        }

        if (lowIndex < hightIndex)
            std::swap(v[lowIndex], v[hightIndex]);
    }
    std::swap(v[hightIndex], v[left]);

    return hightIndex;
}

void QuickSort(vector<int>& v, int left, int right) {
    //��������
    if (left > right)
        return;


    int pivotIndex = Partition(v, left, right);
    cout << left << " ~ " << pivotIndex - 1 << endl;

    QuickSort(v, left, pivotIndex - 1);
    QuickSort(v, pivotIndex + 1, right);
}

int main()
{
    //                                23a   23b
    vector<int> v = { 20,22,10,67, 90,23,88,23,55 };

    QuickSort(v, 0, v.size() - 1);

    //n log n ��ŭ�� �ð����⵵�� ������ ���� 3����.
    std::sort(v.begin(), v.end());
    std::partial_sort(v.begin(), v.begin() + 3, v.end());
    std::stable_sort(v.begin(), v.end());
    
    return 0;
}
