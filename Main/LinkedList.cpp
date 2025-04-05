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

    // Position calculation
    int count = 0;
    Node* temp = head;
    while (temp) {
        temp->pos.x = ScreenWidth / 4 + (ScreenWidth * 7.0f / 40) * count;
        temp->pos.y = ScreenHeight / 2;
        temp = temp->next;
        count++;
    }
}

void LinkedList::add_node_front(int data) {
    Node* new_node = new Node(data);
    new_node->next = head;
    head = new_node;

    // Update positions
    int count = 0;
    Node* temp = head;
    while (temp) {
        temp->pos.x = ScreenWidth / 4 + (ScreenWidth * 7.0f / 40) * count;
        temp->pos.y = ScreenHeight / 2;
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
        return;
    }

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

void LinkedList::update() {
    static Node* cur_node = nullptr;
    Vector2 mouse = GetMousePosition();

    // Find node to move
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

    // Update active node
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        bool miss = true;
        Node* current = head;
        while (current) {
            if (CheckCollisionPointCircle(mouse, current->pos, node_rad)) {
                if (active_node != current->data) {
                    if (active_node != -1) {
                        Node* temp = head;
                        while (temp && temp->data != active_node) temp = temp->next;
                        if (temp) temp->is_highlighted = false;
                    }
                    active_node = current->data;
                    current->is_highlighted = true;
                }
                else {
                    active_node = -1;
                    current->is_highlighted = false;
                }
                miss = false;
                break;
            }
            current = current->next;
        }
        if (miss && active_node != -1) {
            Node* temp = head;
            while (temp && temp->data != active_node) temp = temp->next;
            if (temp) temp->is_highlighted = false;
            active_node = -1;
        }
    }

    if (cur_node) {
        cur_node->pos = mouse;
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

    if (!node->is_highlighted) {
        DrawCircleV(node->pos, node_rad, C[1]);
    }
    else {
        DrawCircleV(node->pos, node_rad, C[5]);
    }
    DrawCircleLinesV(node->pos, node_rad, C[3]);
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

LinkedList::~LinkedList() {
    clear();
}