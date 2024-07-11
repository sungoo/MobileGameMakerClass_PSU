#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

void MergeResult(vector<int>& v, int left, int mid, int right) {
    //ó�� ������ �� : ���� �۰� �ɰ��� ����
    int leftIndex = left;
    int rightIndex = mid + 1;

    vector<int> temp;

    //{left ~ mid} �� {mid+1 ~ right}�� ����
    // |^|              |^|
    //leftIndex        rightIndex
    while (true)
    {
        if (leftIndex > mid || rightIndex > right)
            break;

        //leftindex�� rightindex �� ������ temp�� �ֱ�
        if (v[leftIndex] <= v[rightIndex]) {
            temp.push_back(v[leftIndex]);
            leftIndex++;
        }
        else {
            temp.push_back(v[rightIndex]);
            rightIndex++;
        }

    }
    //�� ������ ������ ���� �� temp�� �ֱ�
    //1. �����ʿ� �ִ� ���ҵ��� �� ���簡 �Ǿ���.
    // left �迭�� �����ִ�.
    for (int i = leftIndex; i <= mid; i++) {
        temp.push_back(v[i]);
    }
    //2. ���ʿ� �ִ� ���ҵ��� �� ���簡 �Ǿ���.
    // right �迭�� �����ִ�.
    for (int i = rightIndex; i <= right; i++) {
        temp.push_back(v[i]);
    }


    for (int i = 0; i < temp.size(); i++) {
        v[left + i] = temp[i];
    }
}

void MergeSort(vector<int>& v, int left, int right) {
    if (left >= right)
        return;

    int mid = (left + right) / 2;

    //Divide
    MergeSort(v, left, mid);
    MergeSort(v, mid+1, right);

    MergeResult(v, left, mid, right);
}

int main()
{
    vector<int> v = { 20,22,10,67, 90,23,88,23,55 };

    //MergeSort(v, 0, v.size() - 1);
    std::stable_sort(v.begin(), v.end());

    for (auto it : v) {
        cout << it << ", ";
    }

    return 0;
}
