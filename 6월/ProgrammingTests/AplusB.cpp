#include <iostream>
///#include <Windows.h>

using namespace std;

int main()
{
	int a = 0;
	int b = 0;
	while (true)
	{
		if (a > 0 && b < 10)
			break;
		cin >> a >> b;
		system("cls");
	}

	cout << a + b << endl;

	return 0;
}