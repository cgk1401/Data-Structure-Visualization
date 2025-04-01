#ifndef INSERTANIMATIONAVLTREE_HPP
#define INSERTANIMATIONAVLTREE_HPP

#include "AVLTree.hpp"
#include <map>

class InsertAnimationAVLTree {
private:
	AVLTree* tree;

	int InsertValue;
	int Indexpath;

	int AnimationStep;

	vector <Node*> path;

	float AnimationTime;
	float duration; // thời gian để hoàn thành mỗi bước animation

	Node* newNode;
	bool RotateSecond;
	map <Node*, Vector2> StartPosition;
	map <Node*, Vector2> TargetPosition;

	Node* NodeRotate;
	map <Node*, Vector2> RotateStartPosition;
	map <Node*, Vector2> RotateTargetPosition;


public:
	InsertAnimationAVLTree(AVLTree* root);

	void StartInsertAnimation(int value);

	void UpdateStep();

	void SetTree(AVLTree* root);
	bool isFinished() const;

};

#endif // !INSERTANIMATIONAVLTREE_HPP
