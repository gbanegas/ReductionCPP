/*
 * ContXor.cpp
 *
 *  Created on: Jul 2, 2015
 *      Author: vader
 */

#include "ContXor.h"

ContXor::ContXor(arma::Mat<int> M, std::map<int, pair<int, int> > matches, int max_colum) {
	this->n_xor = 0;
	this->max_column = max_colum;
	this->calculateXor(M, matches);


}

ContXor::~ContXor() {
	// TODO Auto-generated destructor stub
}

void ContXor::calculateXor(arma::Mat<int> M,
		std::map<int, pair<int, int> > matches) {
	int index = this->max_column - 1;
	arma::Row<int> row(this->max_column);
	for (int i = 0; i < this->max_column; i++)
		row[i] = -1;

}

