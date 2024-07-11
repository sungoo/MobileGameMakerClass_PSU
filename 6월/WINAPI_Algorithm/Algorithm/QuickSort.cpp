#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

//Heap Sort
// 힙트리에 하나씩 다 집어넣고 하나씩 뽑아내는것.

//Quick Sort
// 평균 시간 복잡도 : N x log N
// 최악 시간 복잡도 : N x N
//

int Partition(vector<int>& v, int left, int right) {
    int pivot = v[left];
    int lowIndex = left + 1;
    int hightIndex = right;

    while (true)
    {
        if (lowIndex > hightIndex)
            break;
        //lowindex는 항상 pivot보다 작아야한다.
        //작으면 다음 index를 확인한다.
        while (lowIndex<=right && pivot>=v[lowIndex])
        {
            lowIndex++;
        }
        //highindex는 항상 pivot보다 커야한다.
        //크면 이전 index를 확인한다.
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
    //기저사항
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

    //n log n 만큼의 시간복잡도를 가지는 정렬 3가지.
    std::sort(v.begin(), v.end());
    std::partial_sort(v.begin(), v.begin() + 3, v.end());
    std::stable_sort(v.begin(), v.end());
    
    return 0;
}
