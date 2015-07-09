/*
 * ReductionMatrixThread.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: vader
 */

#include "ReductionMatrixThread.h"

ReductionMatrixThread::ReductionMatrixThread(int max_colum,
		arma::Row<int> rowToReduce, int expoent, int m) {
	this->max_colum = max_colum;
	this->rowToReduce = rowToReduce;
	this->expoent = expoent;
	this->m = m;

}

ReductionMatrixThread::~ReductionMatrixThread() {
	// TODO Auto-generated destructor stub
}

inline void ReductionMatrixThread::reduce() {
	int index = this->max_colum - 1;
	arma::Row<int> row(this->max_colum);
	for (int i = 0; i < this->max_colum; i++)
		row[i] = -1;

	for (int i = this->m - 2; i >= 0; i--) {
		int element = rowToReduce[i];
		int indice = index - expoent;
		//cout << "Indice " << indice << endl;
		row[indice] = element;
		index = index - 1;
	}

	this->row = row;
}
arma::Row<int> ReductionMatrixThread::getRow() {
	return this->row;
}

