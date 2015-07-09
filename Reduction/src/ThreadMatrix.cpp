#include "ThreadMatrix.h"

/**
 * Classe responsável por efetuar a redução de cada "submatrix"
 */

ThreadMatrix::ThreadMatrix(arma::Mat<int> matrix, std::vector<int> exp, int nr,
		int id) {
	this->M = matrix;
	this->exp = exp;
	this->max_colum = (2 * exp[0]) - 1;
	this->m = exp[0];
	this->nr = nr;
	this->id = id;
}

/**
 * Geração da redução de cada matrix
 */
inline void ThreadMatrix::generateReduced() {
	cout << "Starting Thread : " << this->id << endl;
	vector<int> toReduce = this->getToReduce();
	while (toReduce.size() > 0) {

		vector<int>::const_iterator cii;
		vector<ExpThread*> tExp;
		int size = this->M.n_rows;

		for (cii = toReduce.begin(); cii != toReduce.end(); cii++) {
			int index_row = *cii;
			ExpThread* expT = new ExpThread(index_row, this->exp,
					this->max_colum, this->m, this->M.row(index_row));
			tExp.push_back(expT);
		}

		for (unsigned int j = 0; j < tExp.size(); j++) {
			tExp[j]->start();
		}
		for (unsigned int j = 0; j < tExp.size(); j++) {
			tExp[j]->join();
		}
		for (unsigned int j = 0; j < tExp.size(); j++) {
			arma::Mat<int> temp = tExp[j]->getM();

			for (unsigned int k = 0; k < temp.n_rows; k++) {
				this->M.insert_rows(size++, temp.row(k));
			}
			this->cleanReduced(tExp[j]->getIndex());
		}

		toReduce = this->getToReduce();
	}
	cout << "Thread : " << this->id << " Finish" << endl;
	this->M.shed_row(0);
}

arma::Mat<int> ThreadMatrix::getM() {
	return this->M;
}

/**
 * Limpar a linha da matriz que já foi reduzida
 */
inline void ThreadMatrix::cleanReduced(int index_row) {
	arma::Row<int> reducedRow = this->M.row(index_row);
	for (int i = 0; i < this->m - 1; i++) {
		reducedRow[i] = -1;
	}
	this->M.shed_row(index_row);
	this->M.insert_rows(index_row, reducedRow);
}

/**
 * Reduzir matriz
 */
inline arma::Row<int> ThreadMatrix::reduce(arma::Row<int> rowToReduce,
		int expoent) {
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

	return row;
}

/**
 * Pegar os indices das linhas que precisam ser reduzidas
 */
inline vector<int> ThreadMatrix::getToReduce() {
	vector<int> toReduce;
	int index = (this->max_colum - 1 - this->m);
	int rows_size = this->M.n_rows;
	for (int i = 0; i < rows_size; i++) {
		arma::Row<int> row = this->M.row(i);
		if (row[index] != -1)
			toReduce.push_back(i);
	}
	return toReduce;
}

/**
 * Remoção dos elementos repetidos
 */
void ThreadMatrix::removeRepeat() {
	int rows_size = this->M.n_rows;
	for (int i = 0; i < rows_size; i++) {
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

