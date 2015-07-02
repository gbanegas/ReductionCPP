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

#include "Otimizator.h"

using namespace std;
using namespace arma;

class GenerateMatrix
{
public:
	GenerateMatrix(int m, int a, int b, int c);
	GenerateMatrix(vector<int> exp);
	int red();
private:

	vector<int> getToReduce();
	void generateMatrix();
	void reduceFirst();
	void reduceOthers();

	arma::Row<int> reduce(arma::Row<int> row, int expoent);
	void cleanMatrix();
	void removeRepeat();
	void cleanReduced(int index_row);
	void printMatrix();
	int calcNR(int m, int a);


	arma::Mat<int> M;
	int m;
	int a;
	vector<int> exp;
	int max_colum;


};




#endif /* GENERATEMATRIX_H_ */
