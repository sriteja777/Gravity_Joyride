//
// Created by sriteja on 14/1/19.
//

#include "Diamond.h"
#include "Borders.h"

extern Borders slab;
extern Borders ground;

Diamond::Diamond(int bonus, glm::vec3 position, color_t color) : IrregularPolygon(5, get_coordinates(), position, color)  {
    this->alive = true;
    this->going_up = true;
}

GLfloat *Diamond::get_coordinates() {
    static GLfloat coordinates_diamond[] = {
            0.25f, 0.75f, 0.0f,
            0.75f, 0.25f, 0.0f,
            0.0f, -1.0f, 0.0f,
            -0.75f, 0.25f, 0.0f,
            -0.25f, 0.75f, 0.0f
    };

    return coordinates_diamond;

}

void Diamond::tick() {
    this->position.x += 0.08;

    if (going_up) {

        if (int(this->position.y) == int(slab.min_y - 2)) {
            going_up = false;
            this->position.y -= 0.3;
            printf("came here");
        } else {
            this->position.y += 0.3;
        }
    } else {
        if ((int)this->position.y == (int)ground.max_y + 2) {
            going_up = true;
            this->position.y += 0.3;
        } else {
            this->position.y -= 0.3;
        }
    }

}

CircleObject Diamond::convert_to_circle() {
    CircleObject temp = {this->position - 1.0f};
    temp.Radius = 1.0f;
    return temp;
}
