/*
 * Otimizator.h
 *
 *  Created on: Jul 1, 2015
 *      Author: vader
 */

#ifndef OTIMIZATOR_H_
#define OTIMIZATOR_H_

#include <iostream>
#include <armadillo>
#include <map>
#include <math.h>


using namespace std;
using namespace arma;

class Otimizator{
public:
	Otimizator(arma::Mat<int> matrix, vector<int> exp);
	arma::Mat<int> optimize();

private:
	std::vector<std::pair<int,int> > generatePairs(arma::Col<int> column);
	std::pair<int,int> generateAllPairs();
	void changePair(std::pair<int,int> p);
	void printMatrix();
	void findAndChange(std::pair<int,int> p);
	arma::Col<int> removePair(std::pair<int,int> p, arma::Col<int> column);
	arma::Mat<int> M;
	vector<int> exp;
	int variable;
	std::map<int, pair<int,int> > m;
};




#endif /* OTIMIZATOR_H_ */
