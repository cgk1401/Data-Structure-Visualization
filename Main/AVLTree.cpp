#include "AVLTree.hpp"
using namespace std;


AVLTree::AVLTree() {
	Root = nullptr;

	DistanceHorizontal = 60;
	DistanceVertical = 60;


}

void AVLTree::Insert(Node*& root, int data, vector<Node*>& NodeList) {
    for (Node* node : NodeList) {
        if (data == node->val) return;
    }
    InsertHelper(root, data, nullptr, NodeList);
    balanceTree();
    
    
}

Node* AVLTree::InsertHelper(Node*& root, int data, Node* parent, vector<Node*>& NodeList) {
    if (root == nullptr) {
        bool isLeft = (parent && data < parent->val);
        root = new Node(data, (parent ? parent->depth + 1 : 1), 1, 0, NodeList.size(), isLeft,
            Vector2{ (parent ? parent->position.x + (isLeft ? -DistanceHorizontal : DistanceHorizontal) : ScreenWidth / 2),
                     (parent ? parent->position.y + DistanceVertical : 100) },
            nullptr, nullptr, parent);
        NodeList.push_back(root);
        return root;
    }

    if (data < root->val) {
        root->left = InsertHelper(root->left, data, root, NodeList);
    }
    else if (data > root->val) {
        root->right = InsertHelper(root->right, data, root, NodeList);
    }

    return root;  
}
void AVLTree::MoveTree(Node* root, bool isLeft) {
    if (root == nullptr) return;
    root->position.x = root->position.x+ ( isLeft ? -DistanceHorizontal : DistanceHorizontal);
    root->position.y = (root->depth - Root->depth) * DistanceVertical + 150 * 1.0f;
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
            node->position = { ScreenWidth / 2 - 30 , 150 * 1.0f };
            node->depth = 1;
        }
        else {
            Node* cur = Root;
            int depth = 1;
            while (cur) {
                if (node->val != cur->val) node->depth = ++depth;

                if (node->val < cur->val) {
                    //if (cur->left && node->val > cur->left->val) 
                    MoveTree(cur->left, true);
                    cur = cur->left;
                }
                else if (node->val > cur->val) {
                    //if (cur->right && node->val < cur->right->val) 
                    MoveTree(cur->right, false);
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
	if (node == nullptr) return;

	// Vẽ đường nối từ node cha đến node con
	if (node->left) {
		DrawLineEx(node->position, node->left->position, 3, DARKGRAY);
	}
	if (node->right) {
		DrawLineEx(node->position, node->right->position, 3, DARKGRAY);
	}

	// Vẽ node
	DrawCircle(node->position.x, node->position.y, 30, BLACK);
	DrawText(TextFormat("%d", node->val), node->position.x - 10, node->position.y - 10, 20, RED);

	// Đệ quy vẽ node con
	DrawTreeHelper(node->left);
	DrawTreeHelper(node->right);
}



//void AVLTree::SetDistance(int sizetree) {
//	if (sizetree < 15) {
//		DistanceHorizontal = 100;
//		DistanceVertical = 100;
//	}
//	else if (sizetree < 30) {
//		DistanceHorizontal = 80;
//		DistanceVertical = 80;
//	}
//	else if (sizetree < 40) {
//		DistanceHorizontal = 60;
//		DistanceVertical = 80;
//	}
//	else {
//		DistanceHorizontal = 50;
//		DistanceVertical = 80;
//	}
//}
