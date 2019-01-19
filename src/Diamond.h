//
// Created by sriteja on 14/1/19.
//

#ifndef GRAPHICS_ASGN1_DIAMOND_H
#define GRAPHICS_ASGN1_DIAMOND_H

#include "main.h"
#include "IrregularPolygon.h"

class Diamond : public IrregularPolygon{
public:
    Diamond() {};
    Diamond(int bonus, glm::vec3 position, color_t color);
    int bonus;
    void tick();
    bool going_up;
private:
    GLfloat *get_coordinates();

};


#endif //GRAPHICS_ASGN1_DIAMOND_H
