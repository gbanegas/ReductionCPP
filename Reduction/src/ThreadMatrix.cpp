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
	//cout << "Starting Thread : " << this->id << endl;

	for (int i = 0; i < this->nr; i++) {
		vector<int> toReduce = this->getToReduce();
		vector<int>::const_iterator cii;
		int size = this->M.n_rows;

		for (cii = toReduce.begin(); cii != toReduce.end(); cii++) {
			vector<int>::const_iterator expo = this->exp.begin();
			int index_row = *cii;
			expo++;

			while (expo != this->exp.end()) {
				int expoent = *expo;
				arma::Row<int> reducedRow = this->reduce(this->M.row(index_row),
						expoent);
				this->M.insert_rows(size++, reducedRow);
				expo++;

			}
			this->cleanReduced(index_row);

		}

		//cout << "Thread  id : " << this->id << ". In the loop " << i << " of "
		//		<< this->nr << endl;
	}
	//cout << "Thread : " << this->id << " Finish" << endl;
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

