//
// Created by sriteja on 16/1/19.
//

#ifndef GRAPHICS_ASGN1_FIREBEAM_H
#define GRAPHICS_ASGN1_FIREBEAM_H

#include "main.h"
#include "IrregularPolygon.h"


class FireBeam {
public:
    FireBeam() {}
    FireBeam(glm::vec3 wedge1_position, glm::vec3 wedge2_position, float min_y, float max_y );
    IrregularPolygon wedge1;
    IrregularPolygon wedge2;
    IrregularPolygon beam;
    float beam_length;
    float beam_width;
    float min_y;
    float max_y;
    void draw_firebeam(glm::mat4 VP);
    void tick();
    void change_y_position(float y);
    RectangleObject convert_rectangle_object();
private:
    bool going_up;
};


#endif //GRAPHICS_ASGN1_FIREBEAM_H
