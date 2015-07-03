#include "ThreadMatrix.h"


ThreadMatrix::ThreadMatrix(arma::Mat<int> matrix,std::vector<int> exp)
{
  this->M = matrix;
  this->exp = exp;
  this->max_colum = (2 * exp[0]) - 1;
  this->m = exp[0];
}

void ThreadMatrix::generateReduced()
{

  vector<int> toReduce = this->getToReduce();
	vector<int>::const_iterator cii;
	int size = this->M.n_rows;
	for (cii = toReduce.begin(); cii != toReduce.end(); cii++) {
		vector<int>::const_iterator expo = this->exp.begin();
		int index_row = *cii;
		//cout << "CI: " << (*cii) << endl;
		expo++;
		while (expo != this->exp.end()) {
			int expoent = *expo;
			//cout << "Expo: " << (*expo) << endl;
			arma::Row<int> reducedRow = this->reduce(this->M.row(index_row),
					expoent);
			this->M.insert_rows(size++, reducedRow);
			//this->printMatrix();
			expo++;
		}
		this->cleanReduced(index_row);
	}
	this->M.shed_row(0);
}

arma::Mat<int> ThreadMatrix::getM()
{
  return this->M;
}

void ThreadMatrix::cleanReduced(int index_row) {
	arma::Row<int> reducedRow = this->M.row(index_row);
	for (int i = 0; i < this->m - 1; i++) {
		reducedRow[i] = -1;
	}
	this->M.shed_row(index_row);
	this->M.insert_rows(index_row, reducedRow);
}

arma::Row<int> ThreadMatrix::reduce(arma::Row<int> rowToReduce, int expoent) {
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

vector<int> ThreadMatrix::getToReduce() {
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

void ThreadMatrix::removeRepeat() {
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

}

void ThreadMatrix::cleanMatrix() {

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

}
