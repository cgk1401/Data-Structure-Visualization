#include "HashTable.hpp"
#include "GUI.hpp"
#include "raylib.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "tinyfiledialogs.h" // Thư viện nhóm dùng để mở file


HashTable::HashTable(int cap) : capacity(cap), size(0) {
    table.resize(capacity, EMPTY);
}

void HashTable::insert(int key, bool animate) {
    int index = hashFunction(key);
    int originalIndex = index;

    collisionIndices.clear();
    for (int i = 0; i < capacity; i++) {
        if (table[i] == key && table[i] != EMPTY && table[i] != DELETED) {
            collisionIndices.push_back(i);
        }
    }

    if (!collisionIndices.empty()) {
        std::cout << "✅ Collision detected at indices: ";
        for (int idx : collisionIndices) std::cout << idx << " ";
        std::cout << "\n";
        if (animate) startCollisionAnimation(0);
        return;
    }

    while (table[index] != EMPTY && table[index] != DELETED) {
        index = (index + 1) % capacity;
        if (index == originalIndex) {
            std::cout << "❌ HashTable is full!\n";
            return;
        }
    }
    table[index] = key;
    size++;
    std::cout << "✅ Inserted " << key << " at index " << index << "\n";
    if (animate) {
        insertX = GetScreenWidth() / 2;
        insertY = GetScreenHeight() / 2;
        insertTargetIndex = index;
        insertProgress = 0.0f;
        isInsertAnimating = true;
        pendingKey = key;
    }
}

void HashTable::search(int key, bool animate) {
    int index = hashFunction(key);
    int start = index;

    while (table[index] != EMPTY) {
        if (table[index] == key) {
            if (animate) highlightedIndex = index;
            std::cout << "✅ Found " << key << " at index " << index << "\n";
            return;
        }
        index = (index + 1) % capacity;
        if (index == start) break;
    }
    if (animate) highlightedIndex = -1;
    std::cout << "❌ Not found " << key << "\n";
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
            std::cout << "✅ Removed " << key << " at index " << index << "\n";
            return;
        }
        index = (index + 1) % capacity;
        if (index == start) break;
    }
    std::cout << "❌ Not found " << key << " to remove\n";
}

void HashTable::clear() {
    table.assign(capacity, EMPTY);
    size = 0;
    isInsertAnimating = false;
    isRemoveAnimating = false;
    isCollisionAnimation = false;
    pendingKey = -1;
    highlightedIndex = -1;
    collisionIndices.clear();
    initMode = NONE_INIT; // Reset trạng thái Init
    std::cout << "✅ HashTable cleared\n";
}

void HashTable::init(int newCapacity) {
    capacity = newCapacity;
    table.assign(capacity, EMPTY);
    size = 0;
    std::cout << "✅ Initialized HashTable with capacity " << capacity << "\n";
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

    // Animation va chạm
    if (isCollisionAnimation) {
        collisionProgress += 0.02f;
        if (collisionProgress >= 1.0f) {
            collisionProgress = 0.0f;
            collisionBlinkCount++;
            if (collisionBlinkCount >= 2) {
                isCollisionAnimation = false;
                collisionIndices.clear();
                collisionBlinkCount = 0;

                // Sau khi nháy đỏ xong, chèn số và bật animation insert
                if (pendingKey != -1) {
                    int index = hashFunction(pendingKey);
                    int originalIndex = index;
                    while (table[index] != EMPTY && table[index] != DELETED) {
                        index = (index + 1) % capacity;
                        if (index == originalIndex) {
                            std::cout << "❌ HashTable is full!\n";
                            pendingKey = -1;
                            return;
                        }
                    }
                    table[index] = pendingKey;
                    size++;
                    std::cout << "✅ Inserted " << pendingKey << " at index " << index << " after collision\n";
                    insertX = GetScreenWidth() / 2;
                    insertY = GetScreenHeight() / 2;
                    insertTargetIndex = index;
                    insertProgress = 0.0f;
                    isInsertAnimating = true;
                    // Không reset pendingKey ngay, để animation dùng
                }
            }
        }
    }

    // Animation di chuyển cho insert
    if (isInsertAnimating) {
        insertProgress += 0.02f;
        float easedInsert = 1 - pow(1 - insertProgress, 3);
        int targetX = startX + (insertTargetIndex % bucketsPerRow) * (bucketWidth + spacingX) + bucketWidth / 2;
        int targetY = startY + (insertTargetIndex / bucketsPerRow) * (bucketHeight + spacingY) + bucketHeight / 2;
        insertX = centerX + (targetX - centerX) * easedInsert;
        insertY = centerY + (targetY - centerY) * easedInsert;
        DrawText(std::to_string(pendingKey).c_str(), insertX - 10, insertY - 10, 20, RED);
        if (insertProgress >= 1.0f) {
            isInsertAnimating = false;
            pendingKey = -1;
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

    // Animation nhảy lên rồi rơi cho remove
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
                std::cout << "✅ Remove animation completed\n";
            }
        }
        DrawText(std::to_string(removedValue).c_str(), removeX, removeY, 20, RED);
    }
}

void HashTable::handleRandom() {
    int randomCount = GetRandomValue(5, std::min(20, capacity));
    std::cout << "✅ Randomizing " << randomCount << " values\n";
    for (int i = 0; i < randomCount; i++) {
        if (size >= capacity) {
            std::cout << "❌ Table is full after " << i << " insertions\n";
            break;
        }
        int value = GetRandomValue(1, 100);
        insert(value, true);
    }
    std::cout << "✅ Random insertion completed with " << size << " values\n";
}

void HashTable::startCollisionAnimation(int index) {
    isCollisionAnimation = true;
    collisionProgress = 0.0f;
    collisionIndex = index;
    collisionBlinkCount = 0;
}

void HashTable::LoadFromFile() {
    clear(); // Xóa bảng hiện tại
    const char* path = tinyfd_openFileDialog(
        "Open HashTable File", "", 0, nullptr, nullptr, 0
    );
    if (path == nullptr) {
        std::cout << "❌ No file selected\n";
        return;
    }

    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        std::cout << "❌ Failed to open file: " << path << "\n";
        return;
    }

    int x;
    while (ifs >> x) {
        insert(x, false); // Thêm mà không cần animation
    }
    ifs.close();
    std::cout << "✅ Loaded HashTable from file: " << path << "\n";
}