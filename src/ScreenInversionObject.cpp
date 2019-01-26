//
// Created by sriteja on 26/1/19.
//

#include "ScreenInversionObject.h"
#include "Borders.h"
extern Borders slab;
extern Borders ground;

ScreenInversionObject::ScreenInversionObject(glm::vec3 position) {
    object = Ball(position.x, position.y, COLOR_RED);
    this->position = position;
    this->alive = true;
}

void ScreenInversionObject::draw(glm::mat4 VP) {
    this->object.draw(VP);
}


void ScreenInversionObject::tick() {
    this->object.position.x += 0.08;

    if (going_up) {

        if (int(this->object.position.y) == int(slab.min_y)) {
            going_up = false;
            this->object.position.y -= 0.3;
            printf("came here");
        } else {
            this->object.position.y += 0.3;
        }
    } else {
        if ((int)this->object.position.y == (int)ground.max_y + 2) {
            going_up = true;
            this->object.position.y += 0.3;
        } else {
            this->object.position.y -= 0.3;
        }
    }
}

CircleObject ScreenInversionObject::convert_to_circle() {
    CircleObject temp = {this->object.position - this->object.radius,};
    temp.Radius = this->object.radius;
    return  temp;
}