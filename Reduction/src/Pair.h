/*
 * Pair.h
 *
 *  Created on: Jul 1, 2015
 *      Author: vader
 */

#ifndef PAIR_H_
#define PAIR_H_

class Pair {
public:
	Pair(int p1, int p2);
	//return true if the messages are equal, false otherwise
	inline bool operator ==(const Pair &b) const {
		return ((b.p1 == p1) && (b.p2 == p2));
	}

	int p1;
	int p2;
};

#endif /* PAIR_H_ */
