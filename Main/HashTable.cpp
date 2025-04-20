#include "HashTable.hpp"
#include "GUI.hpp"
#include "raylib.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "tinyfiledialogs.h"

HashTable::HashTable(int cap) : capacity(cap), size(0) {
    table.resize(capacity, EMPTY);
}

void HashTable::insert(int key, bool animate) {
    int index = hashFunction(key);
    int originalIndex = index;

    collisionIndices.clear();
    while (table[index] != EMPTY && table[index] != DELETED) {
        if (table[index] == key && animate) {
            collisionIndices.push_back(index);
            pendingKey = key;
            startCollisionAnimation(index);
            return;
        }
        index = (index + 1) % capacity;
        if (index == originalIndex) {
            return;
        }
    }
    table[index] = key;
    size++;
}

void HashTable::search(int key, bool animate) {
    int index = hashFunction(key);
    int start = index;

    while (table[index] != EMPTY) {
        if (table[index] == key) {
            if (animate) highlightedIndex = index;
            return;
        }
        index = (index + 1) % capacity;
        if (index == start) break;
    }
    if (animate) highlightedIndex = -1;
}

void HashTable::remove(int key, bool animate) {
    int index = hashFunction(key);
    int start = index;
    while (table[index] != EMPTY) {
        if (table[index] == key && !isRemoveAnimating) {
            if (animate) {
                removeX = 300 + (index % 10) * (80 + 10) + 30;
                removeY = 150 + (index / 10) * (50 + 30) + 15;
                removeIndex = index;
                removeProgress = 0.0f;
                isRemoveAnimating = true;
                isJumping = true;
                removedValue = table[index];
            }
            table[index] = DELETED;
            size--;
            return;
        }
        index = (index + 1) % capacity;
        if (index == start) break;
    }
}

void HashTable::clear() {
    table.assign(capacity, EMPTY);
    size = 0;
    isRemoveAnimating = false;
    isCollisionAnimation = false;
    highlightedIndex = -1;
    collisionIndices.clear();
    pendingKey = -1;
    initMode = NONE_INIT;
}

void HashTable::init(int newCapacity) {
    capacity = newCapacity;
    table.assign(capacity, EMPTY);
    size = 0;
}

void HashTable::draw() {
    int bucketWidth = 80;
    int bucketHeight = 50;
    int startX = GetScreenWidth() / 5 + 50;
    int startY = 150;
    int bucketsPerRow = std::min(10, capacity);
    int spacingX = 10;
    int spacingY = 30;

    float centerX = GetScreenWidth() / 2;
    float centerY = GetScreenHeight() / 2;

    if (progress < 1.0f) progress += 0.02f;
    float easedProgress = 1 - pow(1 - progress, 3);
    if (isCollisionAnimation) {
        collisionProgress += 0.02f;
        if (collisionProgress >= 1.0f) {
            collisionProgress = 0.0f;
            collisionBlinkCount++;
            if (collisionBlinkCount >= 2) {
                isCollisionAnimation = false;
                collisionIndices.clear();
                collisionBlinkCount = 0;
                if (pendingKey != -1) {
                    int key = pendingKey;
                    pendingKey = -1;
                    int index = hashFunction(key);
                    int originalIndex = index;
                    while (table[index] != EMPTY && table[index] != DELETED) {
                        index = (index + 1) % capacity;
                        if (index == originalIndex) {
                            return;
                        }
                    }
                    table[index] = key;
                    size++;
                }
            }
        }
    }
    BeginScissorMode(GetScreenWidth() / 5, 0, GetScreenWidth() - GetScreenWidth() / 5, GetScreenHeight());
    {
        for (int i = 0; i < capacity; i++) {
            int row = i / bucketsPerRow;
            int col = i % bucketsPerRow;
            int targetX = startX + col * (bucketWidth + spacingX);
            int targetY = startY + row * (bucketHeight + spacingY);
            int x = centerX + (targetX - centerX) * easedProgress;
            int y = centerY + (targetY - centerY) * easedProgress;

            Color bucketColor = YELLOW;
            if (isCollisionAnimation && std::find(collisionIndices.begin(), collisionIndices.end(), i) != collisionIndices.end()) {
                bucketColor = (fmod(collisionProgress, 0.5f) < 0.25f) ? RED : YELLOW;
            }
            else if (i == highlightedIndex) {
                bucketColor = PINK;
            }

            DrawRectangle(x, y, bucketWidth, bucketHeight, bucketColor);
            DrawRectangleLines(x, y, bucketWidth, bucketHeight, BLACK);

            if (progress >= 1.0f && table[i] != EMPTY && table[i] != DELETED) {
                std::string value = std::to_string(table[i]);
                DrawText(value.c_str(), x + 30, y + 15, 20, RED);
            }

            std::string indexStr = std::to_string(i);
            DrawText(indexStr.c_str(), x + 35, y - 20, 20, WHITE);
        }
    }
    EndScissorMode();
    if (isRemoveAnimating) {
        removeProgress += 0.05f;
        if (isJumping) {
            float jumpHeight = bucketHeight / 15;
            removeY -= jumpHeight * (removeProgress / 0.5f);
            if (removeProgress >= 0.5f) {
                isJumping = false;
                removeProgress = 0.0f;
            }
        }
        else {
            removeY += removeProgress * 20;
            if (removeY > GetScreenHeight()) {
                isRemoveAnimating = false;
                removeIndex = -1;
                removedValue = -1;
            }
        }
        DrawText(std::to_string(removedValue).c_str(), removeX, removeY, 20, RED);
    }
}

void HashTable::handleRandom() {
    int randomCount = GetRandomValue(5, std::min(20, capacity));
    for (int i = 0; i < randomCount; i++) {
        if (size >= capacity) {
            break;
        }
        int value = GetRandomValue(1, 100);
        insert(value, true);
    }
}

void HashTable::startCollisionAnimation(int index) {
    isCollisionAnimation = true;
    collisionProgress = 0.0f;
    collisionIndex = index;
    collisionBlinkCount = 0;
}

void HashTable::LoadFromFile() {
    clear();
    const char* path = tinyfd_openFileDialog(
        "Open HashTable File", "", 0, nullptr, nullptr, 0
    );
    if (path == nullptr) {
        return;
    }

    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        return;
    }
    int x;
    while (ifs >> x) {
        insert(x, false);
    }
    ifs.close();
}