#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color, glm::vec3 rotation_axis = glm::vec3(0.0f, 0.f, 1.0f), float initial_rotation_angle=0.0f, float radius=1.0f, float circle_angle= 360.0f, int points = 0);
    glm::vec3 position;
    float rotation;
    glm::vec3 rotation_axis;
    int points;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void fall();
    void rotate();

    bool alive;
    double speed;
    float radius;
    void construct(int n, float circle_angle = 360.0f);
//    double speed_y;
private:
    GLfloat vertex_data[10000];
    VAO *object;
};

#endif // BALL_H
