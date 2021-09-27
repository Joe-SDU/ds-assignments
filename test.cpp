#include <iostream>
#include "currency.h"
#include "recursion.h"
using namespace std;


int main()
{
	currency x;
	x.input(cin);

	x.output(cout) << endl;


	x = x.multiply(0.5);

	x.output(cout);

	return 0;
}