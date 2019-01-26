#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "main.h"
#include "WaterBall.h"
#include "EnhancedPlayer.h"

extern std::vector<WaterBall> water_balls;
extern EnhancedPlayer player;
extern int camera_orientation;

bool   cannon_keyboard_input = true;
bool   drag_pan = false, old_cki;
double drag_oldx = -1, drag_oldy = -1;

using namespace std;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
//         switch (key) {
//         case GLFW_KEY_SPACE:
//             water_balls.push_back(WaterBall(glm::vec3(player.position.x+2.0f, player.position.y, 0.0f)));
//         rectangle_rot_status = !rectangle_rot_status;
//         break;
        // case GLFW_KEY_P:
        // triangle_rot_status = !triangle_rot_status;
        // break;
        // case GLFW_KEY_X:
        //// do something ..
        // break;
        // default:
        // break;
//         }
    } else if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_SPACE:
                water_balls.push_back(WaterBall(glm::vec3(player.position.x+2.0f, player.position.y, 0.0f), 1.0f, glm::vec2(0.0f, -player.vertical_velocity), player.moving_left));
                break;
            case GLFW_KEY_ESCAPE:
            quit(window);
            break;
            case GLFW_KEY_R:
                camera_orientation = 1;
                break;
        default:
            break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar(GLFWwindow *window, unsigned int key) {
    printf("q pressed");
    switch (key) {
        case GLFW_KEY_UP:

        case 'q':
            quit(window);
            break;

        case ' ':

        default:
            break;
    }
}

/* Executed when a mouse button is pressed/released */
void mouseButton(GLFWwindow *window, int button, int action, int mods) {
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
        if (action == GLFW_PRESS) {
            // Do something
            printf("mouse left");
            return;
        } else if (action == GLFW_RELEASE) {
            // Do something
        }
        break;
    // case GLFW_MOUSE_BUTTON_RIGHT:
    // if (action == GLFW_RELEASE) {
    // rectangle_rot_dir *= -1;
    // }
    // break;
    default:
        break;
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    // Do something
    printf("scrolling, %lf %lf",xoffset,yoffset );

    if (yoffset < 0)  {
        if (screen_zoom  > 0.05) screen_zoom -= 0.01;
    }
    else if (yoffset > 0) {
        if (screen_zoom < 0.15) screen_zoom += 0.01;
    }
    reset_screen();
}
