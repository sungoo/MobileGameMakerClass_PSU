#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

bool solution(vector<string> phone_book) {
    bool answer = true;
    bool isoriginShorter = true;

    unordered_map<string, string> phonenum;

    //���ξ�� ���� ������, ���� ª�� ��ȣ ã��.
    string shorter = phone_book[0];
    for (string phonenumber : phone_book)
    {
        if (phonenumber.length() < shorter.length())
            shorter = phonenumber;
    }
    int shortlen = shorter.length();

    //��� ���Ҹ� ���ξ� ���̷� ������ ������ key��, ������ value�� �ֱ�
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