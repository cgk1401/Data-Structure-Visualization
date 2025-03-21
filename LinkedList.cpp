#include "LinkedList.hpp"
#include <string>

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::add_node(int value) {
    Node* newNode = new Node(value);

    if (!head) {
        head = newNode;
        newNode->pos.x = GetScreenWidth() / 4;
        newNode->pos.y = GetScreenHeight() / 2;
    }
    else {
        Node* current = head;
        int index = 0;
        while (current->next) {
            current = current->next;
            index++;
        }
        current->next = newNode;
        newNode->pos.x = head->pos.x + (index + 1) * 100;
        newNode->pos.y = GetScreenHeight() / 2;
    }
    size++;
}

void LinkedList::delete_node(int value) {
    if (!head) return;

    if (head->value == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;

        // Reposition remaining nodes
        Node* current = head;
        int index = 0;
        while (current) {
            current->pos.x = GetScreenWidth() / 4 + index * 100;
            current->pos.y = GetScreenHeight() / 2;
            current = current->next;
            index++;
        }
        return;
    }

    Node* current = head;
    while (current->next && current->next->value != value) {
        current = current->next;
    }

    if (current->next) {
        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
        size--;

        // Reposition remaining nodes
        int index = 1;
        current = current->next;
        while (current) {
            current->pos.x = GetScreenWidth() / 4 + index * 100;
            current->pos.y = GetScreenHeight() / 2;
            current = current->next;
            index++;
        }
    }
}

void LinkedList::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}

void LinkedList::print_list() {
    Node* current = head;
    while (current) {
        std::cout << current->value << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

void LinkedList::draw_node(Node* node, int index) {
    float radius = 40.0f;
    DrawCircleV(node->pos, radius, WHITE);
    DrawCircleLinesV(node->pos, radius, BLACK);
    std::string valStr = std::to_string(node->value);
    int textWidth = MeasureText(valStr.c_str(), 20);
    DrawText(valStr.c_str(), node->pos.x - textWidth / 2, node->pos.y - 10, 20, BLACK);
}

void LinkedList::draw() {
    Node* current = head;
    int index = 0;

    while (current) {
        draw_node(current, index);

        if (current->next) {
            Vector2 start = { current->pos.x + 40, current->pos.y };
            Vector2 end = { current->next->pos.x - 40, current->next->pos.y };
            DrawLineV(start, end, BLACK);
            // Draw arrow
            DrawTriangle({ end.x - 10, end.y - 5 }, { end.x - 10, end.y + 5 }, end, BLACK);
        }

        current = current->next;
        index++;
    }
}

bool LinkedList::search(int value) {
    Node* current = head;
    while (current) {
        if (current->value == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}