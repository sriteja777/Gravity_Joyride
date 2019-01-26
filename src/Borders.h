//
// Created by sriteja on 25/1/19.
//

#ifndef GRAPHICS_ASGN1_BORDERS_H
#define GRAPHICS_ASGN1_BORDERS_H

#include "main.h"
#include "IrregularPolygon.h"

class Borders {
public:
    Borders() {}
    Borders(float length, float height, glm::vec3 position, color_t color);
    float min_y;
    float max_y;
    float min_x;
    float max_x;
    void draw(glm::mat4 VP);
private:
    IrregularPolygon object;
};


#endif //GRAPHICS_ASGN1_BORDERS_H
