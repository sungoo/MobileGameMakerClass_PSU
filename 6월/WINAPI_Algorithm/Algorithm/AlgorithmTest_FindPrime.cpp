#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

vector<string> nums;
vector<bool> visited;
vector<string> primes;
unordered_map<int, int> um;

//숫자가 2개일 때
// n, m, nm, mn 4가지.
// 숫자가 3개일 때
// n, m, l, nm, nl, mn, ml, ln, lm, nml, nlm, mnl, mln, lnm, lmn
//

bool IsPrime(int num)
{
    if (num <= 1)
        return false;
    if (num == 2 || num == 3)
        return true;

    int root = sqrtf(num);
    for (int i = 2; i <= root; i++)
    {
        if (num % i == 0) return false;
    }
    return true;
}

void FindAll(int here, string prime) {
    visited[here] = true;
    prime += nums[here];

    primes.push_back(prime);

    for (int there = 0; there < nums.size(); there++) {
        //첫번째 자리가 0일때
        if (prime[0] == '0')
            continue;
        if (here == there)
            continue;
        if (visited[there])
            continue;

        FindAll(there, prime);

    }
    visited[here] = false;
}

int FindPrime(int len)
{
    int primeCNT = 0;
    bool isPrime = true;

    //모든 문자열 만들기
    for (int i = 0; i < len; i++) {
        FindAll(i, "");
    }

    //중복 삭제
    for (string prime : primes)
    {
        int pNum = stoi(prime);
        um[pNum] = 1;
    }
    //소수 판별
    for (auto myPair : um)
    {
        int num = myPair.first;
        if (IsPrime(num))
            primeCNT++;
    }

    return primeCNT;
}

int solution(string numbers) {
    int answer = 0;

    int len = numbers.size();
    visited = vector<bool>(len, false);

    for (int i = 0; i < len; i++) {
        nums.push_back(numbers.substr(i, 1));
    }

    answer = FindPrime(len);

    return answer;
}

int main() {

    string nums = "1110";

    cout << solution(nums) << endl;
}