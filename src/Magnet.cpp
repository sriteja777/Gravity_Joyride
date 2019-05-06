#include <cmath>

#include <cmath>

//
// Created by sriteja on 25/1/19.
//

#include "Magnet.h"


Magnet::Magnet(glm::vec3 position, float rotation_angle) {
    this->position = position;
    this->rotation = rotation_angle;
    head = Ball(position.x, position.y, COLOR_RED, glm::vec3(0.0f, 0.0f, 1.0f), rotation, 5.0f, 190.0f);
    center_space = Ball(position.x, position.y, COLOR_BACKGROUND, glm::vec3(0.0f, 0.0f, 1.0f), rotation, 3.0f, 190.0f );
    this->rotation = static_cast<float>(rotation * M_PI / 180);
    float pole_length = 5.0f;
    float pole_width = head.radius - center_space.radius;
    GLfloat pole_coordinates[] = {
            head.radius - center_space.radius, -pole_length, 0.0f,
            head.radius - center_space.radius, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, -pole_length, 0.0f,
    } ;

    glm::vec3 point1 (pole_length*std::sin(rotation), -pole_length*std::cos(rotation), 0.0f);
    glm::vec3 point3 (-pole_width*std::cos(rotation), -pole_width*std::sin(rotation), 0.0f);
    GLfloat south_pole_coordinates[] = {
            point1.x, point1.y, 0.0f,
            0.0f, 0.0f, 0.0f,
            point3.x, point3.y, 0.0f,
            point1.x+point3.x, +point1.y+point3.y, 0.0f

    };
    point3 = -point3;

    GLfloat north_pole_coordinates[] = {
            point1.x, point1.y, 0.0f,
            0.0f, 0.0f, 0.0f,
            point3.x, point3.y, 0.0f,
            point1.x + point3.x, point1.y + point3.y, 0.0f
    };


//    GLfloat

    glm::vec3 north_pole_position (head.position.x + center_space.radius * std::cos(this->rotation), head.position.x + center_space.radius *
                                                                                                                  std::sin(this->rotation), 0.0f);
//    south_pole = IrregularPolygon(4, pole_coordinates, glm::vec3(head.position.x - head.radius, head.position.y, 0.0f), COLOR_SILVER);
    south_pole = IrregularPolygon(4, south_pole_coordinates, glm::vec3(center_space.position.x-center_space.radius*std::cos(rotation), center_space.position.y-center_space.radius*std::sin(rotation), 0.0f), COLOR_SILVER);
//    north_pole = IrregularPolygon(4, pole_coordinates, north_pole_position, COLOR_ORCHID);
    north_pole = IrregularPolygon(4, north_pole_coordinates, glm::vec3(center_space.position.x+center_space.radius*std::cos(rotation), center_space.position.y+center_space.radius*std::sin(rotation), 0.0f), COLOR_SILVER);

    magnetic_border.Position = head.position - head.radius;
    magnetic_border.Size.x = 2*head.radius;
    magnetic_border.Size.y = 40;

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