#include <cmath>

//
// Created by sriteja on 25/1/19.
//

#include "Magnet.h"


Magnet::Magnet(glm::vec3 position, float rotation_angle) {
    this->position = position;
    this->rotation = 0.0f;
    head = Ball(position.x, position.y, COLOR_RED, glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, 5.0f, 190.0f);
    center_space = Ball(position.x, position.y, COLOR_BACKGROUND, glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, 3.0f, 190.0f );
    float pole_length = 5.0f;
    GLfloat pole_coordinates[] = {
            head.radius - center_space.radius, -pole_length, 0.0f,
            head.radius - center_space.radius, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, -pole_length, 0.0f,
    } ;

    glm::vec3 north_pole_position (head.position.x + center_space.radius * std::cos(this->rotation), head.position.x + center_space.radius *
                                                                                                                  std::sin(this->rotation), 0.0f);
    south_pole = IrregularPolygon(4, pole_coordinates, glm::vec3(head.position.x - head.radius, head.position.y, 0.0f), COLOR_SILVER);
    north_pole = IrregularPolygon(4, pole_coordinates, north_pole_position, COLOR_SILVER);
}

void Magnet::draw(glm::mat4 VP) {
    head.draw(VP);
    center_space.draw(VP);
    north_pole.draw(VP);
    south_pole.draw(VP);
}


CircleObject Magnet::convert_circle() {
    CircleObject temp = {position - 20.0f,};
    temp.Radius = 20.0f;
    return temp;

}