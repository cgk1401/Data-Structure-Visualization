#include "Pseudocode.hpp"
#include <raylib.h>
#include <string>


void Pseudocode::DrawPseudocode() {
    // Gán danh sách dòng dựa trên text
    if (text == "INSERT") line = lineinsert;
    else if (text == "SEARCH") line = linesearch;
    else if (text == "DELETE") line = linedelete;
    else if (text == "INSERT_HASHTABLE") line = lineinsert_hashtable;
    else if (text == "SEARCH_HASHTABLE") line = linesearch_hashtable;
    else if (text == "DELETE_HASHTABLE") line = linedelete_hashtable;
    else if (text == "") line.clear();

    // Vẽ nền khu vực mã giả
    DrawRectangleRounded(this->area_text, 0.1f, 100, C[2]);

    // Thiết lập thông số vẽ
    const float lineheight = 30.0f; // Khoảng cách giữa các dòng
    const float text_margin = 15.0f; // Lề trái/phải để tránh tràn
    float y = area_text.y + 10.0f; // Margin trên

    // Vẽ từng dòng
    for (int i = 0; i < line.size(); i++) {
        // Kiểm tra tràn dọc
        if (y + 20.0f > area_text.y + area_text.height) {
            break; // Không vẽ nếu vượt quá chiều cao khu vực
        }

        // Lấy văn bản hiện tại
        std::string text = line[i];
        int text_width = MeasureText(text.c_str(), 20);
        float max_width = area_text.width - 2 * text_margin;

        // Nếu văn bản vừa với chiều rộng, vẽ bình thường
        if (text_width <= max_width) {
            if (i == highlightline) {
                DrawRectangle(area_text.x, y - 10, area_text.width, 30, BLACK);
            }
            DrawText(text.c_str(), area_text.x + text_margin, y, 20, WHITE);
            y += lineheight;
            if (i == highlightline) {
                DrawRectangle(area_text.x, y - 10, area_text.width, 35, GRAY);
            }
            else {
                // Nếu văn bản quá dài, chia thành nhiều dòng (text wrapping)
                std::string remaining_text = text;
                bool is_highlighted = (i == highlightline);

                while (!remaining_text.empty()) {
                    // Kiểm tra tràn dọc
                    if (y + 20.0f > area_text.y + area_text.height) {
                        break;
                    }

                    // Tìm đoạn văn bản vừa với max_width
                    size_t chars_to_draw = remaining_text.length();
                    std::string sub_text = remaining_text;
                    int sub_width = MeasureText(sub_text.c_str(), 20);

                    while (sub_width > max_width && chars_to_draw > 0) {
                        // Tìm vị trí cắt gần nhất tại khoảng trắng
                        chars_to_draw = sub_text.rfind(' ', chars_to_draw - 1);
                        if (chars_to_draw == std::string::npos) {
                            chars_to_draw = (max_width / (sub_width / sub_text.length()));
                        }
                        sub_text = remaining_text.substr(0, chars_to_draw);
                        sub_width = MeasureText(sub_text.c_str(), 20);
                    }

                    // Vẽ đoạn văn bản
                    if (is_highlighted) {
                        DrawRectangle(area_text.x, y - 10, area_text.width, 30, BLACK);
                    }
                    DrawText(sub_text.c_str(), area_text.x + text_margin, y, 20, WHITE);

                    // Cập nhật văn bản còn lại
                    if (chars_to_draw >= remaining_text.length()) {
                        remaining_text.clear();
                    }
                    else {
                        remaining_text = remaining_text.substr(chars_to_draw);
                        // Xóa khoảng trắng đầu dòng nếu có
                        while (!remaining_text.empty() && remaining_text[0] == ' ') {
                            remaining_text.erase(0, 1);
                        }
                    }

                    DrawText(line[i].c_str(), area_text.x + 10, y, 20, WHITE);
                    y += lineheight;
                }
            }
        }
    }
}