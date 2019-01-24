//
// Created by sriteja on 16/1/19.
//

#include "FireBeam.h"


FireBeam::FireBeam(glm::vec3 wedge1_position, glm::vec3 wedge2_position, float min_y, float max_y) {

    going_up = true;
    this->min_y = min_y;
    this->max_y = max_y;
    GLfloat wedge1_coor[] = {
            -1.0f, 0.5f, 0.0f,
            -1.0f, -0.5f, 0.0f,
            2.0f, 0.0f, 0.0f
    };

    GLfloat wedge2_coor[] = {
            1.0f, 0.5f, 0.0f,
            1.0f, -0.5f, 0.0f,
            -2.0f, 0.0f, 0.0f
    };

    this->wedge1 = IrregularPolygon(3, wedge1_coor, wedge1_position, COLOR_CHOCOLATE, false, glm::vec3(2.0f));
    this->wedge2 = IrregularPolygon(3, wedge2_coor, wedge2_position, COLOR_CHOCOLATE, false, glm::vec3(2.0f));

    beam_length = (float)fabs(wedge1.position.x - wedge2.position.x);
    beam_width = 1.0f;
    printf("beam length -> %f\n",beam_length);
    GLfloat beam_coor[] = {
            beam_length/2.0f, beam_width / 2.0f, 0.0f,
            -beam_length/2.0f, beam_width / 2.0f, 0.0f,
            -beam_length/2.0f, -beam_width / 2.0f, 0.0f,
            beam_length/2.0f, -beam_width / 2.0f, 0.0f
    };

    glm::vec3 beam_position = glm::vec3((wedge1.position.x + wedge2.position.x)/2,(wedge1.position.y+ wedge2.position.y)/2, 0.0f );

    beam = IrregularPolygon(4, beam_coor, beam_position, COLOR_CRIMSON);
}


void FireBeam::draw_firebeam(glm::mat4 VP) {
    this->wedge1.draw(VP);
    this->wedge2.draw(VP);
    this->beam.draw(VP);
}

void FireBeam::change_y_position(float y) {
    this->wedge1.position.y += y;
    this->wedge2.position.y += y;
    this->beam.position.y += y;
}

void FireBeam::tick() {

    if (going_up) {

        if (this->wedge1.position.y > max_y) {
            going_up = false;
            change_y_position(-0.3f);
            printf("came here");
        } else {
            change_y_position(0.3f);
        }
    } else {
        if (this->wedge1.position.y < min_y) {
            going_up = true;
            change_y_position(0.3);
        } else {
            change_y_position(-0.3f);
        }
    }
}

RectangleObject FireBeam::convert_rectangle_object() {
    RectangleObject temp = {};
    temp.Position.x = this->beam.position.x - this->beam_length /2.0f;
    temp.Position.y = this->beam.position.y - 0.5f;
    temp.Size.x = beam_length;
    temp.Size.y = beam_width;
    return temp;

}