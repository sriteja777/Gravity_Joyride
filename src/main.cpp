#include "main.h"
#include "timer.h"
#include "ball.h"
#include "IrregularPolygon.h"
#include "Player.h"
#include "Diamond.h"
#include "FireLine.h"
#include "FireBeam.h"
#include "Boomerang.h"
#include "EnhancedPlayer.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Ball ball2;
IrregularPolygon temp_pol;
IrregularPolygon temp_ground;
Player temp_player;
vector <Ball> coins;
Diamond power_diamond;
FireLine enemy1;
FireLine enemy1_2;
FireLine enemy_1_3;
FireBeam enemy_2;
FireLine enemy1_4;
Boomerang enemy3;
EnhancedPlayer player;

float screen_zoom = 0.1, screen_center_x = 0, screen_center_y = 0, map_length=300;
screen_t Screen = {-1,-1,-1,-1,-1,-1};
float camera_position = 0;
bool collided = false;
Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
//    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 eye (camera_position, 0, 5);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (camera_position, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
//    ball1.draw(VP);
//    ball2.draw(VP);
    player.draw(VP);
    power_diamond.draw(VP);
    for (int j=0; j<coins.size();j++) {
        if (coins[j].alive) {}
            coins[j].draw(VP);
    }
    temp_player.draw(VP);
    temp_ground.draw(VP);
    enemy1.draw_fireline(VP);
    enemy1_2.draw_fireline(VP);
    enemy_1_3.draw_fireline(VP);
    enemy1_4.draw_fireline(VP);
    enemy_2.draw_firebeam(VP);
    enemy3.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up    = glfwGetKey(window, GLFW_KEY_UP);
    int down  = glfwGetKey(window, GLFW_KEY_DOWN);
    if (left) {
        temp_player.move_left();
        player.move_left();
    }
    if (right) {
        temp_player.move_right();
        player.move_right();
    }
    if (up) {
        temp_player.jump();
        player.move_up();
    }
    if (down) {
        temp_player.move_down();
    }
}

bounding_box_t convertBoxType(Ball box) {
    bounding_box_t var;
    var.x = box.position.x;
    var.y = box.position.y;
    var.height = 2*box.radius;
    var.width = 2*box.radius;
    return var;
}

bool circles_overlap(float x1, float y1, float x2, float y2, float r1, float r2) {
    float correction_factor=3.0f;
    float distance = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
    if (distance + correction_factor < ((r1 + r2)*(r1+r2))) {
        return true;
    }
}


bool detect_coins_taken() {
    for (int i=0;i<coins.size();i++) {
        if (coins[i].alive)
        {
            if (circles_overlap(coins[i].position.x, coins[i].position.y, temp_player.position.x,
                                temp_player.position.y, coins[i].radius, temp_player.size)) {
                coins[i].alive = false;
                return true;
            }
        }
    }
    return false;
}

bool detect_powerups_taken() {
    return false;
}

void tick_elements(){
    if (!collided) {
        ball1.tick();
        ball2.tick();




        if (detect_collision(convertBoxType(ball1), convertBoxType(ball2))) {
            std::cout << "Detected" << std::endl;
            collided = true;
        }


    }
    else {
        ball1.fall();
        ball2.fall();
    }

    if (detect_coins_taken()) {
        cout << "taken coins" << endl;
    }
    if (detect_powerups_taken()) {
        cout << "powerups taken" << endl;
    }
    for (int i=0;i<coins.size();i++)
        coins[i].rotate();

    power_diamond.tick();
    temp_player.tick();
    enemy1.tick();
    enemy1_4.tick();
    enemy_2.tick();
    enemy3.tick();
    if (temp_player.position.y > Screen.dimensions.min_y + 12) {
        temp_player.time_of_falling += 1.0 / 60.0;
        float new_position = float(1.0 / 2.0 * 2.0 * temp_player.time_of_falling * temp_player.time_of_falling);
        if (temp_player.position.y - new_position < Screen.dimensions.min_y + 12) {
            temp_player.position.y = Screen.dimensions.min_y + 12;
            temp_player.time_of_falling = 0.0;

        }
        else {
            temp_player.position.y -= new_position;
        }
    }

//    if (player.position.y > Screen.dimensions.min_y + 12) {
//        player.time_of_falling += 1.0 / 60.0;
//        float new_position = float(1.0 / 2.0 * 2.0 * temp_player.time_of_falling * temp_player.time_of_falling);
//        if (player.position.y - new_position < Screen.dimensions.min_y + 12) {
//            player.position.y = Screen.dimensions.min_y + 12;
//            player.time_of_falling = 0.0;
//
//        }
//        else {
//            player.update_position_y(-new_position);
//        }
//    }


//    if (player.position.y > Screen.dimensions.min_y + 13) {
        if (player.net_vertical_acceleration < 0 && player.vertical_velocity > player.max_vertical_velocity) {
            player.vertical_velocity = player.max_vertical_velocity;
        }

        player.glow_fire = player.net_vertical_acceleration >= 0;

        float time_of_tick = 1.0f / 60.0f;
        float final_velocity;
//        printf("accel -> %f\n", player.net_vertical_acceleration);
        final_velocity = player.net_vertical_acceleration * time_of_tick;
//        printf("velocity > %f\n", player.vertical_velocity);
        float displacement;

        displacement = (player.vertical_velocity * time_of_tick) + (1.0f / 2.0f * player.net_vertical_acceleration * time_of_tick * time_of_tick);
            if (player.position.y + displacement > Screen.dimensions.min_y + 13) {
                player.vertical_velocity += final_velocity;
        player.update_position_y(displacement);
    }
    else {
        player.vertical_velocity = 0;

    }
    player.net_vertical_acceleration = -GRAVITY;



//    temp_player.tick();
//    camera_position += 0.11;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models


    GLfloat vertices_ground[] = {
            Screen.dimensions.min_x, -5.0f, 0.0f,
            Screen.dimensions.min_x, 5.0f, 0.0f,
            Screen.dimensions.min_x + map_length, 5.0f, 0.0f,
            Screen.dimensions.min_x + map_length, -5.0f, 0.0f,
    };

    player = EnhancedPlayer(glm::vec3(-20.0f, -25.0f, 0.0f));

    std::cout  << "Screen -> " << Screen.dimensions.min_y << std::endl;
    temp_ground = IrregularPolygon(4, vertices_ground, glm::vec3(0.0f, Screen.dimensions.min_y+5, 0.0f), COLOR_SADDLE_BROWN);



    ball1       = Ball(3, 0, COLOR_RED);
    ball2       = Ball(-3, 0, COLOR_GREEN);

    for (float j=11.0;j<Screen.dimensions.max_y;j+=3 ) {
        for (float i = -15; i < 15; i += 3) {
            coins.push_back(Ball(i, Screen.dimensions.min_y + j, COLOR_GOLD, glm::vec3(1.0f, 1.0f, 0.0f), i*j));
        }
    }
    GLfloat vertices[] = {
            0.0f, 0.0f, 0.0f,
            0.5f, -3.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            0.5f, 1.5f, 0.0f,
            0.0f, 1.0f, 0.0f,


    };

    GLfloat vertices_player[] = {
        -1.0f, 1.0f, 0.0f,
        -1.5f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, 2.0f, 0.0f,
        1.0f, 2.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.5f, -1.0f, 0.f,
        1.0f, 0.0f, 0.0f,
        1.0f, -2.0f, 0.0f,
        0.5f, -2.0f, 0.0f,
        0.5f, -1.0f, 0.0f,
        -0.5f, -1.0f, 0.0f,
        -0.5f, -2.0f, 0.0f,
        -1.0f, -2.0f, 0.0f,
    };




//    temp_pol    = IrregularPolygon(14, vertices_player, glm::vec3(20.0f, 0.0f, 0.0f), COLOR_RED);
    power_diamond = Diamond(10, glm::vec3(20.0f, 0.0f, 0.0f), COLOR_DIAMOND);
    temp_player = Player(glm::vec3(0.0f, 0.0f, 0.0f));
    enemy1 = FireLine(glm::vec3(30.0f, 30.0f, 0.0f), glm::vec3(30.0f, 20.0f, 0.0f), true, 0.02f);
    enemy1_2 = FireLine(glm::vec3(-30.0f, 30.0f, 0.0f), glm::vec3(-20.0f, 20.0f, 0.0f));
    enemy_1_3 = FireLine(glm::vec3(35.0f, 20.f, 0.0f), glm::vec3(45.0f, 20.0f, 0.0f));
    enemy_2 = FireBeam(glm::vec3(-45.0f, 10.0f, 0.0f), glm::vec3(45.0f, 10.0f, 0.0f), -30.0f, 30.0f);
    enemy1_4 = FireLine(glm::vec3(35.0f, 25.0f, 0.0f), glm::vec3(25.0f, 25.0f, 0.0f), true, 0.02f);
    enemy3 = Boomerang(glm::vec3(Screen.dimensions.max_x, 30.0f,0.0f));
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 1.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}
//GLFWvidmode* get_resolution() {
//    return glfwGetVideoMode(glfwGetPrimaryMonitor());
//
//}


void print_screen_variables() {
    cout << "width -> " <<  Screen.width << endl;
    cout << "height -> " <<  Screen.height << endl;
    cout << "min_x -> " <<  Screen.dimensions.min_x << endl;
    cout << "max_x -> " <<  Screen.dimensions.max_x << endl;
    cout << "min_y -> " <<  Screen.dimensions.min_y << endl;
    cout << "max_y -> " <<  Screen.dimensions.max_y << endl;
}

void set_screen_variables() {
    Screen.dimensions.max_y = screen_center_y + 4 / screen_zoom;
    Screen.dimensions.min_y = screen_center_y - 4 / screen_zoom;
    Screen.dimensions.min_x = screen_center_x - 6 / screen_zoom;
    Screen.dimensions.max_x  = screen_center_x + 6 / screen_zoom;
}

int main(int argc, char **argv) {
//    extern screen_t Screen;
    srand(time(0));

    cout << Screen.height << "  ok  " << Screen.width << endl;
    int width  = 600;
    int height = 600;

    window = initGLFW();

    set_screen_variables();
    initGL (window, width, height);
    print_screen_variables();

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    set_screen_variables();
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 6 / screen_zoom;
    float right  = screen_center_x + 6 / screen_zoom;
    Screen.dimensions.min_x = left;
    Screen.dimensions.max_x = right;
    Screen.dimensions.max_y = top;
    Screen.dimensions.min_y = bottom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
