//
// Created by sriteja on 25/1/19.
//

#include "Borders.h"
#include "IrregularPolygon.h"


Borders::Borders(float length, float height, glm::vec3 position, color_t color) {
    min_x = position.x;
    max_x = position.x + length;
    min_y = position.y;
    max_y = position.y + height;

    GLfloat object_coordinates[] = {
            length, height, 0.0f,
            0.0f, height, 0.0f,
            0.0f, 0.0f, 0.0f,
            length, 0.0f, 0.0f
    };
    object = IrregularPolygon(4, object_coordinates, position, color);
}


void Borders::draw(glm::mat4 VP) {
    object.draw(VP);
}