#include "Node.hpp"

Node::Node(int val, int depth, int height, int balanceFactor, int nodeIdex, bool isLeft, Vector2 position, Node* left, Node* right, Node* parent) {
    this->val = val;
    this->depth = depth;
    this->height = height;
    this->balanceFactor = balanceFactor;
    this->nodeIndex = nodeIndex;
    this->isLeft = isLeft;
    this->position = position;
    this->left = left;
    this->right = right;
    this->parent = parent;
}
