#include <cmath>

//
// Created by sriteja on 18/1/19.
//

#include "Boomerang.h"
#include "IrregularPolygon.h"

Boomerang::Boomerang(glm::vec3 position) : IrregularPolygon(4, get_coordinates(), position, COLOR_PERU, 0.0f, glm::vec3(3.0f, 2.0f, 2.0f), glm::vec3(0.0f, 1.0f, -0.25f)){
    GLfloat coordinates[] = {
            1.0f, 0.4f, 1.0f,
            -1.0f, 0.0f, 0.0f,
            1.0f, -0.4f, -1.0f,
            0.0f, 0.0f, 0.f,
    };


    moving_speed = 0.5;
    rotation_speed = 0.25;
}

GLfloat * Boomerang::get_coordinates() {
    static GLfloat boomerang_coordinates[] = {
            1.0f, 0.4f, 1.0f,
            -1.0f, 0.0f, 0.0f,
            1.0f, -0.4f, -1.0f,
            0.0f, 0.0f, 0.f,
    };

    return boomerang_coordinates;
}


void Boomerang::tick() {
//    if (moving_left) {
//        if (rotation_speed >= 0)
//            this->rotation_speed -= 0.0015;
//        else {
//            moving_left = false;
//            this->rotation_speed += 0.0015;
//        }
//    }
//    else {
//        if (rotation_speed <= 0.3)
//            this->rotation_speed += 0.0015;
//        else {
//            moving_left = true;
//            this->rotation_speed -= 0.0015;
//        }
//    }

//    if (moving_left) {
//        rotation_speed -= 0.0009;
//    }
//    else {
//        rotation_speed += 0.0009;
//    }

    if (position.x - Screen.dimensions.min_x < 10) {
        this->position.y -= 0.5;
        this->moving_speed = -0.5f;
    }

//    this->moving_speed -= 0.0015;
    this->rotation += this->rotation_speed;
    this->position.x -= this->moving_speed;
//    this->position.y -= 0.08;
}


CircleObject Boomerang::convert_circle_object() {
    CircleObject temp = {this->position,};
    temp.Radius = 5.0f;
//    printf(" poistion -> %f, %f  radius -> %f\n", temp.Position.x, temp.Position.y, temp.Radius);
    return temp;
}

LineObject Boomerang::convert_line_object() {
    LineObject temp = {this->position, };
    temp.Length = 4.0f;
    return temp;
}