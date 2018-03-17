#include "Funcs.h"

using namespace std;

void InvalidInput(int n_op, int &op)
{
	while (cin.fail() || (op < 1 || op > n_op))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl << "Invalid option! Please try again\n" << endl;
		cin >> op;
	}
}