#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <vector>
#include <string>
#include "raylib.h"

class HashTable {
public:
    HashTable(int cap = 60);
    void insert(int key, bool animate = true);
    void search(int key, bool animate = true);
    void remove(int key, bool animate = true);
    void clear();
    void init(int newCapacity);
    void draw(int currentStep = -1);
    void handleRandom();
    void startCollisionAnimation(int index);
    void LoadFromFile();
    enum InitMode { NONE_INIT, RANDOM_HASHTABLE, LOADFILE_HASHTABLE };
    void setInitMode(InitMode mode) { initMode = mode; }
    InitMode getInitMode() const { return initMode; }

    // Step-by-step methods for insert
    void startInsertStep(int key);
    void performInsertStep(int step);
    void revertInsertStep(int step);

    // Step-by-step methods for search
    void startSearchStep(int key);
    void performSearchStep(int step);
    void revertSearchStep(int step);

    // Step-by-step methods for delete
    void startDeleteStep(int key);
    void performDeleteStep(int step);
    void revertDeleteStep(int step);

    // Getter và Setter cho các biến private
    int getHighlightedIndex() const { return highlightedIndex; }
    void setHighlightedIndex(int index) { highlightedIndex = index; }
    int getStepInsertIndex() const { return stepInsertIndex; }
    void setStepInsertIndex(int index) { stepInsertIndex = index; }
    bool getStepCollisionDetected() const { return stepCollisionDetected; }
    const std::vector<int>& getStepCollisionIndices() const { return stepCollisionIndices; }
    void clearStepCollisionIndices() { stepCollisionIndices.clear(); }
    int getStepSearchIndex() const { return stepSearchIndex; }
    int getStepDeleteIndex() const { return stepDeleteIndex; }

    // Reset trạng thái step-by-step
    void resetStepState();

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

    // Step-by-step state
    int stepCurrentIndex = -1; // Current index during operation
    std::vector<int> stepCollisionIndices; // List of collision indices
    bool stepCollisionDetected = false; // Flag for collision detection
    int stepInsertIndex = -1; // Index where key will be inserted
    int stepSearchIndex = -1; // Index where key is found (Search)
    int stepDeleteIndex = -1; // Index where key is deleted (Delete)
};

#endif