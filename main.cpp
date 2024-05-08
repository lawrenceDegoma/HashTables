#include <iostream>
#include "HashTables.h"

int main() {
    HashTable<int> table;

    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);
    table.insert(4, 40);
    table.insert(810, 200);

    std::cout << "Value at key 2: " << table[2] << std::endl;

    try{
        std::cout << "Value at key 5: " << table.at(5) << std::endl;
    }
    catch (const std::out_of_range &e){
        std::cerr << e.what() << std::endl;
    }

    std::cout << std::endl << "Key 3 exists: " << (table.contains(3) ? "true" : "false") << std::endl;

    std::cout << "Size of hash table: " << table.size() << std::endl;
    std::cout << "Is hash table empty: " << (table.empty() ? "true" : "false") << std::endl;

    // testing iterator with all inserted keys value pairs
    for (auto iter = table.begin(); iter!=table.end(); ++iter) {
        std::cout << "Key: " << iter->key << ", Value: " << iter->value << std::endl;
    }

    // remove key 20
    table.remove(20);

    // retest iterator with updated table to check if 20 was removed
    for (auto iter = table.begin(); iter!=table.end(); ++iter) {
        std::cout << "Key: " << iter->key << ", Value: " << iter->value << std::endl;
    }

    bool found;
    int index;
    table.find(20, found, index);
    if (found) {
        std::cout << "Key 20 found at index: " << index << std::endl;
    } else {
        std::cout << "Key 20 not found" << std::endl;
    }

    return 0;
}
