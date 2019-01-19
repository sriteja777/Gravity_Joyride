//
// Created by sriteja on 13/1/19.
//
#include "main.h"
#include "IrregularPolygon.h"
#ifndef GRAPHICS_ASGN1_PLAYER_H
#define GRAPHICS_ASGN1_PLAYER_H


class Player : public IrregularPolygon {
public:
    Player() {};
    Player (glm::vec3 position);
    void move_left();
    void move_right();
    void jump();
    float speed;
    float size;
    int get_number_of_sides();
    GLfloat * get_coordinates();
    color_t get_color();
    void move_down();
    void tick();
    float time_of_falling;
    void increase_player_size();
private:
    GLfloat *vertices;
};


#endif //GRAPHICS_ASGN1_PLAYER_H
