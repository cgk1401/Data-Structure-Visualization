#ifndef AVLTree_HPP
#define AVLTree_HPP

#include "Node.hpp"
#include "Config.hpp"
#include <random>
#include <queue>

class AVLTree {
public:
	AVLTree();
	Node* Root;
	vector <Node*> NodeList;
	float DistanceHorizontal;
	float DistanceVertical;
	
	void Insert(Node*& root, int data, vector <Node*> &NodeList);
	Node* InsertHelper(Node*& root, int data, Node* parnent, vector <Node*> &NodeList);
	int GetHeight(Node* node);
	Node* RotationLeft(Node*& root);
	Node* RotationRight(Node*& root);
	void Random();
	void Clear(Node* &root);

	void MoveTree(Node* root, bool isLeft);
	void balanceTree();
	void DrawTreeHelper(Node* root);
	void DrawTree();
	

};

#endif // !AVLTree_HPP

