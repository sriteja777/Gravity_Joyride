//
// Created by sriteja on 25/1/19.
//

#ifndef GRAPHICS_ASGN1_MAGNET_H
#define GRAPHICS_ASGN1_MAGNET_H


#include "main.h"
#include "ball.h"
#include "IrregularPolygon.h"


class Magnet {
public:
    Magnet() {}

    Magnet (glm::vec3 position, float rotation_angle = 0.0f);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    Ball head;
    Ball center_space;
    IrregularPolygon north_pole;
    IrregularPolygon south_pole;
    CircleObject convert_circle();

    float  rotation;
};


#endif //GRAPHICS_ASGN1_MAGNET_H
