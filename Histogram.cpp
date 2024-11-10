#include <iostream>
#include "Histogram.h"
#include "QuickSort.h"
#include "ISorter.h"
#include "PairHasher.h"

int cmp_int(const int& a, const int& b) {
	return a - b;
}

int main() {
	int data[7] = { 1,2,3,5,49,1,1 };
	int data2[3] = { 0 ,5 ,50 };
	ISorter<int>* sort = new QuickSorter<int>();
	Sequence<int>* value = new ArraySequence<int>(data, 7);
	Sequence<int>* lim = new ArraySequence<int>(data2, 3);
	SortedSequence<int>* range = new SortedSequence<int>(lim, sort, cmp_int);
	Histogram<int> histogram(value, range);
	IHasher<Pair<int,int>>* hasher = new PairHasher<int>();
	IDictionary<Pair<int, int>, int>* dict = histogram.BuildHistogram(hasher);
	histogram.Output(dict);
	return 0;
}