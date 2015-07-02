/*
 * GenerateMatrix.cpp
 *
 *  Created on: Jul 1, 2015
 *      Author: vader
 */
#include "GenerateMatrix.h"

GenerateMatrix::GenerateMatrix(int m, int a, int b, int c) {
	this->m = m;
	this->a = a;
	this->exp.push_back(this->m);
	this->exp.push_back(this->a);
	this->exp.push_back(b);
	this->exp.push_back(c);
	this->exp.push_back(0);
	std::sort(this->exp.begin(), this->exp.end(), std::greater<int>());
	this->max_colum = (2 * m) - 1;
}

GenerateMatrix::GenerateMatrix(vector<int> exp) {
	this->exp = exp;
	std::sort(this->exp.begin(), this->exp.end(), std::greater<int>());
	this->m = this->exp[0];
	this->a = this->exp[1];
	this->max_colum = (2 * this->m) - 1;
}

int GenerateMatrix::red() {
	this->generateMatrix();

	cout << "NR: " << calcNR(this->m, this->a) << endl;
	this->reduceFirst();

	return 0;
}

void GenerateMatrix::reduceFirst() {

	vector<int>::const_iterator cii;
	int row_index = 1;
	cii = this->exp.begin();
	cii++;
	while (cii != this->exp.end()) {
		cout << *cii << endl;
		int expoent = *cii;
		int index = this->max_colum - 1;
		arma::Row<int> row(this->max_colum);
		for (int i = 0; i < this->max_colum; i++)
			row[i] = -1;

		for (int i = this->m - 2; i >= 0; i--) {
			int element = this->M.at(0, i);
			int indice = index - expoent;
			cout << "Indice " << indice << endl;
			row[indice] = element;
			index = index - 1;
		}
		this->M.insert_rows(row_index, row);
		row_index++;
		cii++;
	}
	this->printMatrix();
}

void GenerateMatrix::generateMatrix() {

	arma::Mat<int> A;
	arma::Row<int> row(2 * this->m - 1);
	int value = 2 * this->m - 2;

	for (int i = 0; i < 2 * this->m - 1; i++) {
		row[i] = value--;
		cout << value << endl;

	}
	//row[2 * this->m - 1] = 0;

	A.insert_rows(0, row);

//cout << "A: " << endl;
//cout << A << endl;

	this->M = A;
}

int GenerateMatrix::calcNR(int m, int a) {
	int nr = floor((m - 2) / (m - a)) + 1;
	return nr;
}

void GenerateMatrix::printMatrix() {
	cout << "Matrix: " << endl;
	cout << this->M << endl;
	cout << "-----------------" << endl;
}

