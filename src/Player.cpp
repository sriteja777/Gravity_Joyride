//
// Created by sriteja on 13/1/19.
//

#include "Player.h"
#include "IrregularPolygon.h"
#include "main.h"

Player::Player(glm::vec3 position) : IrregularPolygon(get_number_of_sides(), get_coordinates(), position, get_color()) {

    speed = 0.7;
    time_of_falling = 0;

}

int Player::get_number_of_sides() { return 14; }
color_t Player::get_color() { return COLOR_RED; }
GLfloat * Player::get_coordinates() {
    static GLfloat coordinates_player[] = {
            -1.0f, 1.0f, 0.0f,
            -1.5f, -1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            -1.0f, 2.0f, 0.0f,
             1.0f, 2.0f, 0.0f,
             1.0f, 1.0f, 0.0f,
             1.5f, -1.0f, 0.f,
             1.0f, 0.0f, 0.0f,
             1.0f, -2.0f, 0.0f,
             0.5f, -2.0f, 0.0f,
             0.5f, -1.0f, 0.0f,
            -0.5f, -1.0f, 0.0f,
            -0.5f, -2.0f, 0.0f,
            -1.0f, -2.0f, 0.0f,
    };
    this->size = 2;
    return coordinates_player;
}



void Player::move_left() {
    this->position.x -= speed;
}
void Player::move_right() {
    this->position.x += speed;
}
void Player::jump() {
    this->position.y += speed;
    time_of_falling = 0.0;
}

void Player::move_down() {
    if (this->position.y > Screen.dimensions.min_y + 12)
        this->position.y -= speed;
}
void Player::tick() {
    this->position.x += 0.11;
}

void Player::increase_player_size() {
    this->scale = glm::vec3(2.0f);
}
