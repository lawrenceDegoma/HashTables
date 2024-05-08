//
// Created by Lawrence Degoma on 5/7/24.
//
#ifndef HASHTABLE_HASHTABLES_CPP
#define HASHTABLE_HASHTABLES_CPP
#include "HashTables.h"

template<typename T>
void quickSort(std::vector<Record<T>> &data, int size){
    int pivot_index = 0;
    int left, right;

    if (size > 1){
        partition(data, size, pivot_index);
        left = pivot_index;
        right = size - pivot_index - 1;
        quickSort(data, left);
        quickSort(data, right);
    }
}

template<typename T>
void partition(std::vector<Record<T>> &data, int size, int &pivot_index){
    int pivot = data[0].key;
    int i=1, j=size-1;
    while (i <= j){
        while (i < size-1 && data[i].key < pivot){
            i++;
        }
        while (data[j].key > pivot){
            j--;
        }

        if (i < j){
            std::swap(data[i], data[j]);
            i++;
            j--;
        }
    }
    std::swap(data[0], data[j]);
    pivot_index = j;
}

template<typename T>
int binarySearch(std::vector<Record<T>> &data, int target, int left, int right){
    if (left <= right){
        int mid = (right + left) / 2;
        if (data[mid].key == target)
            return mid;
        if (data[mid].key < target)
            return binarySearch(data, target, mid+1, right);
        else
            return binarySearch(data, target, left, mid-1);
    }
    return -1;
}

template<typename T>
int HashTable<T>::hash(int key) {
    return key%CAPACITY;
}

template<typename T>
HashTable<T>::HashTable() {
    total_records = 0;
}

template<typename T>
HashTable<T>::HashTable(std::initializer_list<std::pair<int, T>> &list) {
    total_records = 0;
    for (const auto &pair : list){
        insert(pair);
    }
}

template<typename T>
void HashTable<T>::insert(int key, const T& value) {
   int index = hash(key);
   for (auto &record : data[index]){
       if (record.key == key){
           record.value=value;
           return;
       }
   }
   data[index].push_back(Record<T>(key, value));
   total_records++;

   quickSort(data[index], data[index].size());
}

template<typename T>
void HashTable<T>::insert(const std::pair<int, T> &record) {
    insert(record.first, record.second);
}

template<typename T>
T &HashTable<T>::operator[](unsigned int key) {
    int index = hash(key);
    for (auto &record : data[index]){
        if (record.key == key)
            return record.value;
    }
    throw std::out_of_range("Key not found.");
}

template<typename T>
T &HashTable<T>::at(unsigned int key) {
    return operator[](key);
}

template<typename T>
int HashTable<T>::size() {
    return total_records;
}

template<typename T>
bool HashTable<T>::empty() {
    return (total_records==0);
}

template<typename T>
typename HashTable<T>::iterator HashTable<T>::begin() {
    for (size_t i = 0; i < CAPACITY; ++i) {
        if (!data[i].empty()) {
            return data[i].begin();
        }
    }
    return data[0].end();
}

template<typename T>
typename HashTable<T>::iterator HashTable<T>::end() {
    for (size_t i = CAPACITY; i > 0; --i) {
        if (!data[i-1].empty()) {
            return data[i-1].end();
        }
    }
    return data[0].end();
}

template<typename T>
int HashTable<T>::count(int key) {
    int index = hash(key);
    int count = 0;
    for (const auto &record : data[index]){
        if (record.key == key)
            count ++;
    }
    return count;
}

template<typename T>
bool HashTable<T>::contains(int key) {
    int index = hash(key);
    for (const auto &record : data[index]){
        if (record.key == key)
            return true;
    }
    return false;
}

template<typename T>
void HashTable<T>::remove(int key) {
    int index = hash(key);
    auto &records = data[index];
    for (auto iter = records.begin(); iter != records.end(); ++iter){
        if (iter->key == key){
            records.erase(iter);
            total_records--;
            return;
        }
    }
}

template<typename T>
void HashTable<T>::find(int key, bool &found, int &index){
    int hashed = hash(key);
    auto &records = data[hashed];

    if (!records.empty()){
        int result = binarySearch(records, key, 0, records.size()-1);
        if (result != -1){
            found = true;
            index = result;
            return;
        }
    }

    found = false;
    index = -1;
}

#endif