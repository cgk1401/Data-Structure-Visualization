#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <ctime>
#include "raylib.h"
#include "raymath.h"
#include "LinkedList.hpp"
#include "Config.hpp"

#define NODE_WIDTH 80.0f
#define NODE_HEIGHT 60.0f
#define NODE_RADIUS 30.0f
#define NODE_SPACING 40.0f
#define ARROW_HEAD_LENGTH 15.0f
#define ARROW_HEAD_ANGLE (20.0f * DEG2RAD)

float LinkedList::nodeScale = 1.0f;
int LinkedList::currentDisplayMode = 0;
float LinkedList::listScrollX = 0.0f;

LinkedList::LinkedList() :
    head(nullptr),
    node_rad(35.0f),
    active_node(-1),
    nodeCount(0),
    search_state(-1),
    deleteState(DeleteState::IDLE),
    nodeToDelete(nullptr),
    prevNode(nullptr),
    lastDeletedNode(nullptr),
    lastDeletedPrevNode(nullptr),
    lastInsertedNode(nullptr),
    currentAnimation(AnimationType::NONE),
    animationStep(0),
    isPaused(false),
    animationDuration(0.5f),
    currentAnimationTime(0.0f)
{
    descriptionBox.SetDescription("Ready to start.");
}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::calculate_layout() {
    const int MAX_NODES_PER_ROW = 10;
    const float ROW_SPACING = 100.0f;
    const float MENU_WIDTH = ScreenWidth / 5.0f;
    const float AVAILABLE_WIDTH = ScreenWidth - MENU_WIDTH;

    nodeCount = 0;
    Node* temp = head;
    while (temp) {
        nodeCount++;
        temp = temp->next;
    }

    int rowCount = (nodeCount + MAX_NODES_PER_ROW - 1) / MAX_NODES_PER_ROW;
    contentHeight = rowCount * (NODE_HEIGHT + ROW_SPACING) + 100;

    float startY = 150.0f;
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

        temp->pos = { target_x, target_y };
        temp->target_pos = { target_x, target_y };
        temp = temp->next;
        index++;
    }
}

void LinkedList::add_node(int data) {
    Node* new_node = new Node(data);
    new_node->is_highlighted = false;

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
    lastDeletedNode = nullptr;
    lastDeletedPrevNode = nullptr;
    active_node = data;
    start_animation(AnimationType::DELETE, data);
}

void LinkedList::start_animation(AnimationType type, int value) {
    Node* current = head;
    while (current) {
        current->is_highlighted = false;
        current->searched = false;
        current = current->next;
    }

    active_node = value;
    currentAnimation = type;
    animationStep = 0;
    deleteState = DeleteState::IDLE;
    search_state = -1;
    nodeToDelete = nullptr;
    prevNode = nullptr;
    isPaused = true;

    switch (type) {
    case AnimationType::INSERT:
        descriptionBox.SetDescription("Starting insertion of value " + std::to_string(value) + ".");
        break;
    case AnimationType::DELETE:
        descriptionBox.SetDescription("Starting deletion of value " + std::to_string(value) + ".");
        break;
    case AnimationType::SEARCH:
        descriptionBox.SetDescription("Starting search for value " + std::to_string(value) + ".");
        search_state = 0;
        break;
    default:
        descriptionBox.SetDescription("Invalid operation.");
        currentAnimation = AnimationType::NONE;
        break;
    }
}

void LinkedList::animate_insert(int val) {
    switch (animationStep) {
    case 0: {
        Node* oldTail = nullptr;
        if (head) {
            oldTail = head;
            while (oldTail->next) oldTail = oldTail->next;
        }

        Node* newNode = new Node(val);
        lastInsertedNode = newNode;

        if (!head) {
            head = newNode;
        }
        else {
            oldTail->next = newNode;
        }

        nodeCount++;
        calculate_layout();

        newNode->is_highlighted = true;
        if (oldTail) oldTail->is_highlighted = false;

        descriptionBox.SetDescription("Inserted new node");
        animationStep = 1;
        break;
    }

    case 1: {
        if (lastInsertedNode) {
            lastInsertedNode->is_highlighted = false;
        }
        currentAnimation = AnimationType::NONE;
        animationStep = 0;
        descriptionBox.SetDescription("Insertion complete");
        break;
    }
    }
}

void LinkedList::animate_delete(int val) {
    switch (animationStep) {
    case 0: {
        Node* current = head;
        while (current) {
            current->is_highlighted = false;
            current->searched = false;
            current = current->next;
        }

        if (!head) {
            deleteState = DeleteState::IDLE;
            animationStep = 2;
            descriptionBox.SetDescription("List is empty");
            break;
        }

        current = head;
        current->is_highlighted = true;
        current->searched = true;
        descriptionBox.SetDescription("Checking head node");

        if (current->data == val) {
            lastDeletedNode = current;
            lastDeletedPrevNode = nullptr;

            nodeToDelete = current;
            deleteState = DeleteState::FOUND;
            animationStep = 2;
            descriptionBox.SetDescription("Found at head");
        }
        else {
            prevNode = current;
            animationStep = 1;
        }
        break;
    }

    case 1: {
        if (!prevNode || !prevNode->next) {
            deleteState = DeleteState::IDLE;
            animationStep = 2;
            descriptionBox.SetDescription("Value not found");
            break;
        }

        Node* current = head;
        while (current) {
            current->is_highlighted = false;
            current->searched = false;
            current = current->next;
        }

        current = prevNode->next;
        current->is_highlighted = true;
        current->searched = true;
        descriptionBox.SetDescription("Checking next node");

        if (current->data == val) {
            lastDeletedNode = current;
            lastDeletedPrevNode = prevNode;

            nodeToDelete = current;
            deleteState = DeleteState::FOUND;
            animationStep = 2;
            descriptionBox.SetDescription("Found node");
        }
        else {
            prevNode = current;
        }
        break;
    }

    case 2: {
        if (deleteState == DeleteState::FOUND && nodeToDelete) {
            if (nodeToDelete == head) {
                head = head->next;
            }
            else if (prevNode) {
                prevNode->next = nodeToDelete->next;
            }

            nodeToDelete->is_highlighted = false;
            nodeToDelete->searched = false;

            nodeCount--;
            calculate_layout();

            descriptionBox.SetDescription("Deleted node");
        }
        currentAnimation = AnimationType::NONE;
        animationStep = 0;
        break;
    }
    }
}

void LinkedList::animate_search(int val) {
    switch (animationStep) {
    case 0: {
        Node* temp = head;
        while (temp) {
            temp->is_highlighted = false;
            temp->searched = false;
            temp = temp->next;
        }

        if (!head) {
            search_state = 2;
            animationStep = 2;
            descriptionBox.SetDescription("List is empty");
            break;
        }

        head->is_highlighted = true;
        head->searched = true;
        descriptionBox.SetDescription("Visiting node with value " + std::to_string(head->data));

        if (head->data == val) {
            search_state = 1;
            animationStep = 2;
            descriptionBox.SetDescription("Found " + std::to_string(val));
        }
        else {
            prevNode = head;
            animationStep = 1;
        }
        break;
    }
    case 1: {
        if (!prevNode || !prevNode->next) {
            search_state = 2;
            animationStep = 2;
            descriptionBox.SetDescription(val + " not found");
            break;
        }

        Node* temp = head;
        while (temp) {
            temp->is_highlighted = false;
            temp->searched = false;
            temp = temp->next;
        }

        Node* current = prevNode->next;
        current->is_highlighted = true;
        current->searched = true;
        descriptionBox.SetDescription("Visiting node with value " + std::to_string(current->data));

        if (current->data == val) {
            search_state = 1;
            animationStep = 2;
            descriptionBox.SetDescription("Found " + std::to_string(val));
        }
        else {
            prevNode = current;
        }
        break;
    }
    case 2: {
        if (search_state != 1) {
            Node* temp = head;
            while (temp) {
                temp->is_highlighted = false;
                temp->searched = false;
                temp = temp->next;
            }
        }
        currentAnimation = AnimationType::NONE;
        animationStep = 0;
        descriptionBox.SetDescription("Search complete");
        break;
    }
    }
}

void LinkedList::update() {
    float deltaTime = GetFrameTime();

    float wheelMove = GetMouseWheelMove();
    if (wheelMove != 0) {
        scrollOffset -= wheelMove * 20.0f;
        float maxScroll = contentHeight - ScreenHeight;
        scrollOffset = Clamp(scrollOffset, 0.0f, maxScroll > 0 ? maxScroll : 0.0f);
    }

    Node* current = head;
    while (current) {
        current->pos = Vector2Lerp(current->pos, current->target_pos, 10.0f * deltaTime);
        current = current->next;
    }

    if (currentAnimation != AnimationType::NONE && !isPaused) {
        currentAnimationTime += deltaTime;
        if (currentAnimationTime >= animationDuration) {
            currentAnimationTime = 0.0f;

            switch (currentAnimation) {
            case AnimationType::INSERT:
                animate_insert(active_node);
                break;
            case AnimationType::DELETE:
                animate_delete(active_node);
                break;
            case AnimationType::SEARCH:
                animate_search(active_node);
                break;
            default:
                currentAnimation = AnimationType::NONE;
                descriptionBox.SetDescription("Ready to start.");
                break;
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
    descriptionBox.SetDescription("List cleared.");
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
    descriptionBox.SetDescription("Generated random list with " + std::to_string(n_nodes) + " nodes.");
}

bool LinkedList::load_from_file(const string& filename) {
    clear();
    ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " + filename << std::endl;
        descriptionBox.SetDescription("Failed to load file: " + filename);
        return false;
    }

    int value;
    while (file >> value) {
        if (value < -9999 || value > 9999) {
            std::cerr << "Warning: Skipping invalid value " << value << std::endl;
            continue;
        }
        add_node(value);
    }

    if (nodeCount == 0) {
        std::cerr << "Warning: File was empty or contained no valid numbers" << std::endl;
        descriptionBox.SetDescription("File was empty or invalid.");
    }
    else {
        descriptionBox.SetDescription("Loaded list from file: " + filename);
    }

    file.close();
    calculate_layout();
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

    Vector2 drawPos = { node->pos.x, node->pos.y - scrollOffset };
    std::string dataText = std::to_string(node->data);
    int fontSize = static_cast<int>(20 * nodeScale);

    Color baseColor = node->is_highlighted ? C[5] : C[1];
    Color borderColor = node->searched ? GOLD : C[3];
    float radius = NODE_RADIUS * nodeScale;

    DrawCircleV(drawPos, radius, baseColor);
    DrawCircleLinesV(drawPos, radius, borderColor);

    if (node == nodeToDelete && deleteState == DeleteState::DELETING) {
        float fade = 1.0f - (currentAnimationTime / animationDuration);
        DrawText("Deleting...", drawPos.x - 40, drawPos.y - 10, 20, Fade(RED, fade));
    }
    else {
        int width = MeasureText(dataText.c_str(), fontSize);
        DrawText(dataText.c_str(), drawPos.x - width / 2, drawPos.y - fontSize / 2,
            fontSize, node->is_highlighted ? BLACK : C[0]);
    }
}

void LinkedList::draw_link(const Node* from, const Node* to) const {
    if (!from || !to) return;

    Vector2 fromPos = { from->pos.x, from->pos.y - scrollOffset };
    Vector2 toPos = { to->pos.x, to->pos.y - scrollOffset };

    Vector2 direction = Vector2Subtract(toPos, fromPos);
    float distance = Vector2Length(direction);
    if (distance < 1.0f) return;

    direction = Vector2Normalize(direction);

    Vector2 start_point = Vector2Add(fromPos, Vector2Scale(direction, NODE_RADIUS * nodeScale));
    Vector2 end_point = Vector2Subtract(toPos, Vector2Scale(direction, NODE_RADIUS * nodeScale));

    Color linkColor = from->is_highlighted && to->is_highlighted ? GOLD : C[3];
    DrawLineEx(start_point, end_point, 3.0f * nodeScale, linkColor);

    if (distance > NODE_RADIUS * 2 * nodeScale) {
        float activation = 20.0f * DEG2RAD;
        Vector2 arrow_left = {
            end_point.x - ARROW_HEAD_LENGTH * (cosf(activation) * direction.x + sinf(activation) * direction.y),
            end_point.y - ARROW_HEAD_LENGTH * (cosf(activation) * direction.y - sinf(activation) * direction.x)
        };
        Vector2 arrow_right = {
            end_point.x - ARROW_HEAD_LENGTH * (cosf(activation) * direction.x - sinf(activation) * direction.y),
            end_point.y - ARROW_HEAD_LENGTH * (cosf(activation) * direction.y + sinf(activation) * direction.x)
        };

        DrawLineEx(end_point, arrow_left, 3.0f * nodeScale, linkColor);
        DrawLineEx(end_point, arrow_right, 3.0f * nodeScale, linkColor);
    }
}

void LinkedList::draw() const {
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

    descriptionBox.DrawDescriptionBox();
    EndScissorMode();

    if (contentHeight > ScreenHeight) {
        float scrollRatio = scrollOffset / (contentHeight - ScreenHeight);
        float scrollbarHeight = ScreenHeight * (ScreenHeight / contentHeight);
        DrawRectangle(ScreenWidth - 10, scrollRatio * (ScreenHeight - scrollbarHeight),
            5, scrollbarHeight, Fade(WHITE, 0.5f));
    }
}

bool LinkedList::search_node(int data) {
    active_node = data;
    start_animation(AnimationType::SEARCH, data);
    return true;
}

int LinkedList::get_search_state() const {
    return search_state;
}

void LinkedList::set_paused(bool paused) {
    isPaused = paused;
    descriptionBox.SetDescription(isPaused ? "Animation paused." : "Animation resumed.");
}

void LinkedList::step_forward() {
    if (currentAnimation != AnimationType::NONE && isPaused) {
        switch (currentAnimation) {
        case AnimationType::INSERT:
            animate_insert(active_node);
            break;
        case AnimationType::DELETE:
            animate_delete(active_node);
            break;
        case AnimationType::SEARCH:
            animate_search(active_node);
            break;
        default:
            break;
        }
    }
}

void LinkedList::step_backward() {
    if (currentAnimation == AnimationType::NONE) {
        descriptionBox.SetDescription("No operation to undo");
        return;
    }

    switch (currentAnimation) {
    case AnimationType::INSERT: {
        if (lastInsertedNode) {
            // Special case: undoing insertion at head
            if (head == lastInsertedNode) {
                head = head->next;
            }
            else {
                // Find the node before the inserted node
                Node* prev = head;
                while (prev && prev->next != lastInsertedNode) {
                    prev = prev->next;
                }

                if (prev) {
                    prev->next = lastInsertedNode->next;
                }
            }

            delete lastInsertedNode;
            nodeCount--;
            calculate_layout();
            lastInsertedNode = nullptr;

            descriptionBox.SetDescription("Undo: Removed inserted node");
        }
        currentAnimation = AnimationType::NONE;
        break;
    }

    case AnimationType::DELETE: {
        if (lastDeletedNode) {
            // Restore the node to its original position
            if (lastDeletedPrevNode) {
                // Node was in middle or end of list
                lastDeletedNode->next = lastDeletedPrevNode->next;
                lastDeletedPrevNode->next = lastDeletedNode;
            }
            else {
                // Node was at head
                lastDeletedNode->next = head;
                head = lastDeletedNode;
            }

            nodeCount++;
            calculate_layout();

            // Restore highlight states
            lastDeletedNode->is_highlighted = true;
            if (lastDeletedPrevNode) {
                lastDeletedPrevNode->is_highlighted = true;
            }

            descriptionBox.SetDescription("Undo: Restored deleted node " +
                std::to_string(lastDeletedNode->data));

            // Don't clear these yet - allow multiple undos if needed
            // lastDeletedNode = nullptr;
            // lastDeletedPrevNode = nullptr;
        }
        currentAnimation = AnimationType::NONE;
        break;
    }

    case AnimationType::SEARCH: {
        Node* current = head;
        while (current) {
            current->is_highlighted = false;
            current->searched = false;
            current = current->next;
        }
        descriptionBox.SetDescription("Undo: Cleared search highlights");
        currentAnimation = AnimationType::NONE;
        break;
    }
    }
}

int LinkedList::Max(int a, int b) {
    return (a > b) ? a : b;
}