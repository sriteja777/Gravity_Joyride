//
// Created by sriteja on 25/1/19.
//

#include "EscapeLoop.h"


EscapeLoop::EscapeLoop(glm::vec3 position) {
    this->position = position;
    head = Ball (position.x, position.y, COLOR_NAVY, glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, 25.0f, 190.0f);
    center_space = Ball(position.x, position.y, COLOR_BACKGROUND, glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, 15.0f, 190.0f);
}

void EscapeLoop::draw(glm::mat4 VP) {
    head.draw(VP);
    center_space.draw(VP);
}