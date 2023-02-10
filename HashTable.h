#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <list>
#include "LikedList.h"

using namespace std;


template <typename Key, typename Value>
class HashTable {
public:
    int size_;
    vector<list<pair<Key, Value>>> table_;
    HashTable(int size = 10) : size_(size) {
        table_.resize(size_);
    }

    void put(const Key &key, const Value &value) {
        int hash = hashFunction(key);
        table_[hash].push_back(make_pair(key, value));
    }

    Value get(const Key &key) const {
        int hash = hashFunction(key);
        for (const auto &entry : table_[hash]) {
            if (entry.first == key) {
                return entry.second;
            }
        }
        throw out_of_range("Key not found");
    }

    bool contains(const Key &key) const {
        int hash = hashFunction(key);
        for (const auto &entry : table_[hash]) {
            if (entry.first == key) {
                return true;
            }
        }
        return false;
    }

    void remove(const Key &key) {
        int hash = hashFunction(key);
        for (auto it = table_[hash].begin(); it != table_[hash].end(); ++it) {
            if (it->first == key) {
                table_[hash].erase(it);
                break;
            }
        }
    }

private:
    int hashFunction(Key key) const {
        return key % size_;
    }

};
