#include <iostream>
#include <vector>
#include <list>

using namespace std;

#include "Vector.h"
#include "List.h"

//void PrintVec(const vector<int> v) {
//    for (int i = 0; i < v.size(); i++)
//        cout << v[i] << endl;
//}

int main()
{
#pragma region Vector
    int temp = 1;

    //정적배열
    int arr[5] = { 1,2,3,4,5 };
    vector<int> v;
    Vector<int> myv;
    ////몇 개의 배열을 만들건지 미리 주문해두기
    myv.Reserve(10);
    //v.resize(1000);//0~999까지 기본값으로 초기화
    for (int i = 0; i < 50; i++) {
        myv.PushBack(i);
        cout << myv.Capacity() << endl;//벡터의 실제 크기
        cout << myv.Size() << endl;//현재 유효값이 들어간 벡터의 크기
        cout << "========================================" << endl;
    }
    ////낭비되는 capacity가 없게 줄이기
    //v.shrink_to_fit();

    ///*for (int i = 0; i < v.size(); i++) {
    //    cout << v[i] << endl;
    //    
    //}*/
    cout << "========================================" << endl;
    cout << "========================================" << endl;
    /*for (int i = 0; i < 5; i++) {
        v.push_back(i);
    }*/
    for (int i = 0; i < 5; i++) {
        myv.PopBack();
    }
    for (int i = 0; i < myv.Size(); i++) {
        cout << myv[i] << endl;
        cout << myv.Capacity() << endl;//벡터의 실제 크기
        cout << myv.Size() << endl;//현재 유효값이 들어간 벡터의 크기
        cout << "========================================" << endl;
    }
    cout << "========================================" << endl;
    cout << "========================================" << endl;
    //vector의 clear는 공간을 없애지 않는다. 내용만 삭제함.
    v.clear();
    for (int i = 0; i < myv.Size(); i++) {
        cout << myv[i] << endl;
        cout << myv.Capacity() << endl;//벡터의 실제 크기
        cout << myv.Size() << endl;//현재 유효값이 들어간 벡터의 크기
        cout << "========================================" << endl;
    }

    //임시객체(이름없는 객체 : 생성자 호출 후 바로 소멸자 호출됨)
    vector<int>().swap(v);//Effective STL

    cout << v.capacity() << endl;
    cout << v.size() << endl;

#pragma endregion
#pragma region List
    //list<int> l;
    //List myL;

    //for (int i = 0; i < 5; i++) {
    //    l.push_back(i);
    //    l.push_front(i);

    //    myL.PushBack(i);
    //    //myL.PushFront(i);
    //}

    //myL.PushBack(100);
    //myL.Insert(15, myL.FindNode(3));

    //for (int i = 0; i < myL.Size(); i++) {
    //    //cout << myL[i] << endl;
    //}
#pragma endregion
}
