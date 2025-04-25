#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include "raylib.h"
#include "raymath.h"
#include "LinkedList.hpp"
#include "Config.hpp"

// Constants
#define NODE_WIDTH 80.0f
#define NODE_HEIGHT 60.0f
#define NODE_RADIUS 30.0f
#define NODE_SPACING 40.0f
#define ANIM_SPEED 5.0f
#define ARROW_HEAD_LENGTH 15.0f
#define ARROW_HEAD_ANGLE (20.0f * DEG2RAD)
#define ANIM_SMOOTHNESS 0.1f

// Static member initialization
float LinkedList::nodeScale = 1.0f;
int LinkedList::currentDisplayMode = 0;
float LinkedList::listScrollX = 0.0f;

LinkedList::LinkedList() :
    head(nullptr),
    node_rad(35.0f),
    active_node(-1),
    anim_speed(5.0f),
    nodeCount(0),
    search_state(-1),
    search_timer(0.0f),
    deleteState(DeleteState::IDLE),
    deleteTimer(0.0f),
    nodeToDelete(nullptr),
    prevNode(nullptr) {
}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::calculate_layout() {
    // Constants for layout
    const int MAX_NODES_PER_ROW = 10;
    const float ROW_SPACING = 100.0f;
    const float MENU_WIDTH = ScreenWidth / 5.0f;
    const float AVAILABLE_WIDTH = ScreenWidth - MENU_WIDTH;

    // Calculate node count
    nodeCount = 0;
    Node* temp = head;
    while (temp) {
        nodeCount++;
        temp = temp->next;
    }

    // Calculate how many rows we need
    int rowCount = (nodeCount + MAX_NODES_PER_ROW - 1) / MAX_NODES_PER_ROW;

    // Calculate total content height needed for scrolling
    contentHeight = rowCount * (NODE_HEIGHT + ROW_SPACING) + 100; // Add padding

    // Center the rows vertically (without scroll offset here)
    float startY = 150.0f; // Fixed starting position, scrolling will handle the offset

    // Calculate positions
    int index = 0;
    temp = head;
    while (temp) {
        int row = index / MAX_NODES_PER_ROW;
        int col = index % MAX_NODES_PER_ROW;

        int nodesInThisRow = std::min(nodeCount - (row * MAX_NODES_PER_ROW), MAX_NODES_PER_ROW);
        float rowWidth = nodesInThisRow * (NODE_WIDTH + NODE_SPACING);
        float startX = MENU_WIDTH + (AVAILABLE_WIDTH - rowWidth) / 2;

        float target_x = startX + col * (NODE_WIDTH + NODE_SPACING);
        float target_y = startY + row * (NODE_HEIGHT + ROW_SPACING);

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
    deleteState = DeleteState::SEARCHING;
    active_node = data;
    start_delete_animation(data);
}

void LinkedList::start_delete_animation(int value) {
    Node* current = head;
    while (current) {
        current->searched = false;
        current->is_highlighted = false;
        current = current->next;
    }

    active_node = value;
    deleteState = DeleteState::SEARCHING;
    deleteTimer = 0.5f;
    nodeToDelete = nullptr;
    prevNode = nullptr;

    if (head && head->data != value) {
        prevNode = head;
        while (prevNode->next && prevNode->next->data != value) {
            prevNode = prevNode->next;
        }
    }
}

void LinkedList::update_delete_animation(float deltaTime) {
    switch (deleteState) {
    case DeleteState::SEARCHING:
        deleteTimer -= deltaTime;
        if (deleteTimer <= 0.0f) {
            deleteTimer = 0.5f;
            Node* current = head;
            while (current && current->searched) {
                current = current->next;
            }

            if (current) {
                current->is_highlighted = true;
                current->searched = true;

                if (current->data == active_node) {
                    nodeToDelete = current;
                    deleteState = DeleteState::FOUND;
                    deleteTimer = 1.0f;
                    return;
                }
            }
            else {
                deleteState = DeleteState::IDLE;
            }
        }
        break;

    case DeleteState::FOUND:
        deleteTimer -= deltaTime;
        if (deleteTimer <= 0.0f) {
            deleteState = DeleteState::DELETING;
            deleteTimer = 1.0f;
        }
        break;

    case DeleteState::DELETING:
        deleteTimer -= deltaTime;
        if (nodeToDelete) {
            nodeToDelete->scale = deleteTimer;
            nodeToDelete->color.a = static_cast<unsigned char>(deleteTimer * 255);
        }

        if (deleteTimer <= 0.0f && nodeToDelete) {
            if (nodeToDelete == head) {
                head = head->next;
            }
            else if (prevNode) {
                prevNode->next = nodeToDelete->next;
            }

            delete nodeToDelete;
            nodeCount--;
            calculate_layout();

            deleteState = DeleteState::IDLE;
            nodeToDelete = nullptr;
            prevNode = nullptr;
            active_node = -1;
        }
        break;

    case DeleteState::IDLE:
        break;
    }
}

void LinkedList::update_node_animation(Node* node, float delta_time) {
    if (!Vector2Equals(node->pos, node->target_pos)) {
        node->pos = Vector2Lerp(node->pos, node->target_pos, ANIM_SMOOTHNESS);
        if (Vector2Distance(node->pos, node->target_pos) < 0.5f) {
            node->pos = node->target_pos;
        }
    }
}

void LinkedList::update() {
    float deltaTime = GetFrameTime();

    // Handle scrolling input
    float wheelMove = GetMouseWheelMove();
    if (wheelMove != 0) {
        scrollOffset -= wheelMove * 20.0f; // Adjust scroll speed as needed

        // Clamp scrolling to prevent going too far
        float maxScroll = contentHeight - ScreenHeight;
        scrollOffset = Clamp(scrollOffset, 0.0f, maxScroll > 0 ? maxScroll : 0.0f);
    }

    if (deleteState != DeleteState::IDLE) {
        update_delete_animation(deltaTime);
    }

    // Update node animations (position smoothing)
    Node* temp = head;
    while (temp) {
        update_node_animation(temp, deltaTime);
        temp = temp->next;
    }

    if (search_state == 0) {
        search_timer -= deltaTime;
        if (search_timer <= 0.0f) {
            search_timer = 0.5f;
            Node* current = head;
            while (current) {
                if (!current->is_highlighted) {
                    current->is_highlighted = true;
                    if (current->data == active_node) {
                        search_state = 1;
                    }
                    break;
                }
                if (!current->next) {
                    search_state = 2;
                }
                current = current->next;
            }
        }
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
    deleteState = DeleteState::IDLE;
    scrollOffset = 0.0f;
    contentHeight = 0.0f;
}

int LinkedList::get_active() const {
    return active_node;
}

void LinkedList::rand_list(int n_nodes) {
    clear();
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < n_nodes; i++) {
        add_node(rand() % 100 + 1);
    }
}

bool LinkedList::load_from_file(const string& filename) {
    clear(); // Clear existing list

    ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    int value;
    while (file >> value) {
        // Validate input (optional)
        if (value < -9999 || value > 9999) {
            std::cerr << "Warning: Skipping invalid value " << value << std::endl;
            continue;
        }
        add_node(value);
    }

    if (nodeCount == 0) {
        std::cerr << "Warning: File was empty or contained no valid numbers" << std::endl;
    }

    file.close();
    calculate_layout(); // Update visual layout
    return true;
}

void LinkedList::print_list() const {
    Node* current = head;
    while (current) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

void LinkedList::draw_node(const Node* node) const {
    if (!node) return;

    // Apply scroll offset to node position
    Vector2 drawPos = { node->pos.x, node->pos.y - scrollOffset };

    std::string dataText = std::to_string(node->data);
    float scale = (node == nodeToDelete) ? node->scale : 1.0f;
    int fontSize = static_cast<int>(20 * nodeScale * scale);

    Color nodeColor = node->is_highlighted ? C[5] : C[1];
    if (node == nodeToDelete) {
        nodeColor.a = node->color.a;
    }

    float radius = NODE_RADIUS * nodeScale * scale;
    DrawCircleV(drawPos, radius, nodeColor);
    DrawCircleLinesV(drawPos, radius, C[3]);

    if (node == nodeToDelete && deleteState == DeleteState::DELETING) {
        DrawText("Deleting...", drawPos.x - 40, drawPos.y - 10, 20, RED);
    }
    else {
        int width = MeasureText(dataText.c_str(), fontSize);
        DrawText(dataText.c_str(), drawPos.x - width / 2, drawPos.y - fontSize / 2,
            fontSize, node->is_highlighted ? BLACK : C[0]);
    }
}

void LinkedList::draw_link(const Node* from, const Node* to) const {
    if (!from || !to) return;

    // Apply scroll offset to positions
    Vector2 fromPos = { from->pos.x, from->pos.y - scrollOffset };
    Vector2 toPos = { to->pos.x, to->pos.y - scrollOffset };

    Vector2 direction = Vector2Subtract(toPos, fromPos);
    float distance = Vector2Length(direction);
    if (distance < 1.0f) return;

    direction = Vector2Normalize(direction);

    Vector2 start_point = Vector2Add(fromPos, Vector2Scale(direction, NODE_RADIUS * nodeScale));
    Vector2 end_point = Vector2Subtract(toPos, Vector2Scale(direction, NODE_RADIUS * nodeScale));

    DrawLineEx(start_point, end_point, 3.0f * nodeScale, C[3]);

    if (distance > NODE_RADIUS * 2 * nodeScale) {
        float arrowAngle = 20.0f * DEG2RAD;
        Vector2 arrow_left = {
            end_point.x - ARROW_HEAD_LENGTH * (cosf(arrowAngle) * direction.x + sinf(arrowAngle) * direction.y),
            end_point.y - ARROW_HEAD_LENGTH * (cosf(arrowAngle) * direction.y - sinf(arrowAngle) * direction.x)
        };

        Vector2 arrow_right = {
            end_point.x - ARROW_HEAD_LENGTH * (cosf(arrowAngle) * direction.x - sinf(arrowAngle) * direction.y),
            end_point.y - ARROW_HEAD_LENGTH * (cosf(arrowAngle) * direction.y + sinf(arrowAngle) * direction.x)
        };

        DrawLineEx(end_point, arrow_left, 3.0f * nodeScale, C[3]);
        DrawLineEx(end_point, arrow_right, 3.0f * nodeScale, C[3]);
    }
}

void LinkedList::draw() const {
    // Set up scissor mode to clip drawing to visible area
    float menuWidth = ScreenWidth / 5.0f;
    BeginScissorMode(menuWidth, 0, ScreenWidth - menuWidth, ScreenHeight);

    Node* current = head;
    while (current) {
        if (current->next) {
            draw_link(current, current->next);
        }
        current = current->next;
    }

    current = head;
    while (current) {
        draw_node(current);
        current = current->next;
    }

    EndScissorMode();

    if (contentHeight > ScreenHeight) {
        float scrollRatio = scrollOffset / (contentHeight - ScreenHeight);
        float scrollbarHeight = ScreenHeight * (ScreenHeight / contentHeight);

        DrawRectangle(ScreenWidth - 10, scrollRatio * (ScreenHeight - scrollbarHeight),
            5, scrollbarHeight, Fade(WHITE, 0.5f));
    }
}

bool LinkedList::search_node(int data) {
    // Reset previous search states
    Node* current = head;
    while (current) {
        current->is_highlighted = false;
        current->searched = false;
        current = current->next;
    }

    active_node = data;
    search_state = 0;  // Start search animation
    search_timer = 0.5f;

    // Actual search implementation
    current = head;
    bool found = false;
    while (current) {
        if (current->data == data) {
            found = true;
            break;
        }
        current = current->next;
    }
    return found;
}

int LinkedList::get_search_state() const {
    return search_state;
}

int LinkedList::Max(int a, int b) {
    return (a > b) ? a : b;
}