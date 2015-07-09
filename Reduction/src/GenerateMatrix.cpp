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
GenerateMatrix::~GenerateMatrix() {

	this->M.clear();
}

int GenerateMatrix::red() {
	this->generateMatrix();

	//cout << "NR: " << calcNR(this->m, this->a) << endl;
	this->nr = calcNR(this->m, this->a);
	this->reduceFirst();
	this->reduceOthers();
	//cout << "Reduced" << endl;
	this->removeRepeat();
	//this->printMatrix();
	this->cleanMatrix();
	//this->printMatrix();
	Otimizator ot(this->M, this->exp);
	this->M = ot.optimize();

	//this->printMatrix();

	//ContXor contaXor(this->M, ot.getMatchs(), this->max_colum);

	return this->calculateXor(ot.getMatchs());
}

/**
 * Método para calcular o número de XORs
 */

int GenerateMatrix::calculateXor(std::map<int, pair<int, int> > matches) {
	int count = 0;
	arma::Row<int> row(this->max_colum);
	for (int i = 0; i < this->max_colum; i++)
		row[i] = -1;

	int rows_size = this->M.n_rows;
	arma::Row<int> row_first = this->M.row(0);
	for (int j = 0; j < row_first.size(); j++) {
		int countT = 0;
		int element = row_first[j];
		if (element != -1) {
			for (int i = 1; i < rows_size; i++) {
				arma::Row<int> row_to_compare = this->M.row(i);
				if (row_to_compare[j] != -1) {
					countT++;
				}
			}
		}
		row[j] = countT;
	}

	for (int i = this->m - 1; i < this->max_colum; i++) {
		int tx = row[i];
		count = count + tx;
	}
	count = count + matches.size();
	return count;
}

void GenerateMatrix::reduceOthers() {
	std::vector<arma::Mat<int> > subMatrix = this->getSubMatrix();
	std::vector<arma::Mat<int> >::const_iterator cii;
	std::vector<ThreadMatrix*> objs;

	int i = 0;
	/*for (int j = 0; j < 1; j++) {
	 ThreadMatrix* thre = new ThreadMatrix(subMatrix[0], this->exp, this->nr, i);
	 thre->start();
	 objs.push_back(thre);
	 i++;
	 }
	 for (int j = 0; j < 1; j++) {
	 objs[j]->join();
	 }
	 for (int j = 0; j < 1; j++) {
	 this->M.insert_rows(this->M.n_rows, objs[j]->getM());
	 }*/
	for (cii = subMatrix.begin(); cii != subMatrix.end(); ++cii) {
		ThreadMatrix* thre = new ThreadMatrix(*cii, this->exp, this->nr, i);
		thre->start();
		objs.push_back(thre);
		i++;
	}
	for (int i = 0; i < subMatrix.size(); i++) {
		objs[i]->join();
	}
	for (int i = 0; i < subMatrix.size(); i++) {
		//cout << objs[i]->getM() << endl;
		this->M.insert_rows(this->M.n_rows, objs[i]->getM());
	}

	cout << "DONE!!" << endl;
	for (int i = 1; i < this->M.n_rows; i++) {
		this->cleanReduced(i);
	}
	//this->printMatrix();

	//this->printMatrix();
}
std::vector<arma::Mat<int> > GenerateMatrix::getSubMatrix() {
	std::vector<arma::Mat<int> > matToReturn;
	std::vector<arma::Col<int> > cols;
	for (int i = 0; i < this->M.n_cols; i++) {
		cols.push_back(this->M.col(i));
	}
	//this->printMatrix();
	for (int i = 1; i < this->M.n_rows - 1; i++) {
		arma::Mat<int> matri = this->M.submat(i, 0, i, this->M.n_cols - 1);
		//matri.insert_rows(matri.n_rows);
		//cout << matri <<endl;
		matToReturn.push_back(matri);
	}
	//this->printMatrix();
	return matToReturn;
}
void GenerateMatrix::cleanReduced(int index_row) {
	arma::Row<int> reducedRow = this->M.row(index_row);
	for (int i = 0; i < this->m - 1; i++) {
		reducedRow[i] = -1;
	}
	this->M.shed_row(index_row);
	this->M.insert_rows(index_row, reducedRow);
}

arma::Row<int> GenerateMatrix::reduce(arma::Row<int> rowToReduce, int expoent) {
	int index = this->max_colum - 1;
	arma::Row<int> row(this->max_colum);
	for (int i = 0; i < this->max_colum; i++)
		row[i] = -1;

	for (int i = this->m - 2; i >= 0; i--) {
		int element = rowToReduce[i];
		int indice = index - expoent;
		//cout << "Indice " << indice << endl;
		row[indice] = element;
		index = index - 1;
	}

	//cout << "Row: " << endl;
	//cout << row << endl;

	return row;
}

vector<int> GenerateMatrix::getToReduce() {
	vector<int> toReduce;
	int index = (this->max_colum - 1 - this->m);
	int rows_size = this->M.n_rows;
	for (int i = 1; i < rows_size; i++) {
		arma::Row<int> row = this->M.row(i);
		if (row[index] != -1)
			toReduce.push_back(i);
	}
	return toReduce;
}

void GenerateMatrix::removeRepeat() {
	int rows_size = this->M.n_rows;

	for (int i = 1; i < rows_size; i++) {
		arma::Row<int> row = this->M.row(i);
		int row_size = row.size();
		for (int j = this->m - 1; j < row_size; j++) {
			bool found = false;
			int valueToCompar = row[j];
			if (valueToCompar != -1) {
				for (int k = i + 1; k < rows_size; k++) {
					arma::Row<int> rowToCompare = this->M.row(k);
					int toCompare = rowToCompare[j];
					if (toCompare != -1) {
						if (toCompare == valueToCompar) {
							row[j] = -1;
							rowToCompare[j] = -1;
							found = true;
							//cout << "Removing... 2" << endl;
						}
					}
					this->M.shed_row(k);
					this->M.insert_rows(k, rowToCompare);
					if (found) {
						break;

					}
				}
			}
		}

		this->M.shed_row(i);
		this->M.insert_rows(i, row);
	}
	//cout << "Removing... end" << endl;

}

void GenerateMatrix::cleanMatrix() {

	for (int i = 1; i < this->M.n_rows; i++) {
		bool allZero = true;
		arma::Row<int> row = this->M.row(i);
		int row_size = row.size();
		for (int j = 0; j < row_size; j++) {
			if (row[j] != -1) {
				allZero = false;
				break;
			}
		}
		if (allZero) {
			this->M.shed_row(i);
			//rows_size--;
		}
	}
	cout << "Cleaning... 1" << endl;

}

void GenerateMatrix::reduceFirst() {

	vector<int>::const_iterator cii;
	int row_index = 1;
	cii = this->exp.begin();
	cii++;
	while (cii != this->exp.end()) {

		int expoent = *cii;
		int index = this->max_colum - 1;
		arma::Row<int> row(this->max_colum);
		for (int i = 0; i < this->max_colum; i++)
			row[i] = -1;

		for (int i = this->m - 2; i >= 0; i--) {
			int element = this->M.at(0, i);
			int indice = index - expoent;
			//cout << "Indice " << indice << endl;
			row[indice] = element;
			index = index - 1;
		}
		this->M.insert_rows(row_index, row);
		row_index++;
		cii++;
	}
	//this->printMatrix();
}

void GenerateMatrix::generateMatrix() {

	arma::Mat<int> A;
	arma::Row<int> row(2 * this->m - 1);
	int value = 2 * this->m - 2;

	for (int i = 0; i < 2 * this->m - 1; i++) {
		row[i] = value--;
		//cout << value << endl;

	}
//row[2 * this->m - 1] = 0;

	A.insert_rows(0, row);

//cout << "A: " << endl;
//cout << A << endl;

	this->M = A;
}

int GenerateMatrix::calcNR(int m, int a) {
	int nr = floor((m - 2) / (m - a));
	return nr;
}

void GenerateMatrix::printMatrix() {
	cout << "Matrix: " << endl;
	cout << this->M << endl;
	cout << "-----------------" << endl;
}
