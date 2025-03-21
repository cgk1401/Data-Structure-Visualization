#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <vector>
#include <raylib.h>

class LinkedList {
private:
    struct Node {
        int value;
        Vector2 pos{ -100.0f, -100.0f };
        Node* next;

        Node(int val) : value(val), next(nullptr) {
            pos.x = -100.0f;
            pos.y = -100.0f;
        }
    };

    Node* head;
    int size;

    void draw_node(Node* node, int index);

public:
    LinkedList() : head(nullptr), size(0) {}

    void add_node(int value);
    void delete_node(int value);
    void clear();

    void print_list();
    void draw();

    bool search(int value);

    ~LinkedList();
};

#endif