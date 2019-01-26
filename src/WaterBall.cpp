//
// Created by sriteja on 25/1/19.
//

#include "WaterBall.h"
#include "Borders.h"
extern Borders ground;

WaterBall::WaterBall(glm::vec3 position, float radius, glm::vec2 initial_velocity, bool move_left) {

    this->position = position;
    this->radius = radius;
    water_ball = Ball(position.x, position.y, COLOR_SKY_BLUE);
    this->velocity.x = move_left ? -10.0f : 10.0f;
    this->velocity.y = initial_velocity.y;

}

void WaterBall::draw(glm::mat4 VP) {
    water_ball.draw(VP);
}


void WaterBall::tick() {
    float time_of_tick = 1.0f / 60.0f;
    float displacment = 0.0f;

    displacment = velocity.x * time_of_tick;
    water_ball.position.x += displacment;


    if (water_ball.position.y - water_ball.radius > ground.max_y) {
        velocity.y += (GRAVITY-22) * time_of_tick;
        displacment = velocity.y*time_of_tick + 1.0f /2.0f * (GRAVITY-22) * time_of_tick *time_of_tick;
        water_ball.position.y -=  displacment;
    }

    update_border_positions();
}

void WaterBall::update_border_positions() {
    border_positions[0] = glm::vec3(water_ball.position.x + water_ball.radius, water_ball.position.y, 0.0f);
    border_positions[1] = glm::vec3(water_ball.position.x - water_ball.radius, water_ball.position.y, 0.0f);
    border_positions[2] = glm::vec3(water_ball.position.x, water_ball.position.y + water_ball.radius, 0.0f);
    border_positions[3] = glm::vec3(water_ball.position.x, water_ball.position.y - water_ball.radius, 0.0f);
}