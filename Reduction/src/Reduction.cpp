//============================================================================
// Name        : Reduction.cpp
// Author      : Gustavo Banegas
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <armadillo>

#include "GenerateMatrix.h"

using namespace std;
using namespace arma;

int main() {
	vector<int> exp;
	exp.push_back(5);
	exp.push_back(3);
	exp.push_back(2);
	exp.push_back(1);
	exp.push_back(0);

	GenerateMatrix* matrix = new GenerateMatrix(exp);
	int result = matrix->red();


	cout << "Result : " << result << endl; // prints !!!Hello World!!!
	return 0;
}
