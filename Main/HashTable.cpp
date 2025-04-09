#include "HashTable.hpp"
#include "GUI.hpp"
#include "raylib.h"
#include <iostream>
#include <vector>
#include <cmath>
// Khai báo static ở đầu file
static int buttonCreateX = 0;
static int buttonCreateY = 0;
static int buttonRandomX = 0;
static int buttonRandomY = 0;


HashTable::HashTable(int cap) : capacity(cap), size(0) {
    table.resize(capacity, EMPTY);
}

void HashTable::insert(int key) {
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
        startCollisionAnimation(0);
        pendingKey = key; // Lưu giá trị để chèn sau
        insertTargetIndex = -1; // Chưa xác định vị trí ngay
    }
    else {
        // Không có va chạm, chèn và chạy animation ngay
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
        insertX = GetScreenWidth() / 2;
        insertY = GetScreenHeight() / 2;
        insertTargetIndex = index;
        insertProgress = 0.0f;
        isInsertAnimating = true;
        pendingKey = key;
    }

    drawHashTable();
}

void HashTable::drawHashTable() {
    int bucketWidth = 80;
    int bucketHeight = 50;
    int startX = 250;
    int startY = 300;
    int bucketsPerRow = 10;
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
        insertProgress += 0.02f; // Giảm từ 0.05f xuống 0.02f để chậm hơn (~1 giây)
        float easedInsert = 1 - pow(1 - insertProgress, 3);
        int targetX = startX + (insertTargetIndex % bucketsPerRow) * (bucketWidth + spacingX) + bucketWidth / 2;
        int targetY = startY + (insertTargetIndex / bucketsPerRow) * (bucketHeight + spacingY) + bucketHeight / 2;
        insertX = centerX + (targetX - centerX) * easedInsert;
        insertY = centerY + (targetY - centerY) * easedInsert;
        DrawText(std::to_string(pendingKey).c_str(), insertX - 10, insertY - 10, 20, RED);
        if (insertProgress >= 1.0f) {
            isInsertAnimating = false;
            pendingKey = -1; // Reset sau khi animation hoàn tất
        }
    }

    // Vẽ bucket
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

void HashTable::search(int key) {
    int index = hashFunction(key);
    int start = index;

    while (table[index] != EMPTY) {
        if (table[index] == key) {
            highlightedIndex = index;  // Lưu vị trí cần highlight
            std::cout << "Found at index:  " << highlightedIndex << ':' << index << std::endl;
            drawHashTable();         // Vẽ lại giao diện
            return;
        }
        index = (index + 1) % capacity;
        if (index == start) break;
    }

    highlightedIndex = -1;  // Không tìm thấy thì bỏ highlight
    drawHashTable();
}


void HashTable::remove(int key) {
    int index = hashFunction(key);
    int start = index;

    while (table[index] != EMPTY) {
        if (table[index] == key && !isRemoveAnimating) {
            // Lấy vị trí chính xác của số trong bucket (giữa bucket, đè lên màu vàng)
            removeX = 250 + (index % 10) * (80 + 10) + 30; // Tọa độ x của số trong bucket
            removeY = 300 + (index / 10) * (50 + 30) + 15; // Tọa độ y của số trong bucket
            removeIndex = index;
            removeProgress = 0.0f;
            isRemoveAnimating = true;
            isJumping = true;
            removedValue = table[index]; // Lưu giá trị bị xóa
            table[index] = DELETED;      // Xóa ngay số trong bucket
            size--;
            std::cout << "✅ Starting remove animation for " << removedValue << " at index " << index << "\n";
            drawHashTable();
            return;
        }
        index = (index + 1) % capacity;
        if (index == start) break;
    }
    drawHashTable();
}


void HashTable::rehash() {
    int oldCapacity = capacity;
    capacity *= 2;
    std::vector<int> oldTable = table;
    table.assign(capacity, EMPTY);
    size = 0;
    for (int key : oldTable) {
        if (key != EMPTY && key != DELETED) {
            insert(key);
        }
    }
}


void HashTable::display() {
    for (int i = 0; i < capacity; i++) {
        if (table[i] == EMPTY) std::cout << "[ ] ";
        else if (table[i] == DELETED) std::cout << "[X] ";
        else std::cout << "[" << table[i] << "] ";
    }
    std::cout << std::endl;
}


HashTable& HashTable::operator=(const HashTable& other) {
    if (this == &other) return *this; // Tránh tự gán

    capacity = other.capacity;
    size = other.size;
    table = other.table; // Gán lại vector

    return *this;
}


void HashTable::init(int newCapacity) {
    capacity = newCapacity;
    table.assign(capacity, EMPTY);
    isInitializing = true; // Kích hoạt animation
    progress = 0.0f; // Reset tiến trình animation
}



void HashTable::startInitAnimation() {
    isAnimatingInit = true;
    progressInit = 0.0f; // Reset lại animation
}


bool HashTable::isInitAnimationRunning() const {
    return isAnimatingInit;
}

void HashTable::drawInitAnimation(int startX, int startY) {
    if (!isAnimatingInit) {
        // Nếu animation đã kết thúc, giữ nút hiển thị và xử lý click
        if (isButtonsVisible) {
            DrawRectangle(createButtonX, createButtonY, 100, 27, SKYBLUE);
            DrawRectangle(randomButtonX, randomButtonY, 100, 27, BEIGE);
            DrawText("Create", createButtonX + 15, createButtonY + 6, 20, WHITE);
            DrawText("Random", randomButtonX + 15, randomButtonY + 7, 20, WHITE);

            // Kiểm tra click chuột khi nút đã hiển thị
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mouse = GetMousePosition();
                if (mouse.x >= createButtonX && mouse.x <= createButtonX + 100 &&
                    mouse.y >= createButtonY && mouse.y <= createButtonY + 27) {
                    Gui.isClickCreate = true;
                    Gui.isClickRandom = false;
                    std::cout << "✅ Clicked Create button!\n";
                }
                if (mouse.x >= randomButtonX && mouse.x <= randomButtonX + 100 &&
                    mouse.y >= randomButtonY && mouse.y <= randomButtonY + 27) {
                    Gui.isClickRandom = true;
                    Gui.isClickCreate = false;
                    std::cout << "✅ Clicked Random button!\n";
                }
            }
        }
        return;
    }

    // Animation chỉ chạy một lần khi khởi động
    if (progressInit < 1.0f) {
        progressInit += 0.02f;
    }
    else {
        progressInit = 1.0f;
    }

    float easedProgress = 1 - pow(1 - progressInit, 3);
    if (Gui.isClickInit) {
        Gui.isClickCreate = false;
        Gui.isClickRandom = false;
        std::cout << "✅ Init button clicked, starting animation\n";
    }

    int buttonWidth = 100, buttonHeight = 27;
    int gap = 12;

    int targetX1 = startX + buttonWidth + gap;
    int targetY1 = startY;
    int targetX2 = targetX1;
    int targetY2 = targetY1 + buttonHeight + gap;

    int x1 = startX + (targetX1 - startX) * easedProgress;
    int y1 = startY + (targetY1 - startY) * easedProgress;
    int x2 = startX + (targetX2 - startX) * easedProgress;
    int y2 = startY + (targetY2 - startY) * easedProgress;

    DrawRectangle(x1, y1, buttonWidth, buttonHeight, SKYBLUE);
    DrawRectangle(x2, y2, buttonWidth, buttonHeight, BEIGE);
    DrawText("Create", x1 + 15, y1 + 6, 20, WHITE);
    DrawText("Random", x2 + 15, y2 + 7, 20, WHITE);

    // Khi animation hoàn tất, giữ nút hiển thị
    if (progressInit >= 1.0f) {
        isAnimatingInit = false;
        isButtonsVisible = true;
        setButtonPositions(targetX1, targetY1, targetX2, targetY2);
        std::cout << "✅ Animation finished, buttons remain visible\n";
    }

    // Kiểm tra click chuột trong lúc animation
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        if (mouse.x >= x1 && mouse.x <= x1 + buttonWidth &&
            mouse.y >= y1 && mouse.y <= y1 + buttonHeight) {
            Gui.isClickCreate = true;
            Gui.isClickRandom = false;
            std::cout << "✅ Clicked Create button during animation!\n";
        }
        if (mouse.x >= x2 && mouse.x <= x2 + buttonWidth &&
            mouse.y >= y2 && mouse.y <= y2 + buttonHeight) {
            Gui.isClickRandom = true;
            Gui.isClickCreate = false;
            std::cout << "✅ Clicked Random button during animation!\n";
        }
    }
}

void HashTable::handleRandomButton() {
    int randomCapacity = GetRandomValue(10, 50);
    init(randomCapacity);
    int randomCount = GetRandomValue(5, 20);
    std::cout << "✅ Randomizing " << randomCount << " values into table of size " << randomCapacity << "\n";

    for (int i = 0; i < randomCount; i++) {
        if (size >= capacity) {
            std::cout << "❌ Table is full after " << i << " insertions\n";
            break; // Dừng nếu bảng đầy
        }
        int value = GetRandomValue(1, 100);
        insert(value);
        // Không cần gọi drawHashTable() ở đây vì insert đã gọi
    }
    std::cout << "✅ Random insertion completed with " << size << " values\n";
}

void HashTable::startCollisionAnimation(int index) {
    isCollisionAnimation = true;
    collisionProgress = 0.0f;
    collisionIndex = index;
    collisionBlinkCount = 0;
}