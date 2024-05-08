//
// Created by Lawrence Degoma on 5/7/24.
//

#ifndef HASHTABLE_RECORD_H
#define HASHTABLE_RECORD_H
template<typename T>
struct Record
{
    int key;
    T value;

    Record(int k, const T& v) : key(k), value(v) {}
};
#endif //HASHTABLE_RECORD_H
