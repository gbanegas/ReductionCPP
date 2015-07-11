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
	this->M.clear();
}

void ExpThread::red() {
	vector<int>::const_iterator expo = this->exp.begin();
	expo++;
	while (expo != this->exp.end()) {
		int expoent = *expo;
		int index = this->max_colum - 1;
		arma::Row<int> rowNew(this->max_colum);
		for (int i = 0; i < this->max_colum; i++)
			rowNew[i] = -1;

		for (int i = this->m - 2; i >= 0; i--) {
			int element = this->row[i];
			int indice = index - expoent;

			rowNew[indice] = element;
			index = index - 1;
		}

		this->M.insert_rows(this->M.n_rows, rowNew);
		expo++;
	}

}

arma::Mat<int> ExpThread::getM() {
	return this->M;
}

int ExpThread::getIndex() {
	return this->index_row;
}
