#include "DescriptionBox.hpp"
#include <sstream>
#include <vector>

extern Color C[6];

DescriptionBox::DescriptionBox() {
    box_area = {
        (ScreenWidth / 5.0f) * 0.075f,
        (20 + 60  /*Start position Button Init*/) + 8.3 * (30 + 15), /*position * (BUTTON_HEIGHT + BUTTON_SPACING)*/
        (ScreenWidth / 5.0f) * 0.85f,
        100.0f,
    };
    description = "";
}

void DescriptionBox::SetPosition(float x, float y, float width, float height) {
    box_area = { x, y, width, height };
}

void DescriptionBox::SetDescription(const std::string& new_text) {
    description = new_text;
}

void DescriptionBox::DrawDescriptionBox() const {
    DrawRectangleRounded(box_area, 0.3f, 10, C[2]);
    const int font_size = 20;
    const int padding = 10;
    const float line_spacing = 5.0f;
    const float max_width = box_area.width - 2 * padding;
    std::vector<std::string> words;
    std::istringstream iss(description);
    std::string word;
    while (iss >> word) words.push_back(word);
    std::vector<std::string> lines;
    std::string current_line;
    float current_width = 0.0f;
    for (const auto& word : words) {
        float word_width = MeasureText(word.c_str(), font_size);
        float space_width = MeasureText(" ", font_size);
        if (current_line.empty()) {
            if (word_width <= max_width) {
                current_line = word;
                current_width = word_width;
            }
            else {
                for (size_t i = 0; i < word.length(); ) {
                    int chars_fit = 0;
                    float partial_width = 0.0f;
                    while (i + chars_fit < word.length()) {
                        int new_chars_fit = chars_fit + 1;
                        std::string partial = word.substr(i, new_chars_fit);
                        float new_width = MeasureText(partial.c_str(), font_size);
                        if (new_width > max_width) break;
                        chars_fit = new_chars_fit;
                        partial_width = new_width;
                    }
                    if (chars_fit == 0) chars_fit = 1;
                    lines.push_back(word.substr(i, chars_fit));
                    i += chars_fit;
                }
            }
        }
        else {
            if (current_width + space_width + word_width <= max_width) {
                current_line += " " + word;
                current_width += space_width + word_width;
            }
            else {
                lines.push_back(current_line);
                current_line = word;
                current_width = word_width;
            }
        }
    }

    if (!current_line.empty()) {
        lines.push_back(current_line);
    }

    float total_height = lines.size() * (font_size + line_spacing) - line_spacing;
    float start_y = box_area.y + (box_area.height - total_height) / 2;

    for (size_t i = 0; i < lines.size(); i++) {
        const auto& line = lines[i];
        float text_width = MeasureText(line.c_str(), font_size);
        float start_x = box_area.x + (box_area.width - text_width) / 2;
        DrawText(line.c_str(),
            static_cast<int>(start_x),
            static_cast<int>(start_y + i * (font_size + line_spacing)),
            font_size, C[0]);
    }
}