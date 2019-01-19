//
// Created by sriteja on 13/1/19.
//
#include "main.h"
#ifndef GRAPHICS_ASGN1_IRREGULARPOLYGON_H
#define GRAPHICS_ASGN1_IRREGULARPOLYGON_H




class IrregularPolygon{
public:
    IrregularPolygon() {}
    IrregularPolygon(int num_of_sides, GLfloat *coordinates, glm::vec3 position, color_t color,
                     float rotation_angle=0.0f, glm::vec3 scale_values=glm::vec3(1.0f), glm::vec3 rotation_axis = glm::vec3(0.0f, 0.0f, 1.0f));
    int num_of_sides;
    color_t color;
    glm::vec3 position;
    glm::vec3 vertices[1000];
    float rotation;
    glm::vec3 rotation_axis;
    void construct(glm::vec3 vertices[]);
    void convertCoordinatesToVertices(GLfloat *coordinates, int n, glm::vec3 *vertices);
    void draw(glm::mat4 VP, bool reflect= false);
    glm::vec3 scale;
private:
    glm::vec3 centroid;
    void copyVectorToArray(glm::vec3 vect, GLfloat *arr, int index);
    void findCentroid();
    void print_array(GLfloat *arr);
    GLfloat vertex_data[1000];
    VAO *object;


};


#endif //GRAPHICS_ASGN1_IRREGULARPOLYGON_H
