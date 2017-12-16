#include <iostream>
#include "deque.h"
using namespace std;

int main(int argc, char* argv[]) {
	Deque <int> d;
	d.push_front(1);
	cout << d.front() << ' ' << d[0];
	system("pause");
	return 0;
}