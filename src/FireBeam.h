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
    FireBeam(glm::vec3 wedge1_position, glm::vec3 wedge2_position, float min_y, float max_y, float distance);
    IrregularPolygon wedge1;
    IrregularPolygon wedge2;
    IrregularPolygon wedge3;
    IrregularPolygon wedge4;
    IrregularPolygon beam;
    IrregularPolygon beam_2;
    float beam_length;
    float beam_width;
    float min_y;
    float max_y;
    bool glow_beam;
    bool go_down;
    int number;
    bool move;
    void draw_firebeam(glm::mat4 VP);
    void tick();
    void change_y_position(float y);
    void change_x_position(float x);
    RectangleObject convert_rectangle_object(int beam_id);
private:
    bool going_up;
};


#endif //GRAPHICS_ASGN1_FIREBEAM_H
