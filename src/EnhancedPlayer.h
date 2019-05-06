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

    float min_vertical_velocity;
    float horizontal_deceleration;
    float horizontal_acceleration;

    glm::vec2 magnet_accelerations;
    glm::vec2 net_acceleration;
    glm::vec2 velocity;
    glm::vec3 border_positions[10];
    float leg_length;
    float leg_width;
    float body_length;


    IrregularPolygon body;
    IrregularPolygon left_hand;
    IrregularPolygon right_hand;
    IrregularPolygon left_leg;
    IrregularPolygon right_leg;
    IrregularPolygon jet_box;
    IrregularPolygon fire[5];

    float height;
    float size;

    void move_right();
    void move_left();
    void move_up();
    void move_down();

    void update_position_x(float x);
    void update_position_y(float y);
    void update_border_postitions();
    void move_in_circle(float radius);
//    void get_position();

    float rotation_speed;
    bool moving_up;
    bool glow_fire;

    bool moving_left;
private:
    bool hand_going_up;
    bool moving_right;
    float leg_rotation_speed;

//    void reset_rotation_values();

};


#endif //GRAPHICS_ASGN1_ENHANCEDPLAYER_H
