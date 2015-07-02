/*
 * ContXor.h
 *
 *  Created on: Jul 2, 2015
 *      Author: vader
 */

#ifndef CONTXOR_H_
#define CONTXOR_H_
#include <iostream>
#include <armadillo>
#include <map>
#include <math.h>
using namespace std;
using namespace arma;
class ContXor {
public:
	ContXor(arma::Mat<int> M, std::map<int, pair<int,int> > matches, int max_colum);
	virtual ~ContXor();
	int n_xor;
private:
	void calculateXor(arma::Mat<int> M, std::map<int, pair<int,int> > matches);
	int max_column;


};

#endif /* CONTXOR_H_ */
