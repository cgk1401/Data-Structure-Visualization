#include "InsertAnimationAVLTree.hpp"

InsertAnimationAVLTree::InsertAnimationAVLTree(AVLTree* root) {
	this->tree = root;
	this->InsertValue = -1;
	this->Indexpath = 0;
	this->AnimationStep = 0;
	this->AnimationTime = 0.0f;
	this->duration = 0.5f;
	this->ReverseIndexpath = 0;
	this->RotateSecond = false;
	this->path.clear();
	this->reversepath.clear();
	this->NodeSearch = nullptr;
	this->newNode = nullptr;
	this->NodeRotate = nullptr;
	this->NodeDelete = nullptr;
	this->NodeReplace = nullptr;
	this->GhostNode = nullptr;
	this->GhostStartPosition = {0,0};
	this->RotateStartPosition.clear();
	this->RotateTargetPosition.clear();
}

void InsertAnimationAVLTree::StartInsertAnimation(int value) {
	this->InsertValue = value;
	this->Indexpath = 0;
	this->ReverseIndexpath = 0;
	this->AnimationStep = 1;
	this->AnimationTime = 0.0f;
	this->duration = 1.0f;
	this->isDuplicate = false;
	this->newNode = nullptr;
	this->NodeReplace = nullptr;
	this->NodeSearch = nullptr;
	this->reversepath.clear();
	this->StartPosition.clear();
	this->TargetPosition.clear();
	this->path.clear();
	for (Node* node : tree->NodeList) {
		StartPosition[node] = node->position;
	}

	Node* curr = tree->Root;
	while (curr != nullptr) {
		path.push_back(curr);
		if (value < curr->val) curr = curr->left;
		else if (value > curr->val) curr = curr->right;
		else if (value == curr->val) {
			NodeSearch = curr;
			isDuplicate = true;
			return;
		}
		else break;
	}
	reversepath = path;
	reverse(reversepath.begin(), reversepath.end());
	ReverseIndexpath = 0;
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

void InsertAnimationAVLTree::StartDeleteAnimation(int value) {
	this->InsertValue = value;
	this->Indexpath = 0;
	this->AnimationStep = 1;
	this->AnimationTime = 0.0f;
	this->duration = 0.5f;
	this->ReverseIndexpath = 0;
	this->newNode = nullptr;
	this->NodeDelete = nullptr;
	this->NodeReplace = nullptr;
	this->GhostNode = nullptr;
	this->StartPosition.clear();
	this->TargetPosition.clear();
	this->path.clear();
	this->reversepath.clear();
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

void InsertAnimationAVLTree::StartSearchAnimation(int value) {
	AnimationTime = 0.0f;
	duration = 0.5f;
	Node* curr = tree->Root;
	while (curr != nullptr) {
		if (curr->val < value) curr = curr->right;
		else if (curr->val > value) curr = curr->left;
		else if (curr->val == value) {
			NodeSearch = curr;
			break;
		}
	}
}

void InsertAnimationAVLTree::UpdateStepInsert() {
	if (NodeSearch != nullptr && isDuplicate == true) {
		AnimationTime += GetFrameTime();
		float t = AnimationTime / duration;
		explanationcode.Setstringexplancode("Node already exists, highlight existing node.");
		if (t >= 1.0) {
			NodeSearch = nullptr;
			isDuplicate = false;
			AnimationStep = 0;
			AnimationTime = 0.0f;
			return;
		}

		float radius = 30.0f + (10.0f * sin(t * PI));
		DrawCircle(NodeSearch->position.x, NodeSearch->position.y, radius, YELLOW);
		int fontSize = 20;
		string text = to_string(NodeSearch->val);
		int textWidth = MeasureText(text.c_str(), fontSize);
		DrawText(text.c_str(), NodeSearch->position.x - textWidth / 2, NodeSearch->position.y - fontSize / 2, fontSize, WHITE);
		return;
	}

	AnimationTime += GetFrameTime();
	float t = AnimationTime / duration;

	switch (AnimationStep) {
	case 1:
		explanationcode.Setstringexplancode("Traversing the path from root to the position for insertion.");
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
		explanationcode.Setstringexplancode("Expanding the tree to create spacing for the new node.");
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
		explanationcode.Setstringexplancode("Inserting new node: " + to_string(InsertValue));
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
				AnimationStep = 8;
				AnimationTime = 0.0f;
			}
		}
		break;
	case 4:
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
			explanationcode.Setstringexplancode("Rotating child before rotating parent.");
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
			explanationcode.Setstringexplancode("Rotating Parent.");
			AnimationStep = 5;
			AnimationTime = 0.0f;
		}
		break;
	case 5:
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
				AnimationStep = 8;
				AnimationTime = 0.0f;
			}
		}
		break;
	case 6:
		explanationcode.Setstringexplancode("Reset Status.");
		if (t >= 1.0f) {
			for (Node* node : tree->NodeList) {
				node->isNodeHighLighted = false;
				node->isNodeInserted = false;
				node->isLeftEdgeHightLigted = false;
				node->isRightEdgeHightLighted = false;
			}
			AnimationStep = 0;
			AnimationTime = 0.0f;
			RotateStartPosition.clear();
			RotateTargetPosition.clear();
		}
		break;
	case 7:
		explanationcode.Setstringexplancode("Rotating Parent.");
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
	case 8:
		explanationcode.Setstringexplancode("Highlight Reverse path.");
		if (ReverseIndexpath < reversepath.size()) {
			if (t >= 1.0f) {
				reversepath[ReverseIndexpath]->isNodeHighLighted = false;
				if (abs(reversepath[ReverseIndexpath]->balanceFactor) > 1) {
					NodeRotate = reversepath[ReverseIndexpath];
					ReverseIndexpath++;
					AnimationStep = 4;
					AnimationTime = 0.0f;
				}
				else {
					ReverseIndexpath++;
					AnimationTime = 0.0f;
				}
			}
		}
		else {
			AnimationStep = 6;
			AnimationTime = 0.0f;
		}
		break;
	default:
		break;
	}
}

void InsertAnimationAVLTree::UpdateStepDelete() {
	if (NodeDelete == nullptr) return;

	AnimationTime += GetFrameTime();
	float t = AnimationTime / duration;

	switch (AnimationStep) {
	case 1:
		explanationcode.Setstringexplancode("Traversing the path from root to the position for deletion.");
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
		explanationcode.Setstringexplancode("Replacing Node.");
		for (auto it : reversepath) cout << it << " ";
 		if ((NodeReplace != nullptr && GhostNode != nullptr)) {
			if (t < 1.0f) {
				GhostNode->position.x = GhostStartPosition.x + (NodeDelete->position.x - GhostStartPosition.x)* t;
				GhostNode->position.y = GhostStartPosition.y + (NodeDelete->position.y - GhostStartPosition.y) * t;
				int fontSize = 20;
				string text = to_string(GhostNode->val);
				if (text.size() > 2) fontSize = 19;
				if (text.size() > 4) fontSize = 16;
				int textWidth = MeasureText(text.c_str(), fontSize);
				int textHeight = fontSize;
				DrawCircle(GhostNode->position.x, GhostNode->position.y, 30, BLUE);
				DrawText(text.c_str(), GhostNode->position.x - textWidth / 2, GhostNode->position.y - textHeight / 2, fontSize, WHITE);
			}
			else {
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
	case 3:
		{
		StartPosition.clear();
		TargetPosition.clear();

		int deletevalue = -1;
		if (NodeReplace != nullptr) deletevalue = NodeReplace->val;
		if (NodeReplace == nullptr) {
			if (NodeDelete != nullptr && NodeDelete->parent != nullptr) deletevalue = NodeDelete->parent->val;
			else if (NodeDelete != nullptr && NodeDelete->parent != nullptr) deletevalue = -1;
		}
		
		for (Node* node : tree->NodeList) {
			StartPosition[node] = node->position;
		}

		tree->DeleteNode(tree->Root, NodeDelete->val);
		tree->UpdateHeightAndBalanceFactor(tree->Root);
		tree->balanceTree();
		reversepath.clear();
		if (deletevalue != -1) {
			Node* curr = tree->Root;
			while (curr != nullptr) {
				reversepath.push_back(curr);
				if (curr->val > deletevalue) curr = curr->left;
				else if (curr->val < deletevalue) curr = curr->right;
				else if (curr->val == deletevalue) {
					break;
				}
			}
		}
		reverse(reversepath.begin(), reversepath.end());
		ReverseIndexpath = 0;
		for (auto it : reversepath) cout << it->val << " ";

		for (Node* node : tree->NodeList) {
			TargetPosition[node] = node->position;
		}
		for (Node* node : tree->NodeList) {
			node->position = StartPosition[node];
		}
		AnimationStep = 4;
		AnimationTime = 0.0f;
		break;
	}
	case 4 :
		explanationcode.Setstringexplancode("Expanding the tree after deleting the node.");
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
			AnimationStep = 9;
			AnimationTime = 0.0f;
		}
		break;
	case 5 :
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
			explanationcode.Setstringexplancode("Rotating child before roatating parent.");
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
			explanationcode.Setstringexplancode("Rotating parent.");
			AnimationStep = 6;
			AnimationTime = 0.0f;
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
			else {
				AnimationStep = 9;
				AnimationTime = 0.0f;
			}
		}
		break;
	case 7 :
		explanationcode.Setstringexplancode("Reset status.");
		if (t >= 1.0f) {
			for (Node* node : tree->NodeList) {
				node->isNodeInserted = false;
				node->isNodeHighLighted = false;
			}
			this->path.clear();
			AnimationStep = 0;
			AnimationTime = 0.0f;
			RotateStartPosition.clear();
			RotateTargetPosition.clear();
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
		explanationcode.Setstringexplancode("Rotating parent.");
		AnimationStep = 6;
		AnimationTime = 0.0f;
		break;
	case 9:
		explanationcode.Setstringexplancode("Highlight reverse path.");
		if (ReverseIndexpath < reversepath.size()) {
			if (t >= 1.0f) {
				if (reversepath[ReverseIndexpath] != nullptr) {
					reversepath[ReverseIndexpath]->isNodeHighLighted = false;
					if (abs(reversepath[ReverseIndexpath]->balanceFactor) > 1) {
						NodeRotate = reversepath[ReverseIndexpath];
						ReverseIndexpath++;
						AnimationStep = 5;
						AnimationTime = 0.0f;
					}
					else {
						ReverseIndexpath++;
						AnimationTime = 0.0f;
					}
				}
				else {
					ReverseIndexpath++;
					AnimationTime = 0.0f;
				}
			}
		}
		else {
			NodeRotate = tree->GetNodeRotate();
			if (NodeRotate != nullptr) {
				AnimationStep = 5;
				AnimationTime = 0.0f;
			}
			else {
				AnimationStep = 7;
				AnimationTime = 0.0f;
			}
		}
		break;
	default :
		break;
	}
}

void InsertAnimationAVLTree::UpdateStepSearch(int value) {
	if (NodeSearch == nullptr) return;
	AnimationTime += GetFrameTime();
	float t = AnimationTime / duration;

	if (t >= 1.0) {
		NodeSearch = nullptr;
		AnimationTime = 0.0f;
		t = 1.0f;
		return;
	}
	float radius = 30.0f + (10.0f * sin(t * PI)); 

	DrawCircle(NodeSearch->position.x, NodeSearch->position.y, radius, YELLOW);

	int fontSize = 20;
	string text = to_string(NodeSearch->val);
	int textWidth = MeasureText(text.c_str(), fontSize);
	DrawText(text.c_str(), NodeSearch->position.x - textWidth / 2, NodeSearch->position.y - fontSize / 2, fontSize, WHITE);
}

bool InsertAnimationAVLTree::isFinished() const { return AnimationStep == 0;}

void InsertAnimationAVLTree::SetTree(AVLTree* root) {this->tree = root;}
