#pragma once
#include "ArraySequence.h"
#include "IDictionary.h"
#include "SortedSequence.h"
#include "HashTable.h"
#include <utility>

template <typename Tkey> 
class Histogram {
private:
	Sequence<Tkey>* elems;
	SortedSequence<Tkey>* range;
public:
	Histogram(Sequence<Tkey>* other, SortedSequence<int>* other_range) {
		elems = other;
		range = other_range;
	}
	Histogram(Histogram<Tkey>& other) {
		elems = other.elems;
		range = other.range;
	}
	Histogram(Histogram<Tkey>&& other) {
		elems = std::move(other.elems);
		range = std::move(other.range);
	}
	~Histogram() {
		delete elems;
		delete range;
	}
	int NumberRange(Pair<Tkey, Tkey> range) {
		int number = 0;
		for (int i = 0; i < elems->GetLength(); i++) {
			if (range.Get1() < elems->Get(i) && elems->Get(i) < range.Get2()) {
				number++;
			}
		}
		return number;
	}
	IDictionary<Pair<Tkey, Tkey>, int>* BuildHistogram(IHasher<Pair<Tkey, Tkey>>* other) {
		IDictionary<Pair<Tkey, Tkey>, int>* hist = new HashTable<Pair<Tkey, Tkey>, int>(other);
		for (int i = 0; i < range->GetLength() - 1; i++) {
			Pair<Tkey, Tkey> span(range->Get(i), range->Get(i + 1));
			hist->Add({span, NumberRange(span)});
		}
		return hist;
	}
	void Output(IDictionary<Pair<Tkey, Tkey>, int>* histogram) {
		for (int i = 0; i < range->GetLength() - 1; i++) {
			std::cout << range->Get(i) << "-" << range->Get(i + 1) << ":" << histogram->Get({range->Get(i), range->Get(i + 1)}) << std::endl;
		}
	}
};