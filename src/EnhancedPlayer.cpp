//
// Created by sriteja on 19/1/19.
//

#include "EnhancedPlayer.h"


EnhancedPlayer::EnhancedPlayer(glm::vec3 position) {


    this->position = position;
    this->speed = 0.3f;
    this->rotation_speed = 0.2f;
    this->leg_rotation_speed = 0.1f;
    this->hand_going_up = true;
    this->moving_left = false;
    this->moving_right = false;
//    this->time_of_nitro = 0.0f;
//    this->time_of_falling = 0.0f;
    this->upward_acceleration = 50.0f;
    this->downward_acceleration = 1.0f;
    this->max_vertical_velocity = 20.0f;
    this->min_vertical_velocity = -20.0f;
    this->vertical_velocity = 0.0f;
    this->horizontal_velocity = 0.0f;
    this->horizontal_deceleration = 0.0f;
    this->horizontal_acceleration = 0.0f;
    this->net_vertical_acceleration = -GRAVITY;
    moving_up = false;
    glow_fire = false;


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



    GLfloat coordinates_jetpack[] = {
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,

    };

    jet_box = IrregularPolygon(4, coordinates_jetpack, glm::vec3(this->body.position.x -1.0f, this->body.position.y, 0.0f), COLOR_MAROON);

    GLfloat  coordinates_fire[] = {
            0.1f, 0.0f, 0.0f,
            -0.1f, 0.0f, 0.0f,
            0.0f, -2.0f, 0.0f
    };
    for (int i=0;i<5;i++) {
        fire[i] = IrregularPolygon(3, coordinates_fire, glm::vec3(this->jet_box.position.x - 0.5f + +0.1f + i*0.2f, this->jet_box.position.y -0.5f, 0.0f), COLOR_DARK_ORANGE);
    }

//    fire[0] = IrregularPolygon(3, coordinates_fire, glm::vec3(this->jet_box.position.x, this->jet_box.position.y - 0.5f, 0.0f), COLOR_RED);


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
    this->jet_box.draw(VP);
    if (glow_fire) {
        for (int i = 0; i < 5; i++)
            this->fire[i].draw(VP);
    }
    this->right_leg.draw(VP);
    this->right_hand.draw(VP, moving_left);

}


void EnhancedPlayer::move_right() {
    moving_right = true;
    if (moving_left || moving_up) {
        this->right_hand.rotation = -1.57f;
        this->left_hand.rotation = -1.57f;
        this->right_leg.rotation = 0.0f;
        this->left_leg.rotation = 0.0f;
        if (moving_left) {
            this->jet_box.position.x -= 2.0f;
            for (int i = 0; i < 5; i++)
                this->fire[i].position.x -= 2.0f;
        }
        moving_left = false;
        moving_up = false;
    }

    this->update_position_x(this->speed);

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

}




void EnhancedPlayer::move_left() {
    if (!moving_left || moving_up) {
        this->right_hand.rotation = 1.57f;
        this->left_hand.rotation = 1.57f;
        this->right_leg.rotation = 0.0f;
        this->left_leg.rotation = 0.0f;
        if (!moving_left) {
            this->jet_box.position.x += 2.0f;
            for (int i = 0; i < 5; i++)
                this->fire[i].position.x += 2.0f;
        }
        moving_left = true;
        moving_up = false;
    }

    this->update_position_x(-this->speed);

    if (hand_going_up) {

        if (right_hand.rotation >3.0f) {
            hand_going_up = false;
            right_hand.rotation -= rotation_speed;
            left_hand.rotation += rotation_speed;
            left_leg.rotation -= leg_rotation_speed;
            right_leg.rotation += leg_rotation_speed;
            printf("came here");
        } else {
            right_hand.rotation += rotation_speed;
            left_hand.rotation -= rotation_speed;
            left_leg.rotation += leg_rotation_speed;
            right_leg.rotation -= leg_rotation_speed;
        }
    } else {
        if (right_hand.rotation < 0.0f) {
            hand_going_up = true;
            right_hand.rotation += rotation_speed;
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

void EnhancedPlayer::move_up() {
    moving_up = true;
    if (moving_left) {
        this->right_hand.rotation = -0.50f;
        this->left_hand.rotation = -0.50f;
        this->right_leg.rotation = +0.5f;
        this->left_leg.rotation = +0.5f;
    }
    else if (moving_right) {
        this->right_hand.rotation = +0.50f;
        this->left_hand.rotation = +0.50f;
        this->right_leg.rotation = -0.5f;
        this->left_leg.rotation = -0.5f;
    }
//    time_of_falling = 0.0f;
    float time_of_tick = 1.0f / 60.0f;

    if (vertical_velocity < this->min_vertical_velocity)
        this->vertical_velocity = this->min_vertical_velocity;

    this->net_vertical_acceleration = this->upward_acceleration - GRAVITY;
//    float displacement;
//    displacement = (this->vertical_velocity * time_of_tick) + (1.0f/2.0f * this->upward_acceleration*time_of_tick*time_of_tick);
//    printf("velocity -> %f\n",this->vertical_velocity );
//    if (vertical_velocity > 0)
//        update_position_y(displacement);

//    update_position_y(this->speed);


}


void EnhancedPlayer::update_position_x(float x) {
    this->head.position.x += x;
    this->body.position.x += x;
    this->right_hand.position.x += x;
    this->left_hand.position.x += x;
    this->left_leg.position.x += x;
    this->right_leg.position.x += x;
    this->jet_box.position.x += x;
    for (int i = 0; i < 5; i++)
        this->fire[i].position.x += x;

    this->position.x = this->body.position.x;

}

void EnhancedPlayer::update_position_y(float y) {
    this->head.position.y += y;
    this->body.position.y += y;
    this->right_hand.position.y += y;
    this->left_hand.position.y += y;
    this->left_leg.position.y += y;
    this->right_leg.position.y += y;
    this->jet_box.position.y += y;
    for (int i = 0; i < 5; i++)
        this->fire[i].position.y += y;
    this->position.y = this->body.position.y;
}

void EnhancedPlayer::move_down() {

}



