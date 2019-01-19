//
// Created by sriteja on 19/1/19.
//

#ifndef GRAPHICS_ASGN1_ENHANCEDPLAYER_H
#define GRAPHICS_ASGN1_ENHANCEDPLAYER_H

#include "IrregularPolygon.h"
#include "main.h"
#include "ball.h"

class EnhancedPlayer {
public:
    EnhancedPlayer() {}

    explicit EnhancedPlayer(glm::vec3 position);
    void draw(glm::mat4 VP);
    glm::vec3 position;
    Ball head;
    float speed;
    float hand_rotation_angle;


    IrregularPolygon body;
    IrregularPolygon foot;
    IrregularPolygon left_hand;
    IrregularPolygon right_hand;
    IrregularPolygon left_leg;
    IrregularPolygon right_leg;

    void move_right();

    float rotation_speed;

    void move_left();

private:
    bool hand_going_up;
    bool moving_left;
    float leg_rotation_speed;
//    void reset_rotation_values();
};


#endif //GRAPHICS_ASGN1_ENHANCEDPLAYER_H
