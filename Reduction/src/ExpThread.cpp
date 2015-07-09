/*
 * ExpThread.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: vader
 */

#include "ExpThread.h"

ExpThread::ExpThread(int index_row, vector<int> exp, int max_column, int m,
		arma::Row<int> row) {
	this->index_row = index_row;
	this->exp = exp;
	this->max_colum = max_column;
	this->m = m;
	this->row = row;
	this->M = arma::Mat<int>();

}

ExpThread::~ExpThread() {
}

void ExpThread::red() {
	vector<ReductionMatrixThread*> threads;
	vector<int>::const_iterator expo = this->exp.begin();
	int size = this->M.n_rows;

	expo++;

	while (expo != this->exp.end()) {
		int expoent = *expo;
		ReductionMatrixThread* thread = new ReductionMatrixThread(
				this->max_colum, this->row, expoent, this->m);

		threads.push_back(thread);
		expo++;

	}
	for (unsigned int i = 0; i < threads.size(); i++) {
		threads[i]->start();
	}
	for (unsigned int i = 0; i < threads.size(); i++) {
		threads[i]->join();
	}
	for (unsigned int i = 0; i < threads.size(); i++) {
		this->M.insert_rows(size++, threads[i]->getRow());

	}
}

arma::Mat<int> ExpThread::getM() {
	return this->M;
}

int ExpThread::getIndex() {
	return this->index_row;
}
