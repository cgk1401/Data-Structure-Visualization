#include "InsertAnimationAVLTree.hpp"

void InsertAnimationAVLTree::HightLightPath() {
	if (this->frameCounter < this->delayFrames) {
		this->frameCounter++;
		return;
	}
	this->frameCounter = 0;

	if (idexpath < path.size()) {
		path[idexpath].first->isNodeHighLighted = true;
		idexpath++;
	}
	else animationstep = 2;
}

void InsertAnimationAVLTree::AnimationInsert() {
	if (this->frameCounter < this->delayFrames) {
		this->frameCounter++;
		return;
	}
	this->frameCounter = 0;
	tree->Insert(tree->Root, insertvalue, tree->NodeList);
	for (Node* node : tree->NodeList) {
		if (node->val == insertvalue) {
			node->isNodeInserted = true;
		}
	}
	animationstep = 3;
}

void InsertAnimationAVLTree::Finalize() {
	if (this->frameCounter < this->delayFrames) {
		this->frameCounter++;
		return;
	}
	this->frameCounter = 0;
	for (Node* node : tree->NodeList) {
		node->isNodeHighLighted = false;
		node->isNodeInserted = false;
		node->isLeftEdgeHightLigted = false;
		node->isRightEdgeHightLighted = false;
	}
	animationstep = 0;
}

InsertAnimationAVLTree::InsertAnimationAVLTree(AVLTree* root) {
	this->tree = root;
	this->animationstep = 0;
	this->insertvalue = -1;
	this->idexpath = 0;
	this->frameCounter = 0;
	this->delayFrames = 30; 
}

void InsertAnimationAVLTree::StartInsert(int value) {
	this->insertvalue = value;
	this->idexpath = 0;
	this->animationstep = 1;

	this->path.clear();

	Node* cur = tree->Root;
	while (cur != nullptr) {
		bool isleft = (this->insertvalue < cur->val);
		path.push_back({ cur, isleft });
		if (this->insertvalue < cur->val) cur = cur->left;
		else if (this->insertvalue > cur->val) cur = cur->right;
		else break;
	}

}

void InsertAnimationAVLTree::UpdateStep() {

	if (this->animationstep == 1) HightLightPath();
	else if (this->animationstep == 2) AnimationInsert();
	else if (this->animationstep == 3) Finalize(); // resert sau khi xong
}

bool InsertAnimationAVLTree::isFinished() const {
	return animationstep == 0;
}
