//
// Created by sriteja on 25/1/19.
//

#ifndef GRAPHICS_ASGN1_ESCAPELOOP_H
#define GRAPHICS_ASGN1_ESCAPELOOP_H

#include "main.h"
#include "ball.h"


class EscapeLoop {
public:
    EscapeLoop() {};
    EscapeLoop (glm::vec3 position);
    glm::vec3 position;
    glm::vec3 radius;
    Ball head;
    Ball center_space;

    void draw(glm::mat4 VP);
};


#endif //GRAPHICS_ASGN1_ESCAPELOOP_H
