﻿#include "AVLTree.hpp"
using namespace std;


AVLTree::AVLTree() {
    Root = nullptr;
    DistanceHorizontal = 50;
    DistanceVertical = 80;
}

AVLTree::~AVLTree() {
    Clear(Root);
    NodeList.clear();
}

void AVLTree::Insert(Node*& root, int data, vector<Node*>& NodeList, bool isNeedRotate) {
    for (Node* node : NodeList) {
        if (data == node->val) return;
    }
    InsertHelper(root, data, nullptr, NodeList, isNeedRotate);
}

Node* AVLTree::InsertHelper(Node*& root, int data, Node* parent, vector<Node*>& NodeList, bool isNeedRotate) {
    if (root == nullptr) {
        bool isLeft = (parent && data < parent->val);
        root = new Node(data, (parent ? parent->depth + 1 : 1), 1, 0, NodeList.size(), isLeft,
            Vector2{ (parent ? parent->position.x + (isLeft ? -DistanceHorizontal : DistanceHorizontal) : ScreenWidth * 5 / 8.0f),
                     (parent ? parent->position.y + DistanceVertical : 250) },
            nullptr, nullptr, parent, false, false, false, false);
        NodeList.push_back(root);
        return root;
    }
    if (data < root->val) {
        root->left = InsertHelper(root->left, data, root, NodeList, isNeedRotate);
    }
    else if (data > root->val) {
        root->right = InsertHelper(root->right, data, root, NodeList, isNeedRotate);
    }
    if (isNeedRotate == true) {
        root->balanceFactor = GetHeight(root->left) - GetHeight(root->right);
        root->height = 1 + max(GetHeight(root->left), GetHeight(root->right));
        if (root->balanceFactor > 1 && data < root->left->val) {
            // Left - Left
            root = RotationRight(root);
            return root;
        }
        else if (root->balanceFactor > 1 && data > root->left->val) {
            // Left - Right
            root->left = RotationLeft(root->left);
            root = RotationRight(root);
            return root;
        }
        else if (root->balanceFactor < -1 && data > root->right->val) {
            // Right - Right 
            root = RotationLeft(root);
            return root;
        }
        else if (root->balanceFactor < -1 && data < root->right->val) {
            // Right - Right
            root->right = RotationRight(root->right);
            root = RotationLeft(root);
            return root;
        }
    }
    return root;
}

int AVLTree::GetHeight(Node* root) {
    if (root == nullptr) return 0;
    return root->height;
}

Node* AVLTree::RotationLeft(Node*& root) {
    if (root == nullptr) return nullptr;
    Node* newroot = root->right;
    Node* child = newroot->left;
    newroot->parent = root->parent;
    newroot->left = root;
    root->parent = newroot;
    root->right = child;
    if (child != nullptr) {
        child->parent = root;
        child->isLeft = false;
    }
    newroot->isLeft = root->isLeft;
    root->isLeft = true;
    root->height = 1 + max(GetHeight(root->left), GetHeight(root->right));
    newroot->height = 1 + max(GetHeight(newroot->left), GetHeight(newroot->right));
    swap(NodeList[root->nodeIndex], NodeList[newroot->nodeIndex]);
    for (int i = 0; i < NodeList.size(); i++) NodeList[i]->nodeIndex = i;
    return newroot;
}

Node* AVLTree::RotationRight(Node*& root) {
    if (root == nullptr) return nullptr;
    Node* newroot = root->left;
    Node* child = newroot->right;
    newroot->parent = root->parent;
    newroot->right = root;
    root->parent = newroot;
    root->left = child;
    if (child != nullptr) {
        child->parent = root;
        child->isLeft = true;
    }
    newroot->isLeft = root->isLeft;
    root->isLeft = false;
    root->height = 1 + max(GetHeight(root->left), GetHeight(root->right));
    newroot->height = 1 + max(GetHeight(newroot->left), GetHeight(newroot->right));
    swap(NodeList[root->nodeIndex], NodeList[newroot->nodeIndex]);
    for (int i = 0; i < NodeList.size(); i++) NodeList[i]->nodeIndex = i;
    return newroot;
}

void AVLTree::UpdateHeightAndBalanceFactor(Node*& root) {
    if (root == nullptr) return;
    UpdateHeightAndBalanceFactor(root->left);
    UpdateHeightAndBalanceFactor(root->right);

    root->height = 1 + max(GetHeight(root->left), GetHeight(root->right));
    root->balanceFactor = GetHeight(root->left) - GetHeight(root->right);
}

Node* AVLTree::GetNodeRotate() {
    UpdateHeightAndBalanceFactor(Root);
    Node* ans = nullptr;
    int maxdepth = -1;
    for (Node* node : NodeList) {
        if (abs(node->balanceFactor) > 1 && node->depth > maxdepth) {
            ans = node;
            maxdepth = ans->depth;
        }
    }
    return ans;
}

void AVLTree::Random() {
    random_device rd;
    mt19937 gen(rd());
    mt19937 gen1(rd());
    uniform_int_distribution<int> dist(2, 40);
    uniform_int_distribution<int> dist1(1, 200);
    int size = dist(gen);
    cout << size << " ";

    Clear(Root);
    NodeList.clear();
    if (size > 30) {
        DistanceHorizontal = 40;
        DistanceVertical = 70;
    }
    if (size > 35) {
        DistanceHorizontal = 35;
        DistanceVertical = 70;
    }
    set <int> se;
    while (se.size() < size) {
        int number_random = dist1(gen1);
        se.insert(number_random);
    }
    for (auto it : se) Insert(Root, it, NodeList, true);
    balanceTree();
}

void AVLTree::InitAVLTree(int val) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 200);
    int size = val;
    Clear(Root);
    NodeList.clear();
    if (size > 30) {
        DistanceHorizontal = 40;
        DistanceVertical = 80;
    }
    if (size > 35) {
        DistanceHorizontal = 35;
        DistanceVertical = 90;
    }
    set <int> se;
    while (se.size() < size) {
        int number_random = dist(gen);
        se.insert(number_random);
    }
    for (auto it : se) Insert(Root, it, NodeList, true);
    balanceTree();
}

void AVLTree::Clear(Node*& root) {
    if (root == nullptr) return;
    Clear(root->left);
    Clear(root->right);
    delete(root);
    root = nullptr;
}

void AVLTree::MoveTree(Node* root, bool isLeft) {
    if (root == nullptr) return;
    root->position.x = root->position.x + (isLeft ? -DistanceHorizontal : DistanceHorizontal);
    if (root->left != nullptr) MoveTree(root->left, isLeft);
    if (root->right != nullptr) MoveTree(root->right, isLeft);
}

void AVLTree::balanceTree() {
    if (Root == nullptr) return;

    vector<Node*> nodeList;
    queue<Node*> q;
    q.push(Root);


    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();
        nodeList.push_back(temp);
        if (temp->left) q.push(temp->left);
        if (temp->right) q.push(temp->right);
    }

    for (auto& node : nodeList) {
        if (node == Root) {
            node->position = { ScreenWidth * 5 / 8.0f  , 250 * 1.0f };
            node->depth = 1;
        }
        else {
            Node* cur = Root;
            int depth = 1;
            while (cur) {
                if (node->val != cur->val) node->depth = ++depth;

                if (node->val < cur->val) {
                    if (cur->left && node->val > cur->left->val) MoveTree(cur->left, true);
                    cur = cur->left;
                }
                else if (node->val > cur->val) {
                    if (cur->right && node->val < cur->right->val) MoveTree(cur->right, false);
                    cur = cur->right;
                }
                else {
                    if (node->isLeft)
                        node->position = { node->parent->position.x - DistanceHorizontal, node->parent->position.y + DistanceVertical };
                    else
                        node->position = { node->parent->position.x + DistanceHorizontal, node->parent->position.y + DistanceVertical };

                    break;
                }
            }
        }
    }
}

void AVLTree::DrawTree() {
    DrawTreeHelper(Root);
}

void AVLTree::DrawTreeHelper(Node* node) {
    for (Node* node : NodeList) {
        if (node->left) {
            DrawLineEx(node->position, node->left->position, 3, C[1]);
        }
        if (node->right) {
            DrawLineEx(node->position, node->right->position, 3, C[1]);
        }
    }
    int fontSize = 20;
    for (Node* node : NodeList) {
        string text = to_string(node->val);
        if (text.size() > 2) fontSize = 19;
        if (text.size() > 4) fontSize = 16;
        int textWidth = MeasureText(text.c_str(), fontSize);
        int textHeight = fontSize;

        if (node->isNodeInserted) {
            DrawCircle(node->position.x, node->position.y, 30, BLUE);
        }
        else if (node->isNodeHighLighted) {
            DrawCircle(node->position.x, node->position.y, 30, ORANGE);
        }
        else {
            DrawCircle(node->position.x, node->position.y, 30, C[3]);
        }
        DrawText(text.c_str(), node->position.x - textWidth / 2, node->position.y - textHeight / 2, fontSize, WHITE);
    }
}

void AVLTree::DeleteLeafNode(Node*& root, int key) {
    if (!root) return;

    if (key < root->val) {
        DeleteLeafNode(root->left, key);
    }
    else if (key > root->val) {
        DeleteLeafNode(root->right, key);
    }
    else {
        if (!root->left && !root->right) {
            Node* temp = root;
            root = nullptr;
            delete temp;
        }
    }

    if (root) UpdateHeightAndBalanceFactor(root);
}

int AVLTree::GetBalanceFactor(Node* node) {
    if (!node) return 0;
    int leftHeight = node->left ? node->left->height : 0;
    int rightHeight = node->right ? node->right->height : 0;
    return leftHeight - rightHeight;
}

void AVLTree::RebalanceChild(Node*& root, Node* noderotate) {
    if (!root) return;

    UpdateHeightAndBalanceFactor(Root);

    if (root->balanceFactor > 1 && root == noderotate) {

        if (GetBalanceFactor(root->left) < 0) {
            root->left = RotationLeft(root->left);
            return;
        }
    }
    else if (root->balanceFactor < -1 && root == noderotate) {

        if (GetBalanceFactor(root->right) > 0) {
            root->right = RotationRight(root->right);
            return;
        }
    }

    RebalanceChild(root->left, noderotate);
    RebalanceChild(root->right, noderotate);

}

void AVLTree::RebalanceParent(Node*& root, Node* noderotate) {
    if (!root) return;
    if (root == noderotate) {
        if (root->balanceFactor > 1) root = RotationRight(root);
        else root = RotationLeft(root);
        return;
    }
    RebalanceParent(root->left, noderotate);
    RebalanceParent(root->right, noderotate);
}

Node* AVLTree::DeleteNode(Node* root, int key) {
    if (root == nullptr) return nullptr;
    else if (root->val > key) root->left = DeleteNode(root->left, key);
    else if (root->val < key) root->right = DeleteNode(root->right, key);
    else {
        Node* nodedelete = root;
        if (root->left == nullptr) {
            root = root->right;
            if (root != nullptr) {
                root->parent = nodedelete->parent;
                if (nodedelete->parent != nullptr) { 
                    if (nodedelete->isLeft == true) {
                        nodedelete->parent->left = root;
                        root->isLeft = true;
                    }
                    else {
                        nodedelete->parent->right = root;
                        root->isLeft = false;
                    }
                }
                else {
                    root->isLeft = false;
                }
            }
        }
        else if (root->right == nullptr) {
            root = root->left;
            if (root != nullptr) {
                root->parent = nodedelete->parent;
                if (nodedelete->parent != nullptr) { 
                    if (nodedelete->isLeft == true) {
                        nodedelete->parent->left = root;
                        root->isLeft = true;
                    }
                    else {
                        nodedelete->parent->right = root;
                        root->isLeft = false;
                    }
                }
                else {
                    root->isLeft = false;
                }
            }
        }
        else {
            Node* pre = root->left;
            while (pre->right != nullptr) {
                pre = pre->right;
            }
            root->val = pre->val; 
            root->left = DeleteNode(root->left, pre->val); 
            return root;
        }
        auto it = find(NodeList.begin(), NodeList.end(), nodedelete);
        if (it != NodeList.end()) {
            NodeList.erase(it);
            delete nodedelete;

            for (int i = 0; i < NodeList.size(); ++i) {
                NodeList[i]->nodeIndex = i;
            }
        }
    }
    return root;
}




