#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "raylib.h"
#include "LinkedList.hpp"
#include "Config.hpp"

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

    int count = 0;
    Node* temp = head;
    while (temp) {
        float target_x = ScreenWidth / 4 + (ScreenWidth * 7.0f / 40) * count;
        float target_y = ScreenHeight / 2;
        temp->target_pos = { target_x, target_y };
        if (temp->pos.x < 0) temp->pos = { target_x - 100.0f, target_y };
        temp->anim_progress = 0.0f;
        temp = temp->next;
        count++;
    }
}

void LinkedList::add_node_front(int data) {
    Node* new_node = new Node(data);
    new_node->next = head;
    head = new_node;

    int count = 0;
    Node* temp = head;
    while (temp) {
        float target_x = ScreenWidth / 4 + (ScreenWidth * 7.0f / 40) * count;
        float target_y = ScreenHeight / 2;
        temp->target_pos = { target_x, target_y };
        if (count == 0) temp->pos = { target_x - 100.0f, target_y };
        temp->anim_progress = 0.0f;
        temp = temp->next;
        count++;
    }
}

void LinkedList::delete_node(int data) {
    if (!head) return;

    if (head->data == data) {
        Node* temp = head;
        head = head->next;
        if (active_node == data) active_node = -1;
        delete temp;
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
        }
    }

    int count = 0;
    Node* temp = head;
    while (temp) {
        temp->target_pos = { ScreenWidth / 4 + (ScreenWidth * 7.0f / 40) * count, ScreenHeight / 2 };
        temp->anim_progress = 0.0f;
        temp = temp->next;
        count++;
    }
}

void LinkedList::update_node_animation(Node* node, float delta_time) {
    if (node->anim_progress < 1.0f) {
        node->anim_progress += anim_speed * delta_time;
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
            if (CheckCollisionPointCircle(mouse, current->pos, node_rad)) {
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
            if (CheckCollisionPointCircle(mouse, current->pos, node_rad)) {
                if (active_node != current->data) {
                    if (active_node != -1 && search_state == -1) { // Only reset if not searching
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
    int width = MeasureText(std::to_string(node->data).c_str(), 20);
    int centerX = node->pos.x;
    int centerY = node->pos.y;

    float pulse = node->is_highlighted ? (sin(GetTime() * 4.0f) * 0.2f + 1.0f) : 1.0f;
    float radius = node_rad * pulse;

    if (!node->is_highlighted) {
        DrawCircleV(node->pos, radius, C[1]);
    }
    else {
        DrawCircleV(node->pos, radius, C[5]);
    }
    DrawCircleLinesV(node->pos, radius, C[3]);
    DrawText(std::to_string(node->data).c_str(), centerX - node_rad / 8, centerY - node_rad / 5, 20, C[0]);
}

void LinkedList::draw_link(const Node* from, const Node* to) {
    DrawLineEx(from->pos, to->pos, 3.0f, C[3]);
}

void LinkedList::draw() {
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
        current->is_highlighted = false; // Reset all highlights
        current = current->next;
    }
    active_node = data;
    search_state = 0; // Start searching
    search_timer = 0.5f;
    return true; // Assume success; actual result determined in update
}

LinkedList::~LinkedList() {
    clear();
}