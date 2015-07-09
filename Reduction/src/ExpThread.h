/*
 * ExpThread.h
 *
 *  Created on: Jul 8, 2015
 *      Author: vader
 */

#ifndef EXPTHREAD_H_
#define EXPTHREAD_H_

#include <armadillo>
#include <math.h>

#include "Thread.h"
#include "ThreadMatrix.h"

using namespace std;
using namespace arma;

class ExpThread: public Thread {
public:
	void *run() {

		red();
		// printf("thread done %lu\n", (long unsigned int)self());
		return NULL;
	}
	ExpThread(int index_row, vector<int> exp, int max_column, int m,
			arma::Row<int> row);
	virtual ~ExpThread();
	void red();
	arma::Mat<int> getM();
	int getIndex();
private:
	int index_row;
	vector<int> exp;
	int max_colum;
	int m;
	arma::Row<int> row;
	arma::Mat<int> M;
};

#endif /* EXPTHREAD_H_ */
