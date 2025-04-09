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
    bool isAnimatingInit = false; // Biến kiểm soát trạng thái animation
    float progressInit = 0.0f;    // Tiến trình của animation
    bool isButtonsVisible = false; // Biến kiểm soát việc hiển thị nút Create và Random
    int createButtonX = 0, createButtonY = 0; // Vị trí cuối cùng của nút Create
    int randomButtonX = 0, randomButtonY = 0; // Vị trí cuối cùng của nút Random
    bool isCollisionAnimation = false; // Trạng thái animation va chạm
    float collisionProgress = 0.0f;    // Tiến trình animation
    int collisionIndex = -1;           // Chỉ số bucket đang nháy đỏ
    int collisionBlinkCount = 0;       // Số lần nháy 
    int pendingKey = -1;  //Lưu giá trị chờ chèn
    bool hasPendingInsert = false; // Cờ báo có giá trị đang chờ
    std::vector<int> collisionIndices; // Danh sách các bucket cần nháy
    float insertX = -1, insertY = -1; // Vị trí hiện tại của số đang bay
    int insertTargetIndex = -1;       // Bucket đích
    float insertProgress = 0.0f;      // Tiến trình bay
    bool isInsertAnimating = false;   // Trạng thái animation
    float removeX = -1, removeY = -1; // Vị trí hiện tại của số
    int removeIndex = -1;             // Bucket bị xóa
    float removeProgress = 0.0f;      // Tiến trình tổng (nhảy + rơi)
    bool isRemoveAnimating = false;   // Trạng thái animation
    bool isJumping = false;           // Giai đoạn nhảy lên
    int removedValue = -1;
public:
    HashTable(int cap = 10);
    void insert(int key);
    void search(int key);
    void remove(int key);
    void display(); 
    void drawHashTable();
    HashTable& operator=(const HashTable& other);
    void init(int newCapacity);
    void drawInitAnimation(int startX, int startY);
    void startInitAnimation(); // Bật animation
    bool isInitAnimationRunning() const; // Kiểm tra animation có đang chạy
    void handleRandomButton();
    void setButtonsVisible(bool visible) { isButtonsVisible = visible; }
    bool areButtonsVisible() const { return isButtonsVisible; }
    void setButtonPositions(int cX, int cY, int rX, int rY) {
        createButtonX = cX; createButtonY = cY;
        randomButtonX = rX; randomButtonY = rY;
    }
    void startCollisionAnimation(int index);
    bool isCollisionAnimating() const { return isCollisionAnimation; }
};

#endif
    