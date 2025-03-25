#include "HashTable.hpp"
#include "GUI.hpp"
#include "raylib.h"
#include <iostream>
#include <vector>
#include <cmath>


HashTable::HashTable(int cap) : capacity(cap), size(0) {
    table.resize(capacity, EMPTY);
}
void HashTable::insert(int key) {
    int index = hashFunction(key);
    while (table[index] != EMPTY && table[index] != DELETED) {
        index = (index + 1) % capacity; // Linear Probing
    }
    table[index] = key;  // Gán số vào bucket
    drawHashTable();  // Cập nhật giao diện ngay lập tức
}
/*void HashTable::drawHashTable() {
    int bucketWidth = 80;
    int bucketHeight = 50;
    int startX = 250;
    int startY = 300;
    int bucketsPerRow = 10; // Số bucket tối đa trên một hàng
    int spacingX = 10; // Khoảng cách ngang giữa các bucket
    int spacingY = 30; // Khoảng cách dọc giữa các hàng

    for (int i = 0; i < capacity; i++) {
        int row = i / bucketsPerRow; // Xác định hàng
        int col = i % bucketsPerRow; // Xác định cột
        int x = startX + col * (bucketWidth + spacingX);
        int y = startY + row * (bucketHeight + spacingY);

        // Nếu bucket đang được highlight (tìm kiếm), đổi màu thành hồng
        Color bucketColor = (i == highlightIndex) ? PINK : YELLOW;
        DrawRectangle(x, y, bucketWidth, bucketHeight, bucketColor);
        DrawRectangleLines(x, y, bucketWidth, bucketHeight, BLACK);

        // Vẽ số vào ô nếu có giá trị hợp lệ
        if (table[i] != EMPTY && table[i] != DELETED) {
            std::string value = std::to_string(table[i]);
            DrawText(value.c_str(), x + 30, y + 15, 20, RED);
        }

        // Đánh số thứ tự bucket
        std::string index = std::to_string(i);
        DrawText(index.c_str(), x + 35, y - 20, 20, WHITE);
    }
}*/

void HashTable::drawHashTable() {
    int bucketWidth = 80;
    int bucketHeight = 50;
    int startX = 250;
    int startY = 300;
    int bucketsPerRow = 10; // Số bucket tối đa trên một hàng
    int spacingX = 10; // Khoảng cách ngang giữa các bucket
    int spacingY = 30; // Khoảng cách dọc giữa các hàng

    float centerX = GetScreenWidth() / 2;
    float centerY = GetScreenHeight() / 2;

    // Nếu đang Init, reset progress
    if (isInitializing) {
        progress = 0.0f;
        isInitializing = false;
    }

    // Animation chạy bình thường
    if (progress < 1.0f) {
        progress += 0.02f; // Animation tăng dần
    }

    float easedProgress = 1 - pow(1 - progress, 3); // Hiệu ứng chậm -> nhanh

    for (int i = 0; i < capacity; i++) {
        int row = i / bucketsPerRow;
        int col = i % bucketsPerRow;
        int targetX = startX + col * (bucketWidth + spacingX);
        int targetY = startY + row * (bucketHeight + spacingY);

        // Di chuyển từ giữa ra ngoài
        int x = centerX + (targetX - centerX) * easedProgress;
        int y = centerY + (targetY - centerY) * easedProgress;

        DrawRectangle(x, y, bucketWidth, bucketHeight, YELLOW);
        DrawRectangleLines(x, y, bucketWidth, bucketHeight, BLACK);

        // Hiện số sau khi animation hoàn tất
        if (progress >= 1.0f && table[i] != EMPTY && table[i] != DELETED) {
            std::string value = std::to_string(table[i]);
            DrawText(value.c_str(), x + 30, y + 15, 20, RED);
        }

        // Đánh số thứ tự bucket
        std::string index = std::to_string(i);
        DrawText(index.c_str(), x + 35, y - 20, 20, WHITE);
    }
}

bool HashTable::search(int key) {
    int index = hashFunction(key);
    int start = index;

    while (table[index] != EMPTY) {
        if (table[index] == key) {
            highlightedIndex = index;  // Lưu vị trí cần highlight
            drawHashTable();         // Vẽ lại giao diện
            return true;
        }
        index = (index + 1) % capacity;
        if (index == start) break;
    }

    highlightedIndex = -1;  // Không tìm thấy thì bỏ highlight
    drawHashTable();
    return false;
}

void HashTable::remove(int key) {
    int index = hashFunction(key);
    int start = index;
    while (table[index] != EMPTY) {
        if (table[index] == key) {
            table[index] = DELETED;
            size--;
            drawHashTable();  // Cập nhật giao diện sau khi xóa
            return;
        }
        index = (index + 1) % capacity;
        if (index == start) break;
    }
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
