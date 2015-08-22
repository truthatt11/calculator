#include <iostream>
#include <cstring>
#include "calculator.h"

using namespace std;



int main()
{
	char input[1024];
	calculator c1;

	while (cin.getline(input, 1023)) {
		if (!c1.parse(input)) {
			cout << "Input Error" << endl;
			continue;
		}
		if (c1.calc()) cout << "Answer: " << c1.get_ans() << endl;
	}
	return 0;
}

