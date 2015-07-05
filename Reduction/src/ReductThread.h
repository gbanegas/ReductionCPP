/*
 * ReductThread.h
 *
 *  Created on: Jul 4, 2015
 *      Author: vader
 */

#ifndef REDUCTTHREAD_H_
#define REDUCTTHREAD_H_

#include "Thread.h"
#include "GenerateMatrix.h"

class ReductThread : public Thread{
public:
	ReductThread();
	virtual ~ReductThread();
};

#endif /* REDUCTTHREAD_H_ */
