#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <vector>
#include <fstream>

class LinkedList {
private:
    struct Node {
        int data;
        Vector2 pos{ -100.0f, -100.0f };
        bool is_highlighted = false;
        Node* next;

        Node() : data(-1), pos({ -100.0f, -100.0f }), is_highlighted(false), next(nullptr) {}
        Node(int val, float x = 0, float y = 0, bool is_high = false)
            : data(val), pos({ x, y }), is_highlighted(is_high), next(nullptr) {
        }
    };

    Node* head;
    float node_rad = 35.0f;
    int active_node = -1;

    void draw_node(const Node* node);
    void draw_link(const Node* from, const Node* to);

public:
    LinkedList() : head(nullptr) {}

    void add_node(int data);           // Add node at end
    void add_node_front(int data);     // Add node at beginning
    void delete_node(int data);        // Delete first occurrence
    void update();
    void clear();
    int get_active();

    void rand_list(int n_nodes);       // Generate random list
    void input_list(std::ifstream& fin);
    void print_list();
    void draw();

    ~LinkedList();                    // Destructor to free memory
};

#endif