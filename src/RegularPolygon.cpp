//
// Created by sriteja on 13/1/19.
//

#include "main.h"
#include "RegularPolygon.h"


RegularPolygon::RegularPolygon(int num_of_sides, glm::vec3 center, float radius) {

    this->radius = radius;
    this->center = center;
    this->num_of_sides = num_of_sides;
}

void RegularPolygon::construct() {

}