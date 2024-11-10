#include <iostream>
#include "HashTable.h"
#include "IDictionary.h"
int main() {
    HashTable<int, int> table = HashTable<int, int>(1);
    table.Add(Pair<int, int>(0, 128));
    table.Add(Pair<int, int>(1, 256));
    table.Add(Pair<int, int>(2, -1));
    table.Add(Pair<int, int>(3, 0));
    table.Add(Pair<int, int>(4, 512));
    table.Add(Pair<int, int>(5, 1024));
    table.Add(Pair<int, int>(6, -32));
    table.Add(Pair<int, int>(7, -64));
    assert(table.Get(0) == 128);
    assert(table.Get(1) == 256);
    assert(table.Get(2) == -1);
    assert(table.Get(3) == 0);
    assert(table.Get(4) == 512);
    assert(table.Get(5) == 1024);
    assert(table.Get(6) == -32);
    assert(table.Get(7) == -64);
    assert(table.ContainsKey(0) == true);
    assert(table.ContainsKey(1) == true);
    assert(table.ContainsKey(2) == true);
    assert(table.ContainsKey(3) == true);
    assert(table.ContainsKey(4) == true);
    assert(table.ContainsKey(5) == true);
    assert(table.ContainsKey(6) == true);
    assert(table.ContainsKey(7) == true);
    assert(table.ContainsKey(8) == false);
    table.Remove(4);
    assert(table.ContainsKey(4) == false);
    assert(table.GetCount() == 7);
    assert(table.GetCapacity() == 16);
    std::cout << "Tests successfully completed" << std::endl;
    return 0;
}