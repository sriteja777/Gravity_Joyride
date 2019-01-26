//
// Created by sriteja on 26/1/19.
//

#ifndef GRAPHICS_ASGN1_SCREENINVERSIONOBJECT_H
#define GRAPHICS_ASGN1_SCREENINVERSIONOBJECT_H

#include "main.h"
#include "ball.h"

class ScreenInversionObject {
public:
    ScreenInversionObject() {};
    ScreenInversionObject(glm::vec3 position);
    void tick();
    bool going_up;
    Ball object;
    bool alive;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    CircleObject convert_to_circle();

};


#endif //GRAPHICS_ASGN1_SCREENINVERSIONOBJECT_H
