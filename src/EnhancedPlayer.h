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
    float upward_acceleration;
    float downward_acceleration;
    float max_vertical_velocity;
    float vertical_velocity;
    float min_vertical_velocity;
    float horizontal_velocity;
    float horizontal_deceleration;
    float horizontal_acceleration;

    IrregularPolygon body;
    IrregularPolygon left_hand;
    IrregularPolygon right_hand;
    IrregularPolygon left_leg;
    IrregularPolygon right_leg;
    IrregularPolygon jet_box;
    IrregularPolygon fire[5];

    void move_right();
    void move_left();
    void move_up();
    void move_down();

    void update_position_x(float x);
    void update_position_y(float y);
//    void get_position();
    float net_vertical_acceleration;
    float rotation_speed;
    bool moving_up;
    bool glow_fire;

private:
    bool hand_going_up;
    bool moving_left;
    bool moving_right;
    float leg_rotation_speed;

//    void reset_rotation_values();

};


#endif //GRAPHICS_ASGN1_ENHANCEDPLAYER_H
