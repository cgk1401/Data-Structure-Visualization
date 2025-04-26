#ifndef DESCRIPTION_BOX_HPP
#define DESCRIPTION_BOX_HPP

#include <raylib.h>
#include <string>
#include "Config.hpp"

class DescriptionBox {
private:
    Rectangle box_area;
    std::string description;

public:
    DescriptionBox();
    void DrawDescriptionBox() const;
    void SetDescription(const std::string& new_text);
    void SetPosition(float x, float y, float width, float height);
};

#endif // DESCRIPTION_BOX_HPP