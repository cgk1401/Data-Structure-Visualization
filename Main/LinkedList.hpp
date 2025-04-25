#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "raylib.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class LinkedList {
private:
    struct Node {
        int data;
        Vector2 pos;
        Vector2 target_pos;
        bool is_highlighted;
        float anim_progress;
        float scale;
        Color color;
        bool searched;
        Node* next;

        Node() :
            data(-1),
            pos({ -100.0f, -100.0f }),
            target_pos({ -100.0f, -100.0f }),
            is_highlighted(false),
            anim_progress(0.0f),
            scale(1.0f),
            color(WHITE),
            searched(false),
            next(nullptr) {
        }

        Node(int val, float x = 0, float y = 0, bool is_high = false) :
            data(val),
            pos({ x, y }),
            target_pos({ x, y }),
            is_highlighted(is_high),
            anim_progress(1.0f),
            scale(1.0f),
            color(WHITE),
            searched(false),
            next(nullptr) {
        }
    };

    // Instance members
    Node* head;
    float node_rad;
    int active_node;
    float anim_speed;
    int nodeCount;

    // Search state
    int search_state;
    float search_timer;

    // Delete animation state
    enum class DeleteState { IDLE, SEARCHING, FOUND, DELETING };
    DeleteState deleteState;
    float deleteTimer;
    Node* nodeToDelete;
    Node* prevNode;

    // Private methods
    void draw_node(const Node* node) const;
    void draw_link(const Node* from, const Node* to) const;
    void update_node_animation(Node* node, float delta_time);
    void update_delete_animation(float deltaTime);

    float drawOffset = 0;
    float scrollOffset = 0.0f;
    float contentHeight = 0.0f;

public:
    // Construction/destruction
    LinkedList();
    ~LinkedList();

    // Basic operations
    void add_node(int data);
    void add_node_front(int data);
    void delete_node(int data);
    void clear();
    void rand_list(int n_nodes);
    void print_list() const;
    bool load_from_file(const string& filename);

    // Visualization
    void update();
    void draw() const;

    // Search operations
    bool search_node(int data);
    void start_delete_animation(int value);

    // Getters
    int get_active() const;
    int get_search_state() const;
    static int Max(int a, int b);

    // Layout
    void calculate_layout();

    // Static members
    static int currentDisplayMode;
    static float listScrollX;
    static float nodeScale;

    void setDrawOffset(float offset) { drawOffset = offset; }
    void setScrollOffset(float offset) { scrollOffset = offset; }
    float getContentHeight() const { return contentHeight; }
};

#endif