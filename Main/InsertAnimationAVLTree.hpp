#ifndef  INSERTANIMATIONAVLTREE_HPP
#define INSERTANIMATIONAVLTREE_HPP

#include "AVLTree.hpp"

class InsertAnimationAVLTree {
private :
	AVLTree* tree; // gốc cây để xử lý

	int animationstep; // các bước hiện độ họa trong quá trình insert
	int insertvalue; // giá trị muốn insert

	vector <pair <Node*, bool>> path; // đường đi từ gốc đến vị trí insert
	int idexpath;

	void HightLightPath(); // hightlight đường đi từ gốc đến vị trí insert , step 1
	void AnimationInsert(); // hiệu ứng khi insert, step 2

	void Finalize(); // kết thúc quá trình insert, step 3
	// step 0 kết thúc animation quá trình insert

	int frameCounter = 0; // đếm số frame đã qua
	int delayFrames = 30; // chạy đủ 30 frame mới thực hiện tiế

public :
	
	InsertAnimationAVLTree(AVLTree* root);

	void StartInsert(int value); // bắt đầu hiệu ứng insert với giá trị cần insert là value;
	void UpdateStep(); // điều chỉnh các bước trong quá trình insert;
	bool isFinished() const ;// kiểm tra quá trình insert đã kết thúc chưa

};


#endif // ! INSERTANIMATIONAVLTREE_HPP

