#include <iostream>
#include <string>
#include <vector>

using namespace std;

int Giveupper1(vector<int> answers)
{
    int corrected = 0;
    vector<int> forking = { 1, 2, 3, 4, 5 };

    for (int i = 0; i < answers.size(); i++)
    {
        if (answers[i] == forking[i % forking.size()])
            corrected++;
    }

    return corrected;
}
int Giveupper2(vector<int> answers)
{
    int corrected = 0;
    vector<int> forking = { 2, 1, 2, 3, 2, 4, 2, 5 };

    for (int i = 0; i < answers.size(); i++)
    {
        if (answers[i] == forking[i % forking.size()])
            corrected++;
    }

    return corrected;
}
int Giveupper3(vector<int> answers)
{
    int corrected = 0;
    vector<int> forking = { 3, 3, 1, 1, 2, 2, 4 ,4, 5, 5 };

    for (int i = 0; i < answers.size(); i++)
    {
        if (answers[i] == forking[i % forking.size()])
            corrected++;
    }

    return corrected;
}

vector<int> solution(vector<int> answers) {
    vector<int> answer;
    vector<int> score = vector<int>(3, 0);



    return answer;
}