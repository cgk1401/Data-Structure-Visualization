#include "InsertAnimationAVLTree.hpp"

InsertAnimationAVLTree::InsertAnimationAVLTree(AVLTree* root) {
	this->tree = root;
	this->InsertValue = -1;
	this->Indexpath = 0;
	this->AnimationStep = 0;
	this->path.clear();
	this->AnimationTime = 0.0f;
	this->duration = 0.5f;
	this->newNode = nullptr;
	this->NodeRotate = nullptr;
	this->NodeDelete = nullptr;
	this->NodeReplace = nullptr;
	this->RotateSecond = false;
	this->GhostNode = nullptr;
	this->GhostStartPosition = {0,0};
	this->exist = false;
	this->RotateStartPosition.clear();
	this->RotateTargetPosition.clear();
}

void InsertAnimationAVLTree::StartInsertAnimation(int value) {
	this->InsertValue = value;
	this->Indexpath = 0;
	this->AnimationStep = 1;
	this->AnimationTime = 0.0f;
	this->duration = 0.5f;
	this->StartPosition.clear();
	this->TargetPosition.clear();
	this->path.clear();
	this->newNode = nullptr;
	this->exist = false;
	this->NodeReplace = nullptr;

	for (Node* node : tree->NodeList) {
		StartPosition[node] = node->position;
	}

	Node* curr = tree->Root;
	while (curr != nullptr) {
		path.push_back(curr);
		if (value < curr->val) curr = curr->left;
		else if (value > curr->val) curr = curr->right;
		else if (value == curr->val) {
			exist = true;
			return;
		}
		else break;
	}
	tree->Insert(tree->Root, value, tree->NodeList, false);
	tree->UpdateHeightAndBalanceFactor(tree->Root);
	tree->balanceTree();
	for (Node* node : tree->NodeList) {
		if (node->val == value) {
			newNode = node;
			break;
		}
	}
	for (Node* node : tree->NodeList) {
		TargetPosition[node] = node->position;
	}

	if (newNode != nullptr) {
		if (newNode->parent != nullptr) {
			if (newNode->parent->left == newNode) newNode->parent->left = nullptr;
			else newNode->parent->right = nullptr;
		}
		else {
			tree->Root = nullptr;
		}
		tree->NodeList.pop_back();
		delete newNode;
		newNode = nullptr;
	}
	for (Node* node : tree->NodeList) {
		node->position = StartPosition[node];
	}
	tree->DeleteLeafNode(tree->Root, InsertValue);
}

void InsertAnimationAVLTree::DeleteAnimation(int value) {
	this->InsertValue = value;
	this->Indexpath = 0;
	this->AnimationStep = 1;
	this->AnimationTime = 0.0f;
	this->duration = 1.0f;
	this->StartPosition.clear();
	this->TargetPosition.clear();
	this->path.clear();
	this->newNode = nullptr;
	this->exist = false;
	this->NodeDelete = nullptr;
	this->NodeReplace = nullptr;
	this->GhostNode = nullptr;
	this->GhostStartPosition = { 0,0 };

	Node* curr = tree->Root;
	while (curr != nullptr) {
		path.push_back(curr);
		if (value < curr->val) curr = curr->left;
		else if (value > curr->val) curr = curr->right;
		else {
			NodeDelete = curr;
			break;
		}
	}

	if (NodeDelete == nullptr) return;

	if (NodeDelete->left == nullptr && NodeDelete->right == nullptr) NodeReplace = nullptr; 
	else if (NodeDelete->left == nullptr) NodeReplace = NodeDelete->right; 
	else if (NodeDelete->right == nullptr) NodeReplace = NodeDelete->left; 
	else {
		NodeReplace = NodeDelete->left;
		while (NodeReplace->right != nullptr) {
			NodeReplace = NodeReplace->right;
		}
	}

	if (NodeReplace != nullptr) {
		GhostNode = new Node(NodeReplace->val, 0, 0, 0, -1, false, NodeReplace->position, nullptr, nullptr, nullptr, false, false, false, false);
		GhostStartPosition = GhostNode->position;
	}
}

void InsertAnimationAVLTree::UpdateStepDelete() {
	if (NodeDelete == nullptr) return;

	AnimationTime += GetFrameTime();
	float t = AnimationTime / duration;

	switch (AnimationStep) {
	case 1:
		if (Indexpath < path.size()) {
			if (t >= 1.0) {
				path[Indexpath]->isNodeHighLighted = true;
				AnimationTime = 0.0f;
				Indexpath++;
			}
		}
		else if (t >= 1.0f) {
			AnimationStep = 2;
			AnimationTime = 0.0f;
		}
		break;
	case 2:
		if ((NodeReplace != nullptr && GhostNode != nullptr)) {
			if (t < 1.0f) {
				GhostNode->position.x = GhostStartPosition.x + (NodeDelete->position.x - GhostStartPosition.x)* t;
				GhostNode->position.y = GhostStartPosition.y + (NodeDelete->position.y - GhostStartPosition.y) * t;
				DrawCircle(GhostNode->position.x, GhostNode->position.y, 30, BLUE);
				DrawText(TextFormat("%d", GhostNode->val), GhostNode->position.x, GhostNode->position.y, 20, WHITE);
			}
			else {
				NodeDelete->val = NodeReplace->val;
				NodeDelete->isNodeInserted = true;
				delete GhostNode;
				GhostNode = nullptr;
				AnimationStep = 3;
				AnimationTime = 0.0f;
			}
		}
		else {
			AnimationStep = 3;
			AnimationTime = 0.0f;
		}
		break;
	case 3 :
		StartPosition.clear();
		TargetPosition.clear();

		for (Node* node : tree->NodeList) {
			StartPosition[node] = node->position;
		}

		tree->DeleteNode(tree->Root, NodeDelete->val);
		tree->UpdateHeightAndBalanceFactor(tree->Root);
		tree->balanceTree();

		for (Node* node : tree->NodeList) {
			TargetPosition[node] = node->position;
		}

		for (Node* node : tree->NodeList) {
			node->position = StartPosition[node];
		}
		AnimationStep = 4;
		break;
	case 4 :
		if (t < 1.0f) {
			for (Node* node : tree->NodeList) {
				node->position.x = StartPosition[node].x + (TargetPosition[node].x - StartPosition[node].x) * t;
				node->position.y = StartPosition[node].y + (TargetPosition[node].y - StartPosition[node].y) * t;
			}
		}
		else {
			for (Node* node : tree->NodeList) {
				node->position.x = TargetPosition[node].x;
				node->position.y = TargetPosition[node].y;
			}
			AnimationStep = 5;
			AnimationTime = 0.0f;
		}
		break;
	case 5 :
		NodeRotate = tree->GetNodeRotate();
		if (NodeRotate == nullptr) {
			AnimationStep = 7;
			AnimationTime = 0.0f;
		}
		else{
			RotateStartPosition.clear();
			RotateTargetPosition.clear();
			for (Node* node : tree->NodeList) {
				RotateStartPosition[node] = node->position;
			}
			if (NodeRotate->balanceFactor > 1 && (NodeRotate->left && NodeRotate->left->balanceFactor < 0) || NodeRotate->balanceFactor < -1 && (NodeRotate->right && NodeRotate->right->balanceFactor > 0)) {
				tree->RebalanceChild(tree->Root, NodeRotate);
				tree->UpdateHeightAndBalanceFactor(tree->Root);
				RotateSecond = true;
				tree->balanceTree();

				for (Node* node : tree->NodeList) {
					RotateTargetPosition[node] = node->position;
					node->position = RotateStartPosition[node];
				}
				AnimationStep = 6;
				AnimationTime = 0.0f;
			}
			else {
				tree->RebalanceParent(tree->Root, NodeRotate);
				tree->UpdateHeightAndBalanceFactor(tree->Root);
				tree->balanceTree();
				for (Node* node : tree->NodeList) {
					RotateTargetPosition[node] = node->position;
					node->position = RotateStartPosition[node];
				}
				AnimationStep = 6;
				AnimationTime = 0.0f;
			}
		}
		break;
	case 6 :
		if (t < 1.0f) {
			for (Node* node : tree->NodeList) {
				node->position.x = RotateStartPosition[node].x + (RotateTargetPosition[node].x - RotateStartPosition[node].x) * t;
				node->position.y = RotateStartPosition[node].y + (RotateTargetPosition[node].y - RotateStartPosition[node].y) * t;
			}
		}
		else {
			for (Node* node : tree->NodeList) {
				node->position.x = RotateTargetPosition[node].x;
				node->position.y = RotateTargetPosition[node].y;
			}
			if (RotateSecond == true) {
				AnimationStep = 8;
				AnimationTime = 0.0f;
			}
			else if (NodeRotate != nullptr) {
				AnimationStep = 5;
				AnimationTime = 0.0f;
			}
			else {
				AnimationStep = 7;
				AnimationTime = 0.0f;
			}
		}
		break;
	case 7 :
		if (t >= 1.0f) {
			for (Node* node : tree->NodeList) {
				node->isNodeInserted = false;
				node->isNodeHighLighted = false;
			}
			path.clear();
			AnimationStep = 0;
			AnimationTime = 0.0f;
		}
		break;
	case 8 :
		RotateSecond = false;
		RotateStartPosition.clear();

		for (Node* node : tree->NodeList) {
			RotateStartPosition[node] = node->position;
		}

		tree->RebalanceParent(tree->Root, NodeRotate);
		tree->UpdateHeightAndBalanceFactor(tree->Root);
		tree->balanceTree();

		RotateTargetPosition.clear();

		for (Node* node : tree->NodeList) {
			RotateTargetPosition[node] = node->position;
			node->position = RotateStartPosition[node];
		}

		NodeRotate = tree->GetNodeRotate();

		AnimationStep = 6;
		AnimationTime = 0.0f;

		break;
	}
}
void InsertAnimationAVLTree::UpdateStep() {
	if (exist == true) return;
	AnimationTime += GetFrameTime();
	float t = AnimationTime / duration;

	switch (AnimationStep) {
	case 1:
		if (Indexpath < path.size()) {
			if (t >= 1.0) {
				path[Indexpath]->isNodeHighLighted = true;
				AnimationTime = 0.0f;
				Indexpath++;
			}
		}
		else if (t >= 1.0f) {
			AnimationStep = 2;
			AnimationTime = 0.0f;
		}
		break;
	case 2:
		if (t < 1.0f) {
			for (Node* node : tree->NodeList) {
				node->position.x = StartPosition[node].x + (TargetPosition[node].x - StartPosition[node].x) * t;
				node->position.y = StartPosition[node].y + (TargetPosition[node].y - StartPosition[node].y) * t;
			}
		}
		else {
			for (Node* node : tree->NodeList) {
				node->position = TargetPosition[node];
			}
			AnimationStep = 3;
			AnimationTime = 0.0f;
		}
		break;
	case 3:
		tree->Insert(tree->Root, InsertValue, tree->NodeList, false);
		tree->UpdateHeightAndBalanceFactor(tree->Root);
		for (Node* node : tree->NodeList) {
			if (node->val == InsertValue) {
				newNode = node;
				break;
			}
		}
		if (newNode != nullptr) {
			newNode->isNodeInserted = true;
			if (t >= 1.0f) {
				AnimationStep = 4;
				AnimationTime = 0.0f;
			}
		}
		break;
	case 4:
		RotateStartPosition.clear();
		RotateTargetPosition.clear();
		NodeRotate = tree->GetNodeRotate();
		if (NodeRotate == nullptr) {
			AnimationStep = 6;
			break;
		}
		else {
			for (Node* node : tree->NodeList) {
				RotateStartPosition[node] = node->position;
			}
			if (NodeRotate->balanceFactor > 1 && (NodeRotate->left && NodeRotate->left->balanceFactor < 0) || NodeRotate->balanceFactor < -1 && (NodeRotate->right && NodeRotate->right->balanceFactor > 0)) {
				tree->RebalanceChild(tree->Root, NodeRotate);
				tree->UpdateHeightAndBalanceFactor(tree->Root);
				RotateSecond = true;
				tree->balanceTree();

				for (Node* node : tree->NodeList) {
					RotateTargetPosition[node] = node->position;
					node->position = RotateStartPosition[node];
				}
				AnimationStep = 5;
				AnimationTime = 0.0f;
			}
			else {
				tree->RebalanceParent(tree->Root, NodeRotate);
				tree->UpdateHeightAndBalanceFactor(tree->Root);
				tree->balanceTree();
				for (Node* node : tree->NodeList) {
					RotateTargetPosition[node] = node->position;
					node->position = RotateStartPosition[node];
				}
				AnimationStep = 5;
				AnimationTime = 0.0f;
			}
		}
		break;
	case 5:
		cout << "Case 5" << endl;
		if (t < 1.0f) {
			for (Node* node : tree->NodeList) {
				node->position.x = RotateStartPosition[node].x + (RotateTargetPosition[node].x - RotateStartPosition[node].x) * t;
				node->position.y = RotateStartPosition[node].y + (RotateTargetPosition[node].y - RotateStartPosition[node].y) * t;
			}
		}
		else {
			for (Node* node : tree->NodeList) {
				node->position = RotateTargetPosition[node];
			}
			if (RotateSecond == true) {
				RotateSecond = false;
				AnimationStep = 7;
				AnimationTime = 0.0f;
			}
			else {
				AnimationStep = 6;
				AnimationTime = 0.0f;
			}
		}
		break;
	case 6:
		if (t >= 1.0f) {
			for (Node* node : tree->NodeList) {
				node->isNodeHighLighted = false;
				node->isNodeInserted = false;
				node->isLeftEdgeHightLigted = false;
				node->isRightEdgeHightLighted = false;
			}
			this->path.clear();
			AnimationStep = 0;
			AnimationTime = 0.0f;
			RotateStartPosition.clear();
			RotateTargetPosition.clear();
		}
		break;
	case 7:
		RotateSecond = false;
		RotateStartPosition.clear();
		for (Node* node : tree->NodeList) {
			RotateStartPosition[node] = node->position;
		}
		tree->RebalanceParent(tree->Root, NodeRotate);
		tree->UpdateHeightAndBalanceFactor(tree->Root);
		tree->balanceTree();
		RotateTargetPosition.clear();
		for (Node* node : tree->NodeList) {
			RotateTargetPosition[node] = node->position;
			node->position = RotateStartPosition[node];
		}
		AnimationStep = 5;
		AnimationTime = 0.0f;
		break;
	default:
		break;
	}
}

bool InsertAnimationAVLTree::isFinished() const {
	return AnimationStep == 0;
}

void InsertAnimationAVLTree::SetTree(AVLTree* root) {
	this->tree = root;
}

