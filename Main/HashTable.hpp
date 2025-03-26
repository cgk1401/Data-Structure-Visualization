#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <vector>
#include <iostream>

class HashTable {
private:
    std::vector<int> table;
    int capacity;
    int size;
    const int EMPTY = -1;
    const int DELETED = -2;
    int highlightedIndex = -1;
    int hashFunction(int key) { return key % capacity; }
    void rehash();
    float progress = 0.0f; // Tiến trình animation từ 0.0 -> 1.0
    bool isInitializing = false; // Cờ để kiểm tra đang Init
public:
    HashTable(int cap = 10);
    void insert(int key);
    void search(int key);
    void remove(int key);
    void display(); 
    void drawHashTable();
    HashTable& operator=(const HashTable& other);
    void init(int newCapacity);
};

#endif
