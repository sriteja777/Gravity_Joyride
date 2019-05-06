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
    this->fire_extinguished = false;


    this->orb1 = Ball(position_one.x, position_one.y, COLOR_GREEN);
    this->orb2 = Ball(position_two.x, position_two.y, COLOR_GREEN);
    distance_between_orbs = sqrtf((position_two.x - position_one.x)*(position_two.x - position_one.x) + (position_two.y - position_one.y)*(position_two.y - position_one.y));
    GLfloat connector_coordinates[] = {
            distance_between_orbs/2, orb1.radius, 0.0f,
            distance_between_orbs/2,-orb1.radius, 0.0f,
            -distance_between_orbs/2,-orb1.radius, 0.0f,
            -distance_between_orbs/2,orb1.radius, 0.0f,
    };
    this->slope = (orb1.position.y - orb2.position.y)/(orb1.position.x - orb2.position.x);
    this->rotation_angle = (float)atan((double)slope);


    this->connector = IrregularPolygon(4, connector_coordinates,
            glm::vec3((orb1.position.x + orb2.position.x)/2, (orb1.position.y + orb2.position.y)/2, 0.0),
            COLOR_ORANGE_RED, this->rotation_angle);

    printf("rotation angle -> %f\n", (this->rotation_angle*180/M_PI));
    if (this->rotation_angle <0 ) {
        this->rotation_angle += M_PI;
    }

    find_line_eqns();
}


void FireLine::find_line_eqns() {
    glm::vec2 point = glm::vec2(static_cast<float>(orb1.position.x + orb1.radius * std::cos(this->rotation_angle - M_PI/2.0f)), static_cast<float>(orb1.position.y + orb1.radius * std::sin(this->rotation_angle- M_PI/2.0f)));
    glm::vec2 point_2 = glm::vec2(static_cast<float>(orb2.position.x - orb2.radius * std::cos(this->rotation_angle- M_PI/2.0f)), static_cast<float>(orb2.position.y - orb2.radius * std::sin(this->rotation_angle- M_PI/2.0f)));

    float a,b,c;

    if (std::isinf(slope)) {
//        printf("infinity\n");
        line_equations[0] = glm::vec3(1, 0, -point.x);
        line_equations[2] = glm::vec3(1, 0, -point_2.x);
        line_equations[1] = glm::vec3(0, 1, -point.y);
        line_equations[3] = glm::vec3(0, 1, -point_2.y);
    }
    else if (slope == 0.0f) {
//        printf("zero\n");
        line_equations[0] = glm::vec3(0, 1, -point.y);
        line_equations[2] = glm::vec3(0, 1, -point_2.y);
        line_equations[1] = glm::vec3(1, 0, -point.x);
        line_equations[3] = glm::vec3(1, 0, -point_2.x);
    }

    else {
        a = slope;
        b = -1;
        c = point.y - slope * point.x;
        line_equations[0] = glm::vec3(a, b, c);

        c = point_2.y - slope * point_2.x;
        line_equations[2] = glm::vec3(a, b, c);


        c = point.y - (-1.0f / slope) * point.x;
        line_equations[1] = glm::vec3(-1 / a, b, c);

        c = point_2.y - (-1.0f / slope) * point_2.x;
        line_equations[3] = glm::vec3(-1 / a, b, c);
    }

//    for(int i=0;i<4;i++) {q

}



void FireLine::draw_fireline(glm::mat4 VP) {
    this->orb1.draw(VP);
    this->orb2.draw(VP);
    if (!fire_extinguished)
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
        find_line_eqns();
    }
}


RectangleObject FireLine::convert_to_rectangle_object() {
    RectangleObject temp = {this->orb1.position, };
    temp.Position.y -= this->orb1.radius;
    temp.Size.x = this->distance_between_orbs*std::cos(this->rotation_angle) + 2*this->orb1.radius*std::sin(this->rotation_angle);
    temp.Size.y = 2 * this->orb1.radius*std::cos(this->rotation_angle) + this->distance_between_orbs*std::sin(this->rotation_angle);
    return temp;
}

bool FireLine::check_collision_with_point(glm::vec3 point) {
    if (fire_extinguished)
        return false;


    float val[4];
//    for(int i=0;i<4;i++) {
//        printf("line equation -> %f, %f, %f \n", line_equations[i].x, line_equations[i].y, line_equations[i].z );
//    }
    for (int i=0;i<4; i++) {
        val[i] = line_equations[i].x * point.x + line_equations[i].y * point.y + line_equations[i].z;
//        printf(" value -> %f  ",val[i]);
    }

    if (val[0] * val[2] < 0 && val[1] * val[3] < 0) {
//        printf("came true\n");
        return true;
    }
    else {
//        printf("came false\n");
        return false;
    }

}