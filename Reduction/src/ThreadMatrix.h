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

using namespace std;
using namespace arma;
class ThreadMatrix  : public Thread {
public:
  void *run() {
       for (int i = 0; i < 5; i++) {
           printf("thread %lu running - %d\n",  (long unsigned int)self(), i+1);
           sleep(2);
       }
       printf("thread done %lu\n", (long unsigned int)self());
       return NULL;
   }
  ThreadMatrix(arma::Mat<int> matrix, , std::vector<int> exp);
  void generateReduced();
  arma::Mat<int> getM();

private:
  vector<int> getToReduce();
  arma::Row<int> reduce(arma::Row<int> row, int expoent);
  void cleanMatrix();
  void removeRepeat();
  void cleanReduced(int index_row);

  arma::Mat<int> M;
  std::vector<int> exp;
}


#endif
