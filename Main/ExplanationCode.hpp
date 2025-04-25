#ifndef EXPLANATIONCODE_HPP
#define EXPLANATIONCODE_HPP

#include <iostream>
#include <raylib.h>
#include <sstream>
#include <vector>
#include "Config.hpp"
using namespace std;

class ExplanationCode {
public:
    string text = "";
    vector<string> lines_insert = {
        "Chọn thao tác để bắt đầu.",
        "Đang tính index cho giá trị.",
        "Đang dò tuyến tính do va chạm.",
        "Đã chèn giá trị vào slot."
    };
    vector<string> lines_search = {
        "Chọn thao tác để bắt đầu.",
        "Đang tính index cho giá trị.",
        "Đang dò tuyến tính để tìm.",
        "Đã tìm thấy giá trị."
    };
    vector<string> lines_delete = {
        "Chọn thao tác để bắt đầu.",
        "Đang tính index cho giá trị.",
        "Đang dò tuyến tính để xóa.",
        "Đã xóa giá trị khỏi slot."
    };
    vector<string> lines_init = {
        "Chọn thao tác để bắt đầu.",
        "Đang khởi tạo bảng mới.",
        "Đang tạo bảng ngẫu nhiên.",
        "Đang tải bảng từ file."
    };
    vector<string> lines;

    float highlightline = -1;

    const float MENU_WIDTH = ScreenWidth / 5.0f;
    const float Height_Area = 100.0f;
    const float Weigh_Area = MENU_WIDTH * 0.85f;
    const float Coordinate_X_Area = MENU_WIDTH * 0.075f;
    const float Coordinate_Y_Area = (20 + 60 /*Start position Button Init*/) + 8.3 * (30 + 15) + 495; /*Dưới ô pseudocode*/

    Color color_area = C[1];

    Rectangle area_text{
        Coordinate_X_Area,
        Coordinate_Y_Area,
        Weigh_Area,
        Height_Area,
    };

    void Setstringexplancode(string text) { this->text = text; }
    void SetHighLight(int highlightline) { this->highlightline = highlightline; }
    void DrawExplancodeArea();
};

#endif // !EXPLANATIONCODE_HPP