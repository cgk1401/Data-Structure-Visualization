#include "InsertAnimationAVLTree.hpp"


InsertAnimationAVLTree::InsertAnimationAVLTree(AVLTree* root) {
	this->tree = root;
	this->animationstep = 0;
	this->insertvalue = -1;
	this->idexpath = 0;
	this->frameCounter = 0;
	this->delayFrames = 30;
	this->Noderotate = nullptr;
}

void InsertAnimationAVLTree::UpdateStep() {
	switch (animationstep) {
	case 1 :
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
		break;
	case 2 :
		if (this->frameCounter < this->delayFrames) {
			this->frameCounter++;
			return;
		}
		this->frameCounter = 0;
		tree->Insert(tree->Root, insertvalue, tree->NodeList, false);
		for (Node* node : tree->NodeList) {
			if (node->val == insertvalue) {
				node->isNodeInserted = true;
			}
		}
		animationstep = 3; 
		break;
	case 3 :
		if (this->frameCounter < this->delayFrames) {
			this->frameCounter++;
			return;
		}
		this->frameCounter = 0;

		animationstep = 4; 
		break;
	case 4 :

		tree->balanceTree();
		animationstep = 5;
		break;

	case 5 :
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
		break;
	default:
		break;
	}
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



bool InsertAnimationAVLTree::isFinished() const {
	return animationstep == 0;
}

void InsertAnimationAVLTree::SetTree(AVLTree* tree) {
	this->tree = tree;
}
