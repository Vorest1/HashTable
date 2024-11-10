#pragma once 
#include "IHasher.h"
#include "STLHasher.h"
#include "IDictionary.h"
#include "Pair.h"
#include "ArraySequence.h"
#include "Array.h"
template <typename Tkey, typename Tvalue>
class HashTable : public IDictionary<Tkey, Tvalue> {
    using CollisionList = ArraySequence<Pair<Tkey, Tvalue>>;
    private:
        DynamicArray<CollisionList>* associativeArray;
        IHasher<Tkey>* hasher;
        int count;
    public:
        HashTable() {
            count = 0;
            this->associativeArray = new DynamicArray<CollisionList>(1);
            //this->associativeArray->Resize(1);
            hasher = new STLHasher<Tkey>();
        }

        HashTable(int capacity) {
            count = 0;
            this->associativeArray = new DynamicArray<CollisionList>(capacity);
            //this->associativeArray->Resize(capacity);
            this->hasher = new STLHasher<Tkey>();
        }

        HashTable(IHasher<Tkey>* other) {
            count = 0;
            associativeArray = new DynamicArray<ArraySequence<Pair<Tkey, Tvalue>>>();
            hasher = other;
        }

        HashTable(const HashTable<Tkey, Tvalue>& other) {
            this->associativeArray = other.associativeArray;
            this->hasher = other.hasher;
            this->count = other.count;
        }

        HashTable(HashTable<Tkey, Tvalue>&& other) {
            this->associativeArray = std::exchange(other.associativeArray, nullptr);
            this->hasher = std::exchange(other.hasher, nullptr);
            this->count = std::exchange(other.count, 0);
        }

        ~HashTable() {
            delete associativeArray;
            delete hasher;
        }

        HashTable<Tkey, Tvalue>& operator=(const HashTable<Tkey, Tvalue>& other) {
            delete this->associativeArray;
            this->associativeArray = other.associativeArray;
            delete this->hasher;
            this->hasher = other.hasher;
            this->count = other.count;
        }

        HashTable<Tkey, Tvalue>& operator=(HashTable<Tkey, Tvalue>&& other) {
            delete this->associativeArray;
            this->associativeArray = std::exchange(other.associativeArray, nullptr);
            delete this->hasher;
            this->hasher = std::exchange(other.hasher, nullptr);
            this->count = std::exchange(other.count, 0);
        }

        int GetCount() const {
            return count;
        }

        int GetCapacity() const {
            return associativeArray->GetSize();
        }
        
        Tvalue& Get(const Tkey& key) const {
            CollisionList& collisionList = (*associativeArray)[Hash(key)];
            for(int i = 0; i < collisionList.GetLength(); i++) {
                Pair<Tkey,Tvalue>& record = collisionList.Get(i);
                if(record.Get1() == key) {
                    return record.item2;
                }
            }
            throw std::out_of_range("Value was not found");
        }

        bool ContainsKey(const Tkey& key) const {
            CollisionList& collisionList = (*associativeArray)[Hash(key)];
            for(int i = 0; i < collisionList.GetLength(); i++) {
                Pair<Tkey,Tvalue>& record = collisionList.Get(i);
                if(record.Get1() == key) {
                    return true;
                }
            }
            return false;
        }


        int Hash(const Tkey& key) const {
            return hasher->Hash(key) % this->GetCapacity();
        }

        bool NeedToReconstruct() const {
            return count > 0.8*this->GetCapacity();
        }

        IDictionary<Tkey, Tvalue>* Add(Pair<Tkey, Tvalue> record) {
            if (associativeArray->GetSize() == 0) {
                associativeArray->Resize(1);
            }
            if (ContainsKey(record.Get1())) {
                throw std::invalid_argument("Key already is in table");
            }
            if (NeedToReconstruct()) {
                DynamicArray<CollisionList>* newTable = new DynamicArray<CollisionList>(associativeArray->GetSize() * 2);
                //newTable->Resize(associativeArray->GetSize() * 2);
                for (int i = 0; i < associativeArray->GetSize(); i++) {
                    CollisionList& collisionList = (*associativeArray)[i];
                    if(collisionList.GetLength()!=0) {
                        for (int i = 0; i < collisionList.GetLength(); i++) {
                            Pair<Tkey, Tvalue>& listRecord = collisionList.Get(i);
                            ((*newTable)[hasher->Hash(listRecord.Get1()) % newTable->GetSize()]).Append(listRecord);
                        }
                    }
                } 
                delete this->associativeArray;
                this->associativeArray = newTable;
            }
            ((*associativeArray)[Hash(record.Get1())]).Append(record);
            this->count++;
            return this;
        }

        void Remove(const Tkey& key) {
            if (ContainsKey(key) == false) 
                throw std::out_of_range("Key was not found");
            CollisionList& collisionList = (*associativeArray)[Hash(key)];
            for (int i = 0; i < collisionList.GetLength(); i++) {
                if ((collisionList[i]).Get1() == key) {
                    collisionList.Remove(i);
                    break;
                }
            }
            this->count--;
        }

       /* template<typename T> 
        IDictionary<Sequence<T>*, int> GetHistogram(Sequence<T>* seq, bool (*func)(T), T sign, int (*cmp)(T,T)){
            Sequence<T>* result = seq->Where(func);
            Sequence<T>* less = new ArraySequence<T>();
            Sequence<T>* equal = new ArraySequence<T>();
            Sequence<T>* greater = new ArraySequence<T>();
            HashTable<Sequence<T>*, int> histogram = HashTable<Sequence<T>*, int>(1);
            int count = 0;
            for(int i = 0; i < result->GetLength(); i++) {
                if(cmp(result->Get(i), sign) < 0){
                    less->Append(result->Get(i));
                    count++;
                }
            }
            Pair<Sequence<T>*, int> record1(less, count);
            histogram.Add(record1);
            count = 0;

            for(int i = 0; i < result->GetLength(); i++) {
                if(cmp(result->Get(i), sign) == 0){
                    equal->Append(result->Get(i));
                    count++;
                }
            }
            Pair<Sequence<T>*, int> record2(equal, count);
            histogram.Add(record2);
            count = 0;

            for(int i = 0; i < result->GetLength(); i++) {
                if(cmp(result->Get(i), sign) > 0){
                    greater->Append(result->Get(i));
                    count++;
                }
            }
            Pair<Sequence<T>*, int> record3(greater, count);
            histogram.Add(record3);
            count = 0;

            return histogram;

        }
        */
};