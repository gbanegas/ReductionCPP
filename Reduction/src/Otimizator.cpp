/*
 * Otimizator.cpp
 *
 *  Created on: Jul 1, 2015
 *      Author: vader
 */

#include "Otimizator.h"

Otimizator::Otimizator(arma::Mat<int> matrix, vector<int> exp) {
	this->M = matrix;
	this->exp = exp;
	this->variable = exp[0] * 2 - 1;

}

arma::Mat<int> Otimizator::optimize() {
	bool isToStop = false;
	while (!isToStop) {

		std::pair<int, int> pair = this->generateAllPairs();
		if (pair.first == -1) {
			isToStop = true;
			break;
		}
		this->changePair(pair);
		//this->printMatrix();

	}

	//std::map<int, std::pair<int, int> >::iterator iter;

	//for (iter = this->m.begin(); iter != this->m.end(); ++iter) {
	//	cout << " variavel " << iter->first << " pair : " << iter->second.first
	//			<< "," << iter->second.second << endl;
	//}

	return this->M;
}

void Otimizator::changePair(std::pair<int, int> p) {

	this->m[this->variable] = p;
	this->findAndChange(p);
	this->variable++;
}

void Otimizator::findAndChange(std::pair<int, int> p) {
	int cols_size = this->M.n_cols;
	for (int i = 0; i < cols_size; i++) {
		vector<std::pair<int, int> > result = this->generatePairs(
				this->M.col(i));
		if (std::find(result.begin(), result.end(), p) != result.end()) {
			arma::Col<int> c = this->removePair(p, this->M.col(i));
			this->M.shed_col(i);
			this->M.insert_cols(i, c);
		}
	}
}

arma::Col<int> Otimizator::removePair(std::pair<int, int> p,
		arma::Col<int> column) {
	int col_size = column.size();
	for (int i = 0; i < col_size; i++) {
		if (column[i] == p.first) {
			column[i] = this->variable;
		}

	}
	for (int i = 0; i < col_size; i++) {
		if (column[i] == p.second) {
			column[i] = -1;
		}

	}

	return column;
}

std::pair<int, int> Otimizator::generateAllPairs() {
	std::map<std::pair<int, int>, int> allPairs;
	int cols_size = this->M.n_cols;
	for (int i = 0; i < cols_size; i++) {
		vector<std::pair<int, int> > pairs = this->generatePairs(
				this->M.col(i));
		vector<std::pair<int, int> >::const_iterator cii = pairs.begin();
		while (cii != pairs.end()) {
			std::pair<int, int> p = *cii;
			if (allPairs.count(p)) {
				allPairs[p] = allPairs[p] + 1;
			} else {
				allPairs[p] = 1;
			}
			cii++;
		}
	}
	std::pair<int, int> toReturn(-1, -1);
	int index = 1;
	std::map<std::pair<int, int>, int>::iterator iter;

	for (iter = allPairs.begin(); iter != allPairs.end(); ++iter) {
		if (iter->second > index) {
			toReturn = iter->first;
			index = iter->second;
		}
	}

	return toReturn;
}

vector<std::pair<int, int> > Otimizator::generatePairs(arma::Col<int> column) {
	vector<std::pair<int, int> > result;
	int column_size = column.size();
	for (int i = 1; i < column_size; i++) {
		if (column[i] != -1) {
			int p1 = column[i];
			for (int j = i + 1; j < column_size; j++) {
				int p2 = column[j];
				if (p2 != -1) {
					if (p1 > p2) {
						result.push_back(std::pair<int, int>(p1, p2));
					} else {
						result.push_back(std::pair<int, int>(p2, p1));
					}
				}
			}
		}
	}
	return result;
}

std::map<int, pair<int, int> > Otimizator::getMatchs() {
	return this->m;
}

void Otimizator::printMatrix() {
	cout << "Matrix_1: " << endl;
	cout << this->M << endl;
	cout << "-----------------" << endl;
}
