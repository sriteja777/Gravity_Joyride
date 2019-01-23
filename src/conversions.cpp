//
// Created by sriteja on 23/1/19.
//

#include "conversions.h"


CircleObject convert_ball_circle_object(Ball one){
    CircleObject temp = {one.position, one.radius};
//    temp->Position = one.position;
//    two->Radius = one.radius;
    return temp;

}

RectangleObject convert_player_rectangle(EnhancedPlayer one) {
    RectangleObject temp = {one.body.position};
    temp.Position.y -= 2;

    temp.Size.x = one.size;
    temp.Size.y = one.height;
    return temp;
}


