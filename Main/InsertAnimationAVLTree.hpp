#ifndef  INSERTANIMATIONAVLTREE_HPP
#define INSERTANIMATIONAVLTREE_HPP

#include "AVLTree.hpp"

class InsertAnimationAVLTree {
private :
	AVLTree* tree; 

	int animationstep; 
	int insertvalue; 
	Node* Noderotate;

	vector <pair <Node*, bool>> path; 
	int idexpath;

	
	int frameCounter = 0; 
	int delayFrames = 30; 

public :
	
	InsertAnimationAVLTree(AVLTree* root);

	void StartInsert(int value); 
	void UpdateStep(); 
	bool isFinished() const ;
	
	void SetTree(AVLTree* tree);

};


#endif // ! INSERTANIMATIONAVLTREE_HPP

