﻿#include "HashTable.hpp"
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
        collisionIndices.push_back(index);
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
    stepCollisionIndices.clear();
    pendingKey = -1;
    initMode = NONE_INIT;
    stepCurrentIndex = -1;
    stepCollisionDetected = false;
    stepInsertIndex = -1;
}

void HashTable::init(int newCapacity) {
    capacity = newCapacity;
    table.assign(capacity, EMPTY);
    size = 0;
    progress = 0.0f;
    isCollisionAnimation = false;
    isRemoveAnimating = false;
    highlightedIndex = -1;
    collisionIndices.clear();
    stepCollisionIndices.clear();
    pendingKey = -1;
    collisionProgress = 0.0f;
    removeProgress = 0.0f;
    removeIndex = -1;
    removedValue = -1;
    stepCurrentIndex = -1;
    stepCollisionDetected = false;
    stepInsertIndex = -1;
}

void HashTable::draw(int currentStep) {
    float bucketWidth = ScreenWidth/float (24);
    int bucketHeight = ScreenHeight/float(21.6);
    int startX = GetScreenWidth() / 5 + 50;
    int startY = 150;
    int bucketsPerRow = 15;
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

    // Khởi tạo animation xóa dựa trên stepDeleteIndex
    if (currentStep == 3 && stepDeleteIndex != -1 && stepDeleteIndex < capacity && !isRemoveAnimating) {
        isRemoveAnimating = true;
        isJumping = true;
        removeIndex = stepDeleteIndex;
        removedValue = table[stepDeleteIndex];
        removeProgress = 0.0f;

        // Tính tọa độ bucket tại stepDeleteIndex
        int row = stepDeleteIndex / bucketsPerRow;
        int col = stepDeleteIndex % bucketsPerRow;
        int targetX = startX + col * (bucketWidth + spacingX);
        int targetY = startY + row * (bucketHeight + spacingY);
        int bucketX = centerX + (targetX - centerX) * easedProgress;
        int bucketY = centerY + (targetY - centerY) * easedProgress;

        // Căn chỉnh giống hệt cách vẽ giá trị trong bucket
        removeX = bucketX + 30; // Khớp với x + 30 khi vẽ giá trị
        removeY = bucketY + 15; // Khớp với y + 15 khi vẽ giá trị
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

            Color bucketColor = C[1];
            if (isCollisionAnimation && std::find(collisionIndices.begin(), collisionIndices.end(), i) != collisionIndices.end()) {
                bucketColor = (fmod(collisionProgress, 0.5f) < 0.25f) ? C[0] : C[1];
            }
            else if (i == highlightedIndex) {
                bucketColor = C[5]; // Tô hồng cho bucket đang kiểm tra
            }
            // Chỉ nháy đỏ khi ở bước 2 (dòng "If slot is occupied, probe next")
            else if (currentStep == 2 && std::find(stepCollisionIndices.begin(), stepCollisionIndices.end(), i) != stepCollisionIndices.end()) {
                bucketColor = (fmod(GetTime(), 0.5f) < 0.25f) ? C[0] : C[1]; // Nháy đỏ cho va chạm
            }
            // Chỉ tô xanh khi đang ở bước 3 và giá trị đã được chèn
            else if (i == stepInsertIndex && table[i] != EMPTY && table[i] != DELETED) {
                bucketColor = GREEN;
            }

            DrawRectangle(x, y, bucketWidth, bucketHeight, bucketColor);
            DrawRectangleLines(x, y, bucketWidth, bucketHeight, BLACK);

            if (progress >= 1.0f && table[i] != EMPTY && table[i] != DELETED) {
                std::string value = std::to_string(table[i]);
                DrawText(value.c_str(), x + 30, y + 15, 20, C[0]);
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
        DrawText(std::to_string(removedValue).c_str(), removeX, removeY, 20, C[0]);
    }
}

void HashTable::handleRandom() {
    int newCapacity = GetRandomValue(30, 100);
    init(newCapacity);
    int randomCount = GetRandomValue(newCapacity * 0.5, newCapacity * 0.8);
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

void HashTable::startInsertStep(int key) {
    pendingKey = key;
    stepCollisionIndices.clear();
    stepCurrentIndex = hashFunction(key);
    stepInsertIndex = -1;
    stepCollisionDetected = false;
    highlightedIndex = -1;

    // Kiểm tra bucket ban đầu
    if (table[stepCurrentIndex] != EMPTY && table[stepCurrentIndex] != DELETED) {
        stepCollisionDetected = true;
        stepCollisionIndices.push_back(stepCurrentIndex);
    }
}

void HashTable::performInsertStep(int step) {
    if (step == 1) {
        // Bước 1: Tô sáng bucket ban đầu
        highlightedIndex = stepCurrentIndex;
    }
    else if (step == 2) {
        if (stepCollisionDetected) {
            // Bước 2: Dò tuyến tính
            int originalIndex = hashFunction(pendingKey);
            stepCurrentIndex = (stepCurrentIndex + 1) % capacity;
            if (stepCurrentIndex == originalIndex) {
                // Bảng đầy, không thể chèn
                stepInsertIndex = -1;
                highlightedIndex = -1;
                return;
            }
            if (table[stepCurrentIndex] != EMPTY && table[stepCurrentIndex] != DELETED) {
                stepCollisionIndices.push_back(stepCurrentIndex);
                stepCollisionDetected = true;
            }
            else {
                stepInsertIndex = stepCurrentIndex; // Tìm thấy vị trí chèn
                stepCollisionDetected = false;
            }
            highlightedIndex = stepCurrentIndex;
        }
        else {
            // Không có va chạm, đặt vị trí chèn
            stepInsertIndex = stepCurrentIndex;
        }
    }
    else if (step == 3 && stepInsertIndex != -1) {
        // Bước 3: Chèn giá trị
        table[stepInsertIndex] = pendingKey;
        size++;
        highlightedIndex = -1; // Không tô sáng nữa
    }
}

void HashTable::revertInsertStep(int step) {
    if (step == 0) {
        // Quay lại bước đầu: reset trạng thái
        stepCurrentIndex = hashFunction(pendingKey);
        stepCollisionIndices.clear();
        stepInsertIndex = -1;
        stepCollisionDetected = (table[stepCurrentIndex] != EMPTY && table[stepCurrentIndex] != DELETED);
        if (stepCollisionDetected) {
            stepCollisionIndices.push_back(stepCurrentIndex);
        }
        highlightedIndex = -1;
        if (stepInsertIndex != -1 && table[stepInsertIndex] == pendingKey) {
            table[stepInsertIndex] = EMPTY; // Xóa giá trị đã chèn
            size--;
        }
    }
    else if (step == 1) {
        // Quay lại bước 1: hiển thị bucket ban đầu
        highlightedIndex = stepCurrentIndex;
        if (stepInsertIndex != -1 && table[stepInsertIndex] == pendingKey) {
            table[stepInsertIndex] = EMPTY; // Xóa giá trị đã chèn
            size--;
        }
        stepInsertIndex = -1;
    }
    else if (step == 2) {
        // Quay lại bước 2: hoàn tác dò tuyến tính
        if (stepInsertIndex != -1 && table[stepInsertIndex] == pendingKey) {
            table[stepInsertIndex] = EMPTY; // Xóa giá trị đã chèn
            size--;
        }
        if (stepInsertIndex != -1 && stepInsertIndex == stepCurrentIndex) {
            stepInsertIndex = -1; // Bỏ vị trí chèn
        }
        else if (!stepCollisionIndices.empty()) {
            stepCurrentIndex = stepCollisionIndices.back();
            stepCollisionIndices.pop_back();
            stepCollisionDetected = true;
        }
        else {
            stepCurrentIndex = hashFunction(pendingKey);
            stepCollisionDetected = (table[stepCurrentIndex] != EMPTY && table[stepCurrentIndex] != DELETED);
            if (stepCollisionDetected) {
                stepCollisionIndices.push_back(stepCurrentIndex);
            }
        }
        highlightedIndex = stepCurrentIndex;
        stepInsertIndex = -1;
    }
}

void HashTable::resetStepState() {
    stepInsertIndex = -1;
    stepSearchIndex = -1;
    stepDeleteIndex = -1;
    highlightedIndex = -1;
    stepCollisionIndices.clear();
    stepCollisionDetected = false;
    stepCurrentIndex = -1;
}

void HashTable::startSearchStep(int key) {
    pendingKey = key;
    stepCollisionIndices.clear();
    stepCurrentIndex = hashFunction(key);
    stepSearchIndex = -1;
    stepCollisionDetected = false;
    highlightedIndex = -1;

    // Kiểm tra bucket ban đầu
    if (table[stepCurrentIndex] != EMPTY && table[stepCurrentIndex] != DELETED && table[stepCurrentIndex] != key) {
        stepCollisionDetected = true;
        stepCollisionIndices.push_back(stepCurrentIndex);
    }
    else if (table[stepCurrentIndex] == key) {
        stepSearchIndex = stepCurrentIndex;
    }
}

void HashTable::performSearchStep(int step) {
    if (step == 1) {
        // Bước 1: Tô sáng bucket ban đầu
        highlightedIndex = stepCurrentIndex;
    }
    else if (step == 2) {
        if (stepCollisionDetected && stepSearchIndex == -1) {
            // Bước 2: Dò tuyến tính
            int originalIndex = hashFunction(pendingKey);
            stepCurrentIndex = (stepCurrentIndex + 1) % capacity;
            if (stepCurrentIndex == originalIndex) {
                // Không tìm thấy
                stepSearchIndex = -1;
                highlightedIndex = -1;
                return;
            }
            if (table[stepCurrentIndex] != EMPTY && table[stepCurrentIndex] != DELETED) {
                if (table[stepCurrentIndex] == pendingKey) {
                    stepSearchIndex = stepCurrentIndex; // Tìm thấy giá trị
                    stepCollisionDetected = false;
                }
                else {
                    stepCollisionIndices.push_back(stepCurrentIndex);
                    stepCollisionDetected = true;
                }
            }
            else {
                stepSearchIndex = -1; // Không tìm thấy
                stepCollisionDetected = false;
            }
            highlightedIndex = stepCurrentIndex;
        }
    }
    else if (step == 3 && stepSearchIndex != -1) {
        // Bước 3: Tô sáng vị trí tìm thấy
        highlightedIndex = stepSearchIndex;
    }
}

void HashTable::revertSearchStep(int step) {
    if (step == 0) {
        // Quay lại bước đầu: reset trạng thái
        stepCurrentIndex = hashFunction(pendingKey);
        stepCollisionIndices.clear();
        stepSearchIndex = -1;
        stepCollisionDetected = (table[stepCurrentIndex] != EMPTY && table[stepCurrentIndex] != DELETED && table[stepCurrentIndex] != pendingKey);
        if (stepCollisionDetected) {
            stepCollisionIndices.push_back(stepCurrentIndex);
        }
        highlightedIndex = -1;
    }
    else if (step == 1) {
        // Quay lại bước 1: hiển thị bucket ban đầu
        highlightedIndex = stepCurrentIndex;
        stepSearchIndex = -1;
    }
    else if (step == 2) {
        // Quay lại bước 2: hoàn tác dò tuyến tính
        if (stepSearchIndex != -1) {
            stepSearchIndex = -1; // Bỏ vị trí tìm thấy
        }
        if (!stepCollisionIndices.empty()) {
            stepCurrentIndex = stepCollisionIndices.back();
            stepCollisionIndices.pop_back();
            stepCollisionDetected = true;
        }
        else {
            stepCurrentIndex = hashFunction(pendingKey);
            stepCollisionDetected = (table[stepCurrentIndex] != EMPTY && table[stepCurrentIndex] != DELETED && table[stepCurrentIndex] != pendingKey);
            if (stepCollisionDetected) {
                stepCollisionIndices.push_back(stepCurrentIndex);
            }
        }
        highlightedIndex = stepCurrentIndex;
    }
}

void HashTable::startDeleteStep(int key) {
    pendingKey = key;
    stepCollisionIndices.clear();
    stepCurrentIndex = hashFunction(key);
    stepDeleteIndex = -1;
    stepCollisionDetected = false;
    highlightedIndex = -1;

    // Kiểm tra bucket ban đầu
    if (table[stepCurrentIndex] != EMPTY && table[stepCurrentIndex] != DELETED && table[stepCurrentIndex] != key) {
        stepCollisionDetected = true;
        stepCollisionIndices.push_back(stepCurrentIndex);
    }
    else if (table[stepCurrentIndex] == key) {
        stepDeleteIndex = stepCurrentIndex;
    }
}

void HashTable::performDeleteStep(int step) {
    if (step == 1) {
        // Bước 1: Không tô sáng bucket (để đồng bộ với Search)
        highlightedIndex = -1;
    }
    else if (step == 2) {
        if (stepCollisionDetected && stepDeleteIndex == -1) {
            // Bước 2: Dò tuyến tính
            int originalIndex = hashFunction(pendingKey);
            stepCurrentIndex = (stepCurrentIndex + 1) % capacity;
            if (stepCurrentIndex == originalIndex) {
                // Không tìm thấy
                stepDeleteIndex = -1;
                highlightedIndex = -1;
                return;
            }
            if (table[stepCurrentIndex] != EMPTY && table[stepCurrentIndex] != DELETED) {
                if (table[stepCurrentIndex] == pendingKey) {
                    stepDeleteIndex = stepCurrentIndex; // Tìm thấy giá trị
                    stepCollisionDetected = false;
                }
                else {
                    stepCollisionIndices.push_back(stepCurrentIndex);
                    stepCollisionDetected = true;
                }
            }
            else {
                stepDeleteIndex = -1; // Không tìm thấy
                stepCollisionDetected = false;
            }
            highlightedIndex = stepCurrentIndex; // Tô hồng bucket ở bước 2
        }
    }
    else if (step == 3) {
        if (stepDeleteIndex != -1) {
            // Bước 3: Xóa giá trị và kích hoạt animation
            removedValue = table[stepDeleteIndex];
            table[stepDeleteIndex] = DELETED;
            size--;
            // Khởi tạo animation
            removeX = 300 + (stepDeleteIndex % 10) * (80 + 10) + 30;
            removeY = 150 + (stepDeleteIndex / 10) * (50 + 30) + 15;
            removeIndex = stepDeleteIndex;
            removeProgress = 0.0f;
            isRemoveAnimating = true;
            isJumping = true;
            highlightedIndex = stepDeleteIndex; // Tô sáng bucket trước khi animation
        }
        else {
            // Không tìm thấy giá trị
            highlightedIndex = -1;
        }
    }
}

void HashTable::revertDeleteStep(int step) {
    if (step == 0) {
        // Quay lại bước đầu: reset trạng thái
        stepCurrentIndex = hashFunction(pendingKey);
        stepCollisionIndices.clear();
        stepDeleteIndex = -1;
        stepCollisionDetected = (table[stepCurrentIndex] != EMPTY && table[stepCurrentIndex] != DELETED && table[stepCurrentIndex] != pendingKey);
        if (stepCollisionDetected) {
            stepCollisionIndices.push_back(stepCurrentIndex);
        }
        highlightedIndex = -1;
        if (stepDeleteIndex != -1 && table[stepDeleteIndex] == DELETED) {
            table[stepDeleteIndex] = pendingKey; // Khôi phục giá trị đã xóa
            size++;
        }
    }
    else if (step == 1) {
        // Quay lại bước 1: hiển thị bucket ban đầu
        highlightedIndex = stepCurrentIndex;
        if (stepDeleteIndex != -1 && table[stepDeleteIndex] == DELETED) {
            table[stepDeleteIndex] = pendingKey; // Khôi phục giá trị đã xóa
            size++;
        }
        stepDeleteIndex = -1;
    }
    else if (step == 2) {
        // Quay lại bước 2: hoàn tác dò tuyến tính
        if (stepDeleteIndex != -1 && table[stepDeleteIndex] == DELETED) {
            table[stepDeleteIndex] = pendingKey; // Khôi phục giá trị đã xóa
            size++;
        }
        if (stepDeleteIndex != -1) {
            stepDeleteIndex = -1; // Bỏ vị trí xóa
        }
        if (!stepCollisionIndices.empty()) {
            stepCurrentIndex = stepCollisionIndices.back();
            stepCollisionIndices.pop_back();
            stepCollisionDetected = true;
        }
        else {
            stepCurrentIndex = hashFunction(pendingKey);
            stepCollisionDetected = (table[stepCurrentIndex] != EMPTY && table[stepCurrentIndex] != DELETED && table[stepCurrentIndex] != pendingKey);
            if (stepCollisionDetected) {
                stepCollisionIndices.push_back(stepCurrentIndex);
            }
        }
        highlightedIndex = stepCurrentIndex;
    }
}

