//
// Created by sriteja on 18/1/19.
//

#ifndef GRAPHICS_ASGN1_BOOMERANG_H
#define GRAPHICS_ASGN1_BOOMERANG_H

#include "main.h"
#include "IrregularPolygon.h"

class Boomerang : public IrregularPolygon{
public:
    Boomerang() {}
    Boomerang(glm::vec3 position);
    float rotation_speed;
    float moving_speed;
    void tick();
    CircleObject convert_circle_object();
    GLfloat * get_coordinates();
private:

};


#endif //GRAPHICS_ASGN1_BOOMERANG_H
