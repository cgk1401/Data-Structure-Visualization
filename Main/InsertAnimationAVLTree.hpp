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
	vector <Node*> reversepath;
	int ReverseIndexpath;

	float AnimationTime;
	float duration;

	Node* newNode;
	bool exist = false;
	bool RotateSecond;
	map <Node*, Vector2> StartPosition;
	map <Node*, Vector2> TargetPosition;

	Node* NodeRotate;
	Node* NodeDelete;
	Node* NodeReplace;
	Node* GhostNode;
	Vector2 GhostStartPosition;
	map <Node*, Vector2> RotateStartPosition;
	map <Node*, Vector2> RotateTargetPosition;

public:
	InsertAnimationAVLTree(AVLTree* root);

	void StartInsertAnimation(int value);
	void DeleteAnimation(int value);

	void UpdateStep();
	void UpdateStepDelete();
		
	void SetTree(AVLTree* root);
	bool isFinished() const;

};

#endif // !INSERTANIMATIONAVLTREE_HPP
