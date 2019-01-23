#include <cmath>

//
// Created by sriteja on 16/1/19.
//

#include "FireLine.h"
#include "main.h"
#include "IrregularPolygon.h"
#include "ball.h"

FireLine::FireLine(glm::vec3 position_one, glm::vec3 position_two, bool rotate, float rotation_speed) {

    this->rotate = rotate;
    this->rotation_speed = rotation_speed;


    this->orb1 = Ball(position_one.x, position_one.y, COLOR_GREEN);
    this->orb2 = Ball(position_two.x, position_two.y, COLOR_GREEN);
    distance_between_orbs = sqrtf((position_two.x - position_one.x)*(position_two.x - position_one.x) + (position_two.y - position_one.y)*(position_two.y - position_one.y));
    GLfloat connector_coordinates[] = {
            distance_between_orbs/2, orb1.radius, 0.0f,
            distance_between_orbs/2,-orb1.radius, 0.0f,
            -distance_between_orbs/2,-orb1.radius, 0.0f,
            -distance_between_orbs/2,orb1.radius, 0.0f,
    };
    this->rotation_angle = (float)atan((double)(orb1.position.y - orb2.position.y)/(orb1.position.x - orb2.position.x));


    this->connector = IrregularPolygon(4, connector_coordinates,
            glm::vec3((orb1.position.x + orb2.position.x)/2, (orb1.position.y + orb2.position.y)/2, 0.0),
            COLOR_RED, this->rotation_angle);
}


void FireLine::draw_fireline(glm::mat4 VP) {
    this->orb1.draw(VP);
    this->orb2.draw(VP);
    this->connector.draw(VP);
}


void FireLine::tick() {
    if (this->rotate) {

        this->rotation_angle += rotation_speed;
        this->connector.rotation += rotation_speed;

        float relative_x =  this->distance_between_orbs/2 * std::cos(this->rotation_angle);
        float relative_y = this->distance_between_orbs/2 * std::sin(this->rotation_angle);

        this->orb1.set_position(this->connector.position.x + relative_x, this->connector.position.y + relative_y);
        this->orb2.set_position(this->connector.position.x - relative_x, this->connector.position.y - relative_y);
    }
}


RectangleObject FireLine::convert_to_rectangle_object() {
    RectangleObject temp = {this->connector.position, };
    temp.Size.x = this->distance_between_orbs;
    temp.Size.y = 2 * this->orb1.radius;
    return temp;
}