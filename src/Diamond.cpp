//
// Created by sriteja on 14/1/19.
//

#include "Diamond.h"

Diamond::Diamond(int bonus, glm::vec3 position, color_t color) : IrregularPolygon(5, get_coordinates(), position, color)  {
    std::cout << this->num_of_sides;
}

GLfloat *Diamond::get_coordinates() {
    static GLfloat coordinates_diamond[] = {
            0.25f, 0.75f, 0.0f,
            0.75f, 0.25f, 0.0f,
            0.0f, -1.0f, 0.0f,
            -0.75f, 0.25f, 0.0f,
            -0.25f, 0.75f, 0.0f
    };
    this->going_up = true;
    return coordinates_diamond;

}

void Diamond::tick() {
    this->position.x += 0.08;

    if (going_up) {

        if (int(this->position.y) == int(Screen.dimensions.max_y)) {
            going_up = false;
            this->position.y -= 0.3;
            printf("came here");
        } else {
            this->position.y += 0.3;
        }
    } else {
        if ((int)this->position.y == (int)Screen.dimensions.min_y + 12) {
            going_up = true;
            this->position.y += 0.3;
        } else {
            this->position.y -= 0.3;
        }
    }

}
