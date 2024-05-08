//
// Created by Lawrence Degoma on 5/7/24.
//

#ifndef HASHTABLE_HASHTABLES_H
#define HASHTABLE_HASHTABLES_H
#include "Record.h"
#include <vector>
#include <initializer_list>
#include <stdexcept>

template <typename T>
class HashTable {
private:
    static const int CAPACITY = 811;
    std::vector<Record<T>> data[CAPACITY];
    int total_records = 0;
    int hash(int key);

public:
    using iterator = typename std::vector<Record<T>>::iterator;
    HashTable();
    HashTable(std::initializer_list<std::pair<int, T>>& list);
    void insert(int key, const T& value);
    void insert(const std::pair<int, T>& record);
    T& operator[](unsigned int);    // throw exception, then crash if key doesn't exist
    T& at(unsigned int);    // throw exception, then crash if key doesn't exist

    int size();
    bool empty();

    // iterator
    iterator begin();
    iterator end();
    int count(int key);    // return the number of keys that equal key in the map
    bool contains(int key);    // returns true if the key exists
    void remove(int key);   // remove the record containing the key
    void find(int key, bool &found, int& index);    // index of collision
};

#include "HashTables.cpp"
#endif //HASHTABLE_HASHTABLES_H
