/*
 * ReductionMatrixThread.h
 *
 *  Created on: Jul 8, 2015
 *      Author: vader
 */

#ifndef REDUCTIONMATRIXTHREAD_H_
#define REDUCTIONMATRIXTHREAD_H_
#include <armadillo>
#include <math.h>

#include "Thread.h"

using namespace std;
using namespace arma;

class ReductionMatrixThread: public Thread {
public:
	void *run() {

		reduce();
		// printf("thread done %lu\n", (long unsigned int)self());
		return NULL;
	}
	ReductionMatrixThread(int max_colum,arma::Row<int> rowToReduce,
			int expoent, int m);
	virtual ~ReductionMatrixThread();
	void reduce();
	arma::Row<int> getRow();
private:
	int max_colum;
	arma::Row<int> rowToReduce;
	int expoent;
	int m;
	arma::Row<int> row;
};

#endif /* REDUCTIONMATRIXTHREAD_H_ */
