//
// Created by sriteja on 16/1/19.
//

#include "FireBeam.h"


FireBeam::FireBeam(glm::vec3 wedge1_position, glm::vec3 wedge2_position, float min_y, float max_y, float distance) {

    going_up = true;
    go_down = false;
    number = 0;
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
    float start_y_position = 0.0f;

    this->wedge1 = IrregularPolygon(3, wedge1_coor, glm::vec3(wedge1_position.x, -40.0f, 0.0f), COLOR_CHOCOLATE, false, glm::vec3(2.0f));
    this->wedge2 = IrregularPolygon(3, wedge2_coor, glm::vec3(wedge2_position.x, -40.0f, 0.0f), COLOR_CHOCOLATE, false, glm::vec3(2.0f));
    this->wedge3 = IrregularPolygon(3, wedge1_coor, glm::vec3(wedge1_position.x, -40.0f - distance, 0.0f), COLOR_CHOCOLATE, false, glm::vec3(2.0f));
    this->wedge4 = IrregularPolygon(3, wedge2_coor, glm::vec3(wedge2_position.x, -40.0f - distance, 0.0f), COLOR_CHOCOLATE, false, glm::vec3(2.0f));

    beam_length = (float)fabs(wedge1.position.x - wedge2.position.x);
    beam_width = 1.0f;
    printf("beam length -> %f\n",beam_length);
    GLfloat beam_coor[] = {
            beam_length/2.0f, beam_width / 2.0f, 0.0f,
            -beam_length/2.0f, beam_width / 2.0f, 0.0f,
            -beam_length/2.0f, -beam_width / 2.0f, 0.0f,
            beam_length/2.0f, -beam_width / 2.0f, 0.0f
    };

    glm::vec3 beam_position = glm::vec3((wedge1.position.x + wedge2.position.x)/2, -40.0f, 0.0f );

    beam = IrregularPolygon(4, beam_coor, beam_position, COLOR_CRIMSON);
    beam_2 = IrregularPolygon(4, beam_coor, glm::vec3(beam_position.x, beam_position.y - distance, 0.0f), COLOR_CRIMSON);
}


void FireBeam::draw_firebeam(glm::mat4 VP) {
    this->wedge1.draw(VP);
    this->wedge2.draw(VP);
    this->wedge3.draw(VP);
    this->wedge4.draw(VP);
    this->beam.draw(VP);
    this->beam_2.draw(VP);
}

void FireBeam::change_y_position(float y) {
    this->wedge1.position.y += y;
    this->wedge2.position.y += y;
    this->wedge3.position.y += y;
    this->wedge4.position.y += y;
    this->beam.position.y += y;
    this->beam_2.position.y += y;
}


void FireBeam::change_x_position(float x) {
    this->wedge1.position.x += x;
    this->wedge2.position.x += x;
    this->wedge3.position.x += x;
    this->wedge4.position.x += x;
    this->beam.position.x += x;
    this->beam_2.position.x += x;
}

void FireBeam::tick() {

    if (go_down) {
        change_y_position(-0.2f);
        return;
    }

        if (going_up) {

            if (this->wedge1.position.y > max_y) {
                going_up = false;
                change_y_position(-0.15f);
                printf("came here");
            } else {
                change_y_position(0.15f);
            }
        } else {
            if (this->wedge3.position.y < min_y) {
                going_up = true;
                change_y_position(0.15);
                number += 1;
                if (number == 3) go_down = true;
            } else {
                change_y_position(-0.15f);
            }
        }

}

RectangleObject FireBeam::convert_rectangle_object(int beam_id) {
    RectangleObject temp = {};
    if (beam_id ==1) {
        temp.Position.x = this->beam.position.x - this->beam_length / 2.0f;
        temp.Position.y = this->beam.position.y - 0.5f;
    } else {
        temp.Position.x = this->beam_2.position.x - this->beam_length / 2.0f;
        temp.Position.y = this->beam_2.position.y - 0.5f;
    }
    temp.Size.x = beam_length;
    temp.Size.y = beam_width;
    return temp;

}