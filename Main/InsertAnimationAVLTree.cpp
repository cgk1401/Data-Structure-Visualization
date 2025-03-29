#include "InsertAnimationAVLTree.hpp"

InsertAnimationAVLTree::InsertAnimationAVLTree(AVLTree* root) {
	this->tree = root;
	this->AnimationStep = 0;
	this->AnimationTime = 0.0f;
	this->duration = 0.5f;
	this->newNode = nullptr;
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

	for (Node* node : tree->NodeList) {
		StartPosition[node] = node->position;
	}

	Node* curr = tree->Root;
	while (curr != nullptr) {
		path.push_back(curr);
		if (value < curr->val) curr = curr->left;
		else if (value > curr->val) curr = curr->right;
		else break;
	}

	tree->Insert(tree->Root, value, tree->NodeList, false);
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
}


void InsertAnimationAVLTree::SetTree(AVLTree* root) {
	this->tree = root;
}


void InsertAnimationAVLTree::UpdateStep() {
	AnimationTime += GetFrameTime(); 
	float t = AnimationTime / duration; 

	switch (AnimationStep) {
	case 1 :


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
	case 3 :
		tree->Insert(tree->Root, InsertValue, tree->NodeList, false);
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
	case 4 :
		if (t >= 1.0f){
			for (Node* node : tree->NodeList) {
				node->isNodeHighLighted = false;
				node->isNodeInserted = false;
				node->isLeftEdgeHightLigted = false;
				node->isRightEdgeHightLighted = false;
			}
			AnimationStep = 0;
			AnimationTime = 0.0f;
		}
		break;
	default:
		break;
	}
}

bool InsertAnimationAVLTree:: isFinished() const {
	return AnimationStep == 0;
}