#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> nums;
vector<bool> visited;
vector<string> primes;

//숫자가 2개일 때
// n, m, nm, mn 4가지.
// 숫자가 3개일 때
// n, m, l, nm, nl, mn, ml, ln, lm, nml, nlm, mnl, mln, lnm, lmn
//

void FindAll(int here, string prime) {
    visited[here] = true;
    prime += nums[here];
    
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
    cout << prime << endl;

    primes.push_back(prime);
}

int FindPrime(int len)
{
    int primeCNT = 0;
    bool isPrime = true;

    for (int i = 0; i < len; i++) {
        FindAll(i, "");
    }
    cout << endl;

    for (string prime : primes) 
    {
        int pNum = stoi(prime);
        if (pNum == 0 || pNum == 1)
            continue;
        for (int i = 2; i <pNum; i++) {
            if (pNum % i == 0)
            {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            cout << pNum << endl;
            primeCNT++;
        }
    }
    cout << endl;
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