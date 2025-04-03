#include "InsertAnimationAVLTree.hpp"

InsertAnimationAVLTree::InsertAnimationAVLTree(AVLTree* root) {
	this->tree = root;
	this->AnimationStep = 0;
	this->AnimationTime = 0.0f;
	this->duration = 0.5f;
	this->newNode = nullptr;
	this->NodeRotate = nullptr;
	this->Indexpath = 0;
	this->RotateSecond = false;
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

	tree->DrawLevelOrder(tree->Root);
}


void InsertAnimationAVLTree::SetTree(AVLTree* root) {
	this->tree = root;
}

void InsertAnimationAVLTree::UpdateStep() {
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
			AnimationStep = 0;
			AnimationTime = 0.0f;
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

//void InsertAnimationAVLTree::NextStep() {
//	if (AnimationStep == 0){
//		if (AnimationStep == 0) {
//			StartInsertAnimation(InsertValue);
//		}
//		else if (AnimationStep < 6) {
//			AnimationTime = duration;  
//		}
//	}
//
//}

