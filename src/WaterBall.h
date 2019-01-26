//
// Created by sriteja on 25/1/19.
//

#ifndef GRAPHICS_ASGN1_WATERBALL_H
#define GRAPHICS_ASGN1_WATERBALL_H

#include "main.h"
#include "ball.h"

class WaterBall {
public:
    WaterBall() {}
    WaterBall (glm::vec3 position, float radius = 0.0f, glm::vec2 initial_velocity = glm::vec2(0.0f), bool move_left= false);

    glm::vec3 position;
    float radius;
    Ball water_ball;
    glm::vec2 velocity;
    glm::vec3 border_positions[4];

    void draw(glm::mat4 VP);
    void tick();
    void update_border_positions();

};


#endif //GRAPHICS_ASGN1_WATERBALL_H
