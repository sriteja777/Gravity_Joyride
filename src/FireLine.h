//
// Created by sriteja on 16/1/19.
//

#ifndef GRAPHICS_ASGN1_FIRELINE_H
#define GRAPHICS_ASGN1_FIRELINE_H

#include "main.h"
#include "IrregularPolygon.h"
#include "ball.h"

class FireLine{
public:
    FireLine() {}
    FireLine(glm::vec3 position_one, glm::vec3 position_two, bool rotate = false, float rotation_speed=0.01f);
    Ball orb1;
    Ball orb2;
    bool rotate;
    float rotation_speed;
    IrregularPolygon connector;
    float distance_between_orbs;
    void draw_fireline(glm::mat4 VP);
    void tick();
    RectangleObject convert_to_rectangle_object();

    glm::vec3 line_equations[4];
private:
    float rotation_angle;
    VAO *orb1_object;
    VAO *orb2_object;
    VAO *connector_object;

};


#endif //GRAPHICS_ASGN1_FIRELINE_H
