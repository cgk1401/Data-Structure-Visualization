#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <vector>
#include <fstream>



class LinkedList {
private:
    struct Node {
        int data;
        Vector2 pos;
        Vector2 target_pos;
        bool is_highlighted = false;
        float anim_progress = 0.0f;
        Node* next;

        Node() : data(-1), pos({ -100.0f, -100.0f }), target_pos({ -100.0f, -100.0f }),
            is_highlighted(false), anim_progress(0.0f), next(nullptr) {
        }
        Node(int val, float x = 0, float y = 0, bool is_high = false)
            : data(val), pos({ x, y }), target_pos({ x, y }),
            is_highlighted(is_high), anim_progress(1.0f), next(nullptr) {
        }
    };

    Node* head;
    float node_rad = 35.0f;
    int active_node = -1;
    float anim_speed = 5.0f;
    int search_state = -1;    // -1: idle, 0: searching, 1: found, 2: not found
    float search_timer = 0.0f;

    void draw_node(const Node* node);
    void draw_link(const Node* from, const Node* to);
    void update_node_animation(Node* node, float delta_time);

    int nodeCount = 0;

public:
    LinkedList() : head(nullptr) {}

    void add_node(int data);
    void add_node_front(int data);
    void delete_node(int data);
    void update();
    void clear();
    int get_active();

    void rand_list(int n_nodes);
    void input_list(std::ifstream& fin);
    void print_list();
    void draw();

    bool search_node(int data);
    int get_search_state() const { return search_state; } // New: Public getter



    static int currentDisplayMode;
    static float listScrollX;
    static float nodeScale;

    void calculate_layout();

    static int Max(int a, int b) {
        return (a > b) ? a : b;
    }

    ~LinkedList();
};

#endif