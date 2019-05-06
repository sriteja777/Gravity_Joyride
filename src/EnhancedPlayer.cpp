//
// Created by sriteja on 19/1/19.
//

#include "EnhancedPlayer.h"
#include "Borders.h"
#include "FireBeam.h"

extern Borders ground;
extern Borders slab;
extern float camera_position;
extern std::vector <FireBeam> fire_beams;

EnhancedPlayer::EnhancedPlayer(glm::vec3 position) {


    this->position = position;
    this->speed = 0.3f;
    this->rotation_speed = 0.2f;
    this->leg_rotation_speed = 0.1f;
    this->hand_going_up = true;
    this->moving_left = false;
    this->moving_right = false;
    this->upward_acceleration = 50.0f;
    this->downward_acceleration = 1.0f;
    this->max_vertical_velocity = 20.0f;
    this->min_vertical_velocity = -20.0f;
    this->velocity.y = 0.0f;
    this->velocity.x = 0.0f;
    this->horizontal_deceleration = 0.0f;
    this->horizontal_acceleration = 0.0f;
    this->magnet_accelerations.x = 0.0f;
    this->magnet_accelerations.y = 0.0f;


    this->net_acceleration.x = 0.0f;
    this->net_acceleration.y = -GRAVITY;


    moving_up = false;
    glow_fire = false;


    head = Ball(this->position.x, this->position.y, COLOR_SKIN, glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, 0.9f);
//    GLfloat coor[] = {
//            0.5f , 0.5f, 0.f,
//            1.5f, 0.0f, 0.0f,
//            0.5f, -1.0f, 0.0f
//            -0.25f, -1.0f, 0.0f,
//            -0.25f, 0.0f, 0.f,
//            -1.0f, 0.75f, 0.f
//    };

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

    leg_length = 2.0f;
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
    left_hand = IrregularPolygon(6, hand_coor, glm::vec3(this->body.position.x, this->body.position.y, 0.0f), COLOR_SKIN, -1.57f);

    right_hand = IrregularPolygon(6, hand_coor, glm::vec3(this->body.position.x, this->body.position.y, 0.0f), COLOR_SKIN, -1.57f);

    this->height = 2.0f + 2.4f + 1.5f;
//    this->size = (1.8f + 1.6f)/2.0f;
    this->size = 1.8f;
    update_border_postitions();
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
//    this->velocity.x = 1.0f;
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
//    this->velocity.x = -1.0f;
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

    if (velocity.y < this->min_vertical_velocity)
        this->velocity.y = this->min_vertical_velocity;

    this->net_acceleration.y = this->upward_acceleration - GRAVITY;
//    float displacement;
//    displacement = (this->velocity.y * time_of_tick) + (1.0f/2.0f * this->upward_acceleration*time_of_tick*time_of_tick);
//    printf("velocity -> %f\n",this->velocity.y );
//    if (velocity.y > 0)
//        update_position_y(displacement);

//    update_position_y(this->speed);


}

void EnhancedPlayer::update_border_postitions() {
    border_positions[0] = glm::vec3(head.position.x + head.radius, head.position.y, 0.0f);                               /// head right
    border_positions[1] = glm::vec3(head.position.x - head.radius, head.position.y, 0.0f);                               /// head left
    border_positions[2] = glm::vec3(head.position.x, head.position.y + head.radius, 0.0f);                               /// head up

    float cos_x = std::cos(right_hand.rotation);
    float sin_x = std::cos(right_hand.rotation);

    border_positions[3] = glm::vec3(right_hand.position.x + 2.1*cos_x + 0.4*sin_x, right_hand.position.y + 2.1*sin_x + 0.4*cos_x, 0.0f);           /// right hand

    cos_x = std::cos(left_hand.rotation);
    sin_x = std::cos(left_hand.rotation);

    border_positions[4] = glm::vec3(left_hand.position.x + 2.1*cos_x + 0.4*sin_x, left_hand.position.y + 2.1*sin_x + 0.4*cos_x, 0.0f);            /// left hand

    border_positions[5] = glm::vec3(left_leg.position.x, left_leg.position.y - leg_length, 0.0f);                                        /// left leg

    border_positions[6] = glm::vec3(body.position.x + this->size / 2.0f, body.position.y, 0.0f);                         //// body left
    border_positions[7] = glm::vec3(body.position.x - this->size / 2.0f, body.position.y, 0.0f);                         //// body right
}

void EnhancedPlayer::update_position_x(float x) {

//    printf("borders -> %f, %f, %f, %f", border_positions[1].x, border_positions[3].x, ground.min_x, ground.min_y);
    if (border_positions[0].x + x > ground.max_x)
        return;
    if (border_positions[1].x + x < ground.min_x)
        return;
//    exit(0);
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
//    printf("screen -> %f %f\n", Screen.dimensions.min_x, ground.min_x);

    if (camera_position + x >=0 && this->position.x > -20)
        camera_position += x;

    if (!fire_beams.empty()) {
        fire_beams[0].change_x_position(x);
    }

    update_border_postitions();

}

void EnhancedPlayer::update_position_y(float y) {
    if (border_positions[2].y + y > slab.min_y || border_positions[5].y + y < ground.max_y) {
        this->velocity.y = 0;
        return;
    }

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
    update_border_postitions();
}

void EnhancedPlayer::move_down() {

}

void EnhancedPlayer::move_in_circle(float radius) {
    float teta = 180.0f;
//    while (teta > 0) {
//        this->update_position_x(400 + radius * cos(teta * M_PI / 180.0f));
//        this->update_position_y(400 + radius*sin(teta * M_PI / 180));
//
//        teta -= 0.000001;
//
//
//    }
}


