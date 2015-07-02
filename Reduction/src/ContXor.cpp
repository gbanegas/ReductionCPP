/*
 * ContXor.cpp
 *
 *  Created on: Jul 2, 2015
 *      Author: vader
 */

#include "ContXor.h"

ContXor::ContXor(arma::Mat<int> M, std::map<int, pair<int,int> > matches) {
	this->n_xor =0;
	this->calculateXor(M, matches);

}

ContXor::~ContXor() {
	// TODO Auto-generated destructor stub
}

void ContXor::calculateXor(arma::Mat<int> M, std::map<int, pair<int,int> > matches){

}

