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
	exp.push_back(15);
	exp.push_back(14);
	exp.push_back(13);
	exp.push_back(1);
	exp.push_back(0);

	GenerateMatrix* matrix = new GenerateMatrix(exp);
	int result = matrix->red();


	cout << "Result : " << result << endl; // prints !!!Hello World!!!
	return 0;
}
