#pragma once
#include <utility>
#include <ostream>
template <typename T1, typename T2> class Pair {
public:
    T1 item1;
    T2 item2; 

    Pair() {
        item1 = T1();
        item2 = T2();
    }

    Pair(const T1& value1, const T2& value2) {
        item1 = value1;
        item2 = value2;
    }

    Pair(T1&& value1, T2&& value2) {
        item1 = value1;
        item2 = value2;
    }

    Pair(const Pair<T1,T2>& other) {
        item1 = other.item1;
        item2 = other.item2;
    }

    Pair(Pair<T1,T2>&& other) {
        item1 = std::move(other.item1);
        item2 = std::move(other.item2);
    }

    T1 Get1() const {
        return item1;
    }

    T2 Get2() const {
        return item2;
    }

    void Set(const T1& value1, const T2& value2) {
        item1 = value1;
        item2 = value2;
    }

    Pair<T1,T2>& operator=(const Pair<T1,T2>& other) {
        item1 = other.item1;
        item2 = other.item2;
        return *this;
    }

    bool operator==(const Pair<T1,T2>& other) const {
        return (this->Get1()==other.Get1() && this->Get2()==other.Get2());
    }

    friend std::ostream& operator <<(std::ostream& stream, const Pair<T1,T2>& pair) {
        stream << "{" << pair.Get1() << "," << pair.Get2() << "}";
        return stream; 
    }

    /*Pair<T1,T2> Get() {
        Pair<T1,T2> pair[2] = {item1,item2};
        return pair;

    }*/
};