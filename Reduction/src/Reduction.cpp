//============================================================================
// Name        : Reduction.cpp
// Author      : Gustavo Banegas
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <armadillo>
#include <fstream>

#include "GenerateMatrix.h"

#include <sstream>

#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace std;
using namespace arma;

std::vector<std::string> &split(const std::string &s, char delim,
		std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

std::string removechars(const std::string& source, const std::string& chars) {
	std::string result = "";
	for (unsigned int i = 0; i < source.length(); i++) {
		bool foundany = false;
		for (unsigned int j = 0; j < chars.length() && !foundany; j++) {
			foundany = (source[i] == chars[j]);
		}
		if (!foundany) {
			result += source[i];
		}
	}
	return result;
}

int main() {
	string line;
	ofstream writefile;
	writefile.open("result_teste_1.txt");
	ifstream myfile;
	myfile.open("pol_1.txt");
	std::vector<std::vector<int> > exps;
	std::map<std::vector<int>, std::string> vector_string;
	while (getline(myfile, line)) {
		std::string resultS;
		resultS = "[";
		vector<int> exp;
		std::vector<std::string> splited = split(line, '+');
		std::vector<std::string>::const_iterator cii;
		for (cii = splited.begin(); cii != splited.end() - 1; ++cii) {
			std::string re = removechars(*cii, "x^ ");
			if (re.empty())
				re = "1";
			resultS += re;
			resultS += ",";
			//cout << re << endl;
			exp.push_back(atoi(re.c_str()));
		}
		cout << line << '\n';

		exp.push_back(0);
		resultS += "0]:";
		exps.push_back(exp);
		vector_string[exp] = resultS;
		GenerateMatrix* matrix = new GenerateMatrix(exp);
		int result = matrix->red();
		//char *intStr = itoa(result);
		string str = SSTR(result);
		resultS += str;
		writefile << resultS << "\n";
		cout << resultS  << endl;

		//cout << "Result : " << result << endl;
	}
	writefile.close();

	// prints !!!Hello World!!!
	return 0;
}
