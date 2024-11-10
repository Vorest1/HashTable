#pragma once
#include "IHasher.h"
#include <functional>
#include "Pair.h"
template <typename Tkey>
class PairHasher : public IHasher<Pair<Tkey, Tkey>> {
    public:
        int Hash(const Pair<Tkey, Tkey>& key) const {
            return std::hash<Tkey>{}(key.Get1())+std::hash<Tkey>{}(key.Get2());
        }
};