#ifndef AVLTree_HPP
#define AVLTree_HPP

#include "Node.hpp"
#include "Config.hpp"
#include <random>
#include <queue>
#include <chrono>
#include <thread>

class AVLTree {
public :

	AVLTree();
	Node* Root;
	vector <Node*> NodeList;

	float DistanceHorizontal;
	float DistanceVertical;

public :
	void MoveTree(Node* root, bool isLeft);
	void balanceTree();
public :
	void DrawTreeHelper(Node* root);
	void DrawTree();
	
public:
	void Insert(Node*& root, int data, vector <Node*> &NodeList);
	Node* InsertHelper(Node*& root, int data, Node* parnent, vector <Node*> &NodeList);
	int GetHeight(Node* node);
	Node* RotationLeft(Node*& root);
	Node* RotationRight(Node*& root);

	void Random();
	void Clear(Node* &root);

	

};

#endif // !AVLTree_HPP

