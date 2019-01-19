//
// Created by sriteja on 19/1/19.
//

#include "EnhancedPlayer.h"


EnhancedPlayer::EnhancedPlayer(glm::vec3 position) {


    this->position = position;
    this->speed = 0.2f;
    this->rotation_speed = 0.1f;
    this->leg_rotation_speed = 0.05f;
    this->hand_going_up = true;
    this->moving_left = false;


    head = Ball(this->position.x, this->position.y, COLOR_SKIN, glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, 0.9f);
    GLfloat coor[] = {
            0.5f , 0.5f, 0.f,
            1.5f, 0.0f, 0.0f,
            0.5f, -1.0f, 0.0f
            -0.25f, -1.0f, 0.0f,
            -0.25f, 0.0f, 0.f,
            -1.0f, 0.75f, 0.f
    };




    GLfloat coo[] = {
        0.8f, 1.2f, 0.0f,
        -0.8f, 1.2f, 0.0f,
        -0.8f, -1.2f, 0.0f,
        0.8f, -1.2f, 0.0f,
    };


    body = IrregularPolygon(4, coo, glm::vec3(this->head.position.x, this->head.position.y-this->head.radius-0.8f, 0.0f), COLOR_NAVY);

    GLfloat leg_coor[] = {
            0.25f, 0.0f, 0.0f,
            -0.25f, 0.0f, 0.0f,
            -0.25f, -2.0f, 0.0f,
            0.25f, -2.0f, 0.0f
    };
    left_leg = IrregularPolygon(4, leg_coor, glm::vec3(this->body.position.x, this->body.position.y - 1.0f, 0.0f), COLOR_CHOCOLATE, 0.0f);
    right_leg = IrregularPolygon(4, leg_coor, glm::vec3(this->body.position.x, this->body.position.y - 1.0f, 0.0f), COLOR_CHOCOLATE, 0.0f);

    GLfloat hand_coor[] = {
            0.0f + 0.9f, 0.5f - 0.4f, 0.0f,
            1.0f + 0.9f, 1.0f - 0.4f, 0.0f,
            1.2f + 0.9f, 0.8f - 0.4f, 0.f,
            0.0f + 0.9f, -0.25f - 0.4f, 0.f,
            -1.0f + 0.9f, 0.0f - 0.4f, 0.0f,
            -0.8f + 0.9f, 0.8f - 0.4f, 0.0f,
    };
    left_hand = IrregularPolygon(6, hand_coor, glm::vec3(this->body.position.x+1.0f -1.0f, this->body.position.y, 0.0f), COLOR_SKIN, -1.57f);

    right_hand = IrregularPolygon(6, hand_coor, glm::vec3(this->body.position.x+1.0f -1.0f, this->body.position.y, 0.0f), COLOR_SKIN, -1.57f);








}


void EnhancedPlayer::draw(glm::mat4 VP) {
    this->head.draw(VP);
    this->left_hand.draw(VP, moving_left);
    this->body.draw(VP);
    this->left_leg.draw(VP);
    this->right_leg.draw(VP);
    this->right_hand.draw(VP, moving_left);

}


void EnhancedPlayer::move_right() {
    if (moving_left) {
        this->right_hand.rotation = -1.57f;
        this->left_hand.rotation = -1.57f;
        this->right_leg.rotation = 0.0f;
        this->left_leg.rotation = 0.0f;
        moving_left = false;
    }
    this->head.position.x += this->speed;
    this->body.position.x += this->speed;
    this->right_hand.position.x += this->speed;
    this->left_hand.position.x += this->speed;
    this->left_leg.position.x += this->speed;
    this->right_leg.position.x += this->speed;
    this->hand_rotation_angle += rotation_speed;


    if (hand_going_up) {

        if (right_hand.rotation >-0.0f) {
            hand_going_up = false;
            right_hand.rotation -= rotation_speed;
            left_hand.rotation += rotation_speed;
            left_leg.rotation -= leg_rotation_speed;
            right_leg.rotation += leg_rotation_speed;
            printf("came here");
        } else {
            this->right_hand.rotation += rotation_speed;
            left_hand.rotation -= rotation_speed;
            left_leg.rotation += leg_rotation_speed;
            right_leg.rotation -= leg_rotation_speed;
        }
    } else {
        if (right_hand.rotation < -3.0f) {
            hand_going_up = true;
            this->right_hand.rotation += rotation_speed;
            left_hand.rotation -= rotation_speed;
            left_leg.rotation += leg_rotation_speed;
            right_leg.rotation -= leg_rotation_speed;
        } else {
            this->right_hand.rotation -= rotation_speed;
            left_hand.rotation += rotation_speed;
            left_leg.rotation -= leg_rotation_speed;
            right_leg.rotation += leg_rotation_speed;
        }
    }


//    float relative_x =  this->distance_between_orbs/2 * std::cos(this->hand_rotation_angle);
//    float relative_y = this->distance_between_orbs/2 * std::sin(this->hand_rotation_angle);
//
//    this->orb1.set_position(this->connector.position.x + relative_x, this->connector.position.y + relative_y);
//    this->orb2.set_position(this->connector.position.x - relative_x, this->connector.position.y - relative_y);
}




void EnhancedPlayer::move_left() {
    if (!moving_left) {
        this->right_hand.rotation = 1.57f;
        this->left_hand.rotation = 1.57f;
        this->right_leg.rotation = 0.0f;
        this->left_leg.rotation = 0.0f;
        moving_left = true;
    }


    this->head.position.x -= this->speed;
    this->body.position.x -= this->speed;
    this->right_hand.position.x -= this->speed;
    this->left_hand.position.x -= this->speed;
    this->left_leg.position.x -= this->speed;
    this->right_leg.position.x -= this->speed;
//    this->right_hand.rotation -= rotation_speed;

    if (hand_going_up) {

        if (right_hand.rotation >3.0f) {
            hand_going_up = false;
            right_hand.rotation -= rotation_speed;
            left_hand.rotation += rotation_speed;
            left_leg.rotation -= leg_rotation_speed;
            right_leg.rotation += leg_rotation_speed;
            printf("came here");
        } else {
            this->right_hand.rotation += rotation_speed;
            left_hand.rotation -= rotation_speed;
            left_leg.rotation += leg_rotation_speed;
            right_leg.rotation -= leg_rotation_speed;
        }
    } else {
        if (right_hand.rotation < 0.0f) {
            hand_going_up = true;
            this->right_hand.rotation += rotation_speed;
            left_hand.rotation -= rotation_speed;
            left_leg.rotation += leg_rotation_speed;
            right_leg.rotation -= leg_rotation_speed;
        } else {
            this->right_hand.rotation -= rotation_speed;
            left_hand.rotation += rotation_speed;
            left_leg.rotation -= leg_rotation_speed;
            right_leg.rotation += leg_rotation_speed;
        }
    }

}
