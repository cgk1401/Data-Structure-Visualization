#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "raylib.h"
#include <vector>
#include <iostream>
#include <string>
#include "DescriptionBox.hpp"

using namespace std;

class LinkedList {
public:
    enum class AnimationType { NONE, INSERT, DELETE, SEARCH };

    LinkedList();
    ~LinkedList();

    void add_node(int data);
    void add_node_front(int data);
    void delete_node(int data);
    void clear();
    void rand_list(int n_nodes);

    void print_list() const;
    bool load_from_file(const string& filename);

    void update();
    void draw() const;

    bool search_node(int data);
    void start_animation(AnimationType type, int value);

    int get_active() const;
    int get_search_state() const;
    static int Max(int a, int b);

    void calculate_layout();

    static int currentDisplayMode;
    static float listScrollX;
    static float nodeScale;

    void setDrawOffset(float offset) { drawOffset = offset; }
    void setScrollOffset(float offset) { scrollOffset = offset; }
    float getContentHeight() const { return contentHeight; }

    void set_paused(bool paused);
    void step_forward();
    void step_backward();
    bool get_paused() const { return isPaused; }

private:
    struct Node {
        int data;
        Vector2 pos;
        Vector2 target_pos;
        bool is_highlighted;
        bool searched;
        Node* next;

        Node() :
            data(-1),
            pos({ -100.0f, -100.0f }),
            target_pos({ -100.0f, -100.0f }),
            is_highlighted(false),
            searched(false),
            next(nullptr) {
        }

        Node(int val, float x = 0, float y = 0, bool is_high = false) :
            data(val),
            pos({ x, y }),
            target_pos({ x, y }),
            is_highlighted(is_high),
            searched(false),
            next(nullptr) {
        }
    };

    Node* head;
    float node_rad;
    int active_node;
    int nodeCount;
    int search_state;

    enum class DeleteState { IDLE, SEARCHING, FOUND, DELETING };
    DeleteState deleteState;
    Node* nodeToDelete;
    Node* prevNode;

    AnimationType currentAnimation;
    int animationStep;
    bool isPaused;
    DescriptionBox descriptionBox;

    void draw_node(const Node* node) const;
    void draw_link(const Node* from, const Node* to) const;
    void animate_insert(int val);
    void animate_delete(int val);
    void animate_search(int val);

    float drawOffset = 0;
    float scrollOffset = 0.0f;
    float contentHeight = 0.0f;

    float animationDuration;
    float currentAnimationTime;

    Node* lastInsertedNode = nullptr;
    Node* lastInsertedPrevNode = nullptr;
    bool lastInsertWasFront = false;
    Node* lastDeletedNode = nullptr;
    Node* lastDeletedPrevNode = nullptr;

    std::vector<Node*> searchPath;
    size_t currentSearchIndex = 0;
};

#endif