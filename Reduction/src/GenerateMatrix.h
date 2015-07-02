/*
 * GenerateMatrix.h
 *
 *  Created on: Jul 1, 2015
 *      Author: vader
 */

#ifndef GENERATEMATRIX_H_
#define GENERATEMATRIX_H_
#include <iostream>
#include <armadillo>
#include <math.h>
using namespace std;
using namespace arma;

class GenerateMatrix
{
public:
	GenerateMatrix(int m, int a, int b, int c);
	GenerateMatrix(vector<int> exp);
	int red();
private:

	void generateMatrix();
	void reduceFirst();

	void printMatrix();
	int calcNR(int m, int a);


	arma::Mat<int> M;
	int m;
	int a;
	vector<int> exp;
	int max_colum;


};




#endif /* GENERATEMATRIX_H_ */
