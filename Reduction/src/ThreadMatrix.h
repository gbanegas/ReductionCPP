/*
 * Otimizator.h
 *
 *  Created on: Jul 1, 2015
 *      Author: vader
 */

#ifndef THREADMATRIX_H_
#define THREADMATRIX_H_
#include <iostream>
#include <armadillo>
#include <math.h>

#include "ReductionMatrixThread.h"
#include "ExpThread.h"
#include "Thread.h"

using namespace std;
using namespace arma;
class ThreadMatrix  : public Thread {
public:
  void *run() {

	  generateReduced();
	 // printf("thread done %lu\n", (long unsigned int)self());
	  return NULL;
   }
  ThreadMatrix(arma::Mat<int> matrix, std::vector<int> exp, int nr, int id);
  inline void generateReduced();
  arma::Mat<int> getM();

private:
  inline vector<int> getToReduce();
  inline arma::Row<int> reduce(arma::Row<int> row, int expoent);
  //void cleanMatrix();
  void removeRepeat();
  inline void cleanReduced(int index_row);

  arma::Mat<int> M;
  std::vector<int> exp;
  int max_colum;
  int m;
  int nr;
  int id;
};


#endif
