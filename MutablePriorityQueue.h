/*
 * MutablePriorityQueue.h
 * A simple implementation of mutable priority queues, required by Dijkstra algorithm.
 *
 * Created on: 17/03/2018
 *      Author: João Pascoal Faria
 */

#ifndef SRC_MUTABLEPRIORITYQUEUE_H_
#define SRC_MUTABLEPRIORITYQUEUE_H_

#include <vector>

/**
 * class T must have: (i) accessible field int queueIndex; (ii) operator< defined.
 */

using namespace std;

template <class T>
class MutablePriorityQueue
{
	vector<T *> H;
	void heapifyUp(unsigned i);
	void heapifyDown(unsigned i);
	inline void set(unsigned i, T * x);
public:
	MutablePriorityQueue();
	void insert(T * x);
	T * extractMin();
	void decreaseKey(T * x);
	bool empty();
};

#endif /* SRC_MUTABLEPRIORITYQUEUE_H_ */
