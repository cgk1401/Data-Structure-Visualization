#include <iostream>
#include "Config.hpp"
using namespace std;

float ScreenWidth = 2000;
float ScreenHeight = 900;
float SecondMenuWidth = 500;//ScreenWidth * float(1) / 4;
float SecondMenuHeight = 450;

Color ColorPalette[4][6] = {
	{//#1 Monochrome Magic
		{ 255, 255, 255, 255},
		{ 215, 215, 215, 255 },
		{ 176, 176, 176, 176 },
		{ 125, 125, 125, 255 },
		{ 74, 74, 74, 255 },
		{ 220, 190, 140, 255 }
	},
	{//#2  Cool Grays
		{ 240, 244, 248, 255 },
		{ 176, 190, 197, 255 },
		{ 120, 144, 156, 255 },
		{ 84, 110, 122, 255 },
		{ 38, 50, 56, 255 },
		{ 112, 150, 209, 255 }
	},
	{//#3 Soft Blues
		{ 25, 55, 92, 255 },
		{ 187, 222, 251, 255 },
		{ 144, 192, 249, 255 },
		{ 100, 181, 246, 255 },
		{ 226, 242, 253, 255 },
		{ 66, 165, 245, 255 }
	},
	{//#4 Warm Pastels
		{ 66, 33, 11, 255 },
		{ 255, 224, 178, 255 },
		{ 255, 204, 128, 255 },
		{ 255, 183, 77, 255 },
		{ 230, 220, 200, 255 },
		{ 255, 167, 38, 255 }
	}

};

Color C[6];
/*
C[0] : Text
C[1] : Node, Second menu
C[2] : Button
C[3] : Edge
C[4] : Background
C[5] : Active node
*/