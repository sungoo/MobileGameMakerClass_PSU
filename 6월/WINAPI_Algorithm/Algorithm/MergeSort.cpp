#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

void MergeResult(vector<int>& v, int left, int mid, int right) {
    //처음 들어왔을 때 : 제일 작게 쪼개진 상태
    int leftIndex = left;
    int rightIndex = mid + 1;

    vector<int> temp;

    //{left ~ mid} 와 {mid+1 ~ right}의 병합
    // |^|              |^|
    //leftIndex        rightIndex
    while (true)
    {
        if (leftIndex > mid || rightIndex > right)
            break;

        //leftindex와 rightindex 중 작은거 temp에 넣기
        if (v[leftIndex] <= v[rightIndex]) {
            temp.push_back(v[leftIndex]);
            leftIndex++;
        }
        else {
            temp.push_back(v[rightIndex]);
            rightIndex++;
        }

    }
    //위 과정이 끝나고 남은 값 temp에 넣기
    //1. 오른쪽에 있던 원소들이 다 복사가 되었다.
    // left 배열이 남아있다.
    for (int i = leftIndex; i <= mid; i++) {
        temp.push_back(v[i]);
    }
    //2. 왼쪽에 있던 원소들이 다 복사가 되었다.
    // right 배열이 남아있다.
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
