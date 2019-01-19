//
// Created by sriteja on 13/1/19.
//
#include "main.h"
#ifndef GRAPHICS_ASGN1_REGULARPOLYGON_H
#define GRAPHICS_ASGN1_REGULARPOLYGON_H

class RegularPolygon {
public:
    RegularPolygon() {}
    RegularPolygon(int num_of_sides, glm::vec3 center, float radius);
    glm::vec3 center;
    float radius;
    int num_of_sides;
    void construct();
private:
    VAO *object;

};




#endif //GRAPHICS_ASGN1_REGULARPOLYGON_H
