#include "compvalue.h"
#include "trans.h"
#include <iostream>
#include "mgpath.h"
using namespace std;

int main()
{
	if (!mgpath(1, 1, 8, 8))
		cout << "YES!" << endl;
	return 0;
}