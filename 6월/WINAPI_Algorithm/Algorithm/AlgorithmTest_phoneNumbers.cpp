#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

bool solution(vector<string> phone_book) {
    bool answer = true;
    bool isoriginShorter = true;

    unordered_map<string, string> phonenum;

    //접두어로 가장 유력한, 가장 짧은 번호 찾기.
    string shorter = phone_book[0];
    for (string phonenumber : phone_book)
    {
        if (phonenumber.length() < shorter.length())
            shorter = phonenumber;
    }
    int shortlen = shorter.length();

    //모든 원소를 접두어 길이로 나눠서 앞쪽은 key로, 뒤쪽은 value로 넣기
    for (string phonenumber : phone_book)
    {
        string header = phonenumber.substr(0, shortlen);
        if (phonenum.find(header) == phonenum.end())
            phonenum.insert({ header, phonenumber });
        else
        {
            if (header != shorter)
                isoriginShorter = false;
            phonenum[header] = phonenumber;
        }
    }

    if (phonenum.size() != phone_book.size() && isoriginShorter)
        answer = false;

    return answer;
}

int main()
{
    vector<string> phones = { "123", "1005", "1006", "1007"};
    
    if (solution(phones))
        cout << "true" << endl;
    else
        cout << "false" << endl;

    return 0;
}