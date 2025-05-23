﻿#ifndef ANIMATIONAVLTREE_HPP
#define ANIMATIONAVLTREE_HPP

#include "AVLTree.hpp"
#include "ExplanationCode.hpp"
#include "Pseudocode.hpp"
#include <map>

class AnimationAVLTree {
private:
	AVLTree* tree;

	int InsertValue;
	int Indexpath;

	int AnimationStep;
	float AnimationTime;
	float duration;
	int ReverseIndexpath;
	bool RotateSecond;
	bool isDuplicate = false;

	Node* NodeRotate;
	Node* NodeDelete;
	Node* NodeReplace;
	Node* GhostNode;
	Node* NodeSearch;
	Node* newNode;

	vector <Node*> path;
	vector <Node*> reversepath;

	map <Node*, Vector2> StartPosition;
	map <Node*, Vector2> TargetPosition;

	Vector2 GhostStartPosition;
	map <Node*, Vector2> RotateStartPosition;
	map <Node*, Vector2> RotateTargetPosition;
public:
	AnimationAVLTree(AVLTree* root);
	ExplanationCode explanationcode;
	Pseudocode pseudocode;
	

	void StartInsertAnimation(int value);
	void StartDeleteAnimation(int value);
	void StartSearchAnimation(int value);

	void UpdateStepInsert();
	void UpdateStepDelete();
	void UpdateStepSearch(int value);
		
	void SetTree(AVLTree* root);
	void SetTime(float value) { this->duration = value; }
	bool isFinished() const;
};

#endif // !ANIMATIONAVLTREE_HPP
