#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <vector>
#include <string>
#include "raylib.h"

class HashTable {
public:
    HashTable(int cap = 10);
    void insert(int key, bool animate = true);
    void search(int key, bool animate = true);
    void remove(int key, bool animate = true);
    void clear();
    void init(int newCapacity);
    void draw();
    void handleRandom();
    void startCollisionAnimation(int index);
    void LoadFromFile();
    enum InitMode { NONE_INIT, RANDOM_HASHTABLE, LOADFILE_HASHTABLE };
    void setInitMode(InitMode mode) { initMode = mode; }
    InitMode getInitMode() const { return initMode; }
private:
    std::vector<int> table;
    int capacity, size;
    float progress = 0.0f;
    bool isCollisionAnimation = false;
    float collisionProgress = 0.0f;
    int collisionIndex = -1;
    int collisionBlinkCount = 0;
    std::vector<int> collisionIndices;
    int pendingKey = -1;
    bool isRemoveAnimating = false;
    bool isJumping = false;
    float removeProgress = 0.0f;
    int removeIndex = -1;
    int removeX = 0, removeY = 0;
    int removedValue = -1;
    int highlightedIndex = -1;
    static const int EMPTY = -1;
    static const int DELETED = -2;
    int hashFunction(int key) const { return key % capacity; }
    InitMode initMode = NONE_INIT;
};

#endif