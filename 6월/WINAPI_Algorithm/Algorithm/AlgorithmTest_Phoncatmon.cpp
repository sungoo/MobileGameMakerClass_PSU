#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int solution(vector<int> nums)
{
    int answer = 0;
    int numP = nums.size();
    unordered_map<int, int> phoncat;
    
    for (int num : nums)
    {
        if (phoncat.find(num) == phoncat.end())
            phoncat.insert({ num, 1 });
        else
            phoncat[num]++;
    }

    int specip = phoncat.size();

    if (numP / 2 < specip)
        answer = numP / 2;
    else
        answer = specip;

    return answer;
}

int main() {
    vector<int> phoncats = { 1, 1, 2, 2, 2, 2, 2, 5 };

    cout << solution(phoncats) << endl;
}