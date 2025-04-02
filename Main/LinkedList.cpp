#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include "raylib.h"
#include "LinkedList.hpp"
#include "Config.hpp"

// Node display constants
#define NODE_WIDTH 80.0f
#define NODE_HEIGHT 60.0f
#define NODE_RADIUS 30.0f
#define NODE_SPACING 40.0f
#define ANIM_SPEED 5.0f

// Static member initialization
float LinkedList::nodeScale = 1.0f;

void LinkedList::calculate_layout() {
    // Calculate node count
    nodeCount = 0;
    Node* temp = head;
    while (temp) { nodeCount++; temp = temp->next; }

    // Calculate required and available space
    float requiredWidth = nodeCount * (NODE_WIDTH + NODE_SPACING);
    float availableWidth = ScreenWidth * 0.9f; // 90% of screen width

    // Automatic scaling if needed
    if (requiredWidth > availableWidth) {
        nodeScale = availableWidth / requiredWidth;
    }
    else {
        nodeScale = 1.0f; // Default scale if fits
    }

    // Calculate positions with scaling
    int index = 0;
    temp = head;
    float startX = (ScreenWidth - (nodeCount * (NODE_WIDTH + NODE_SPACING) * nodeScale)) / 2;

    while (temp) {
        float target_x = startX + (NODE_WIDTH + NODE_SPACING) * index * nodeScale;
        float target_y = ScreenHeight / 2;

        temp->target_pos = { target_x, target_y };
        if (temp->pos.x < 0) temp->pos = { target_x - 100.0f, target_y };
        temp->anim_progress = 0.0f;
        temp = temp->next;
        index++;
    }
}

void LinkedList::add_node(int data) {
    Node* new_node = new Node(data);
    if (!head) {
        head = new_node;
    }
    else {
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
    nodeCount++;
    calculate_layout();
}

void LinkedList::add_node_front(int data) {
    Node* new_node = new Node(data);
    new_node->next = head;
    head = new_node;
    nodeCount++;
    calculate_layout();
}

void LinkedList::delete_node(int data) {
    if (!head) return;

    if (head->data == data) {
        Node* temp = head;
        head = head->next;
        if (active_node == data) active_node = -1;
        delete temp;
        nodeCount--;
    }
    else {
        Node* current = head;
        while (current->next && current->next->data != data) {
            current = current->next;
        }
        if (current->next) {
            Node* temp = current->next;
            current->next = temp->next;
            if (active_node == data) active_node = -1;
            delete temp;
            nodeCount--;
        }
    }
    calculate_layout();
}

void LinkedList::update_node_animation(Node* node, float delta_time) {
    if (node->anim_progress < 1.0f) {
        node->anim_progress += ANIM_SPEED * delta_time;
        if (node->anim_progress > 1.0f) node->anim_progress = 1.0f;
        float t = node->anim_progress * node->anim_progress; // Quadratic easing
        node->pos.x = node->pos.x + (node->target_pos.x - node->pos.x) * t;
        node->pos.y = node->pos.y + (node->target_pos.y - node->pos.y) * t;
    }
}

void LinkedList::update() {
    float delta_time = GetFrameTime();
    Node* temp = head;
    while (temp) {
        update_node_animation(temp, delta_time);
        temp = temp->next;
    }

    // Animated search logic
    if (search_state == 0) {
        search_timer -= delta_time;
        if (search_timer <= 0.0f) {
            search_timer = 0.5f; // Delay per node
            Node* current = head;
            while (current) {
                if (!current->is_highlighted) {
                    current->is_highlighted = true;
                    if (current->data == active_node) {
                        search_state = 1; // Found
                    }
                    break;
                }
                if (!current->next) {
                    search_state = 2; // Not found
                }
                current = current->next;
            }
        }
    }

    static Node* cur_node = nullptr;
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !cur_node) {
        Node* current = head;
        while (current) {
            if (CheckCollisionPointCircle(mouse, current->pos, NODE_RADIUS)) {
                cur_node = current;
                break;
            }
            current = current->next;
        }
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        bool miss = true;
        Node* current = head;
        while (current) {
            if (CheckCollisionPointCircle(mouse, current->pos, NODE_RADIUS)) {
                if (active_node != current->data) {
                    if (active_node != -1 && search_state == -1) {
                        Node* temp = head;
                        while (temp && temp->data != active_node) temp = temp->next;
                        if (temp) temp->is_highlighted = false;
                    }
                    active_node = current->data;
                    if (search_state == -1) current->is_highlighted = true;
                }
                else {
                    active_node = -1;
                    if (search_state == -1) current->is_highlighted = false;
                }
                miss = false;
                break;
            }
            current = current->next;
        }
        if (miss && active_node != -1 && search_state == -1) {
            Node* temp = head;
            while (temp && temp->data != active_node) temp = temp->next;
            if (temp) temp->is_highlighted = false;
            active_node = -1;
        }
    }

    if (cur_node) {
        cur_node->pos = mouse;
        cur_node->target_pos = mouse;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) cur_node = nullptr;
    }
}

void LinkedList::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    nodeCount = 0;
    active_node = -1;
    search_state = -1;
}

int LinkedList::get_active() {
    return active_node;
}

void LinkedList::rand_list(int n_nodes) {
    clear();
    srand(time(0));
    for (int i = 0; i < n_nodes; i++) {
        add_node(rand() % 100 + 1);
    }
}

void LinkedList::input_list(std::ifstream& fin) {
    clear();
    int n_nodes;
    fin >> n_nodes;
    for (int i = 0; i < n_nodes; i++) {
        int data;
        fin >> data;
        add_node(data);
    }
}

void LinkedList::print_list() {
    Node* current = head;
    while (current) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

void LinkedList::draw_node(const Node* node) {
    std::string dataText = std::to_string(node->data);
    int fontSize = (int)(20 * nodeScale); // Scale font size too
    int width = MeasureText(dataText.c_str(), fontSize);

    float pulse = node->is_highlighted ? (sinf(GetTime() * 4.0f) * 0.2f + 1.0f) : 1.0f;
    float radius = NODE_RADIUS * pulse * nodeScale;

    // Draw node
    Color nodeColor = node->is_highlighted ? C[5] : C[1];
    DrawCircleV(node->pos, radius, nodeColor);
    DrawCircleLinesV(node->pos, radius, C[3]);

    // Draw text centered
    DrawText(dataText.c_str(),
        node->pos.x - width / 2,
        node->pos.y - fontSize / 2,
        fontSize, C[0]);
}

void LinkedList::draw_link(const Node* from, const Node* to) {
    DrawLineEx(from->pos, to->pos, 3.0f * nodeScale, C[3]);
}

void LinkedList::draw() {
    // Draw all nodes centered on screen
    Node* current = head;
    while (current) {
        draw_node(current);
        if (current->next) {
            draw_link(current, current->next);
        }
        current = current->next;
    }
}

bool LinkedList::search_node(int data) {
    Node* current = head;
    while (current) {
        current->is_highlighted = false;
        current = current->next;
    }
    active_node = data;
    search_state = 0;
    search_timer = 0.5f;
    return true;
}

LinkedList::~LinkedList() {
    clear();
}