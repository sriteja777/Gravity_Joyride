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
#include "conversions.h"
#include "WaterBall.h"
#include "Magnet.h"
#include "EscapeLoop.h"
#include "Borders.h"
#include "ScreenInversionObject.h"


using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

// Declare Objects

IrregularPolygon groun;
Borders ground;
Borders slab;

Diamond power_diamond;
ScreenInversionObject inv_obj;

FireLine enemy1;
FireLine enemy1_2;
FireLine enemy_horizontal;
FireBeam enemy_2;
FireLine enemy1_4;
FireLine enemy_vertical;
Boomerang enemy3;
EnhancedPlayer player;
vector <WaterBall> water_balls;
Magnet mag;
EscapeLoop loop;

vector <Ball> coins;
vector<FireLine> fire_lines;
vector<FireBeam> fire_beams;



bool created = false;
int camera_orientation = 1;
float level_1_map_length = 1000.0f;
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
    glm::vec3 up (0, camera_orientation, 0);

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
    ground.draw(VP);
    slab.draw(VP);
    if (inv_obj.alive)
        inv_obj.draw(VP);

    for (int i=0;i<fire_lines.size();i++) {
        fire_lines[i].draw_fireline(VP);
    }

    for (int i=0;i<fire_beams.size();i++) {
        fire_beams[i].draw_firebeam(VP);
    }

//    mag.draw(VP);

//    loop.draw(VP);
    player.draw(VP);
    if (power_diamond.alive)
        power_diamond.draw(VP);
    for (int j=0; j<coins.size();j++) {
        coins[j].draw(VP);
    }


//    enemy1.draw_fireline(VP);
//    enemy1_2.draw_fireline(VP);
//    enemy_horizontal.draw_fireline(VP);
//    enemy1_4.draw_fireline(VP);
//    enemy_vertical.draw_fireline(VP);
//    enemy_2.draw_firebeam(VP);
//    enemy3.draw(VP);
    for (int i=0;i<water_balls.size();i++) {
        water_balls[i].draw(VP);
    }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up    = glfwGetKey(window, GLFW_KEY_UP);
    int down  = glfwGetKey(window, GLFW_KEY_DOWN);

    if (left) {
        player.move_left();
    }
    if (right) {
        player.move_right();
    }
    if (up) {
        player.move_up();
    }
    if (down) {

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


//bool detect_coins_taken() {
//    for (int i=0;i<coins.size();i++) {
//        if (coins[i].alive)
//        {
//            if (circles_overlap(coins[i].position.x, coins[i].position.y, temp_player.position.x,
//                                temp_player.position.y, coins[i].radius, temp_player.size)) {
//                coins[i].alive = false;
//                return true;
//            }
//        }
//    }
//    return false;
//}

bool detect_powerups_taken() {
    return false;
}




void tick_elements(){


//    if (detect_coins_taken()) {
////        cout << "taken coins" << endl;
//    }
    vector<Ball>::iterator coin;
    vector<FireLine>::iterator fire_line;
    vector<FireBeam>::iterator fire_beam;
    vector<WaterBall>::iterator water_ball;

    RectangleObject player_rectangle_obj = convert_player_rectangle(player);
    CircleObject temp_circle;
    LineObject temp_line;
    RectangleObject temp_rectangle;


    temp_circle = enemy3.convert_circle_object();
    temp_line = enemy3.convert_line_object();
//    if (CheckCollision(player_rectangle_obj, temp_line)) {
//        player.update_position_x(-10);
//        printf("Boomerang collided");
//    }

    // Check collision of coins with player
    for (coin = coins.begin(); coin < coins.end(); coin++) {

        temp_circle = convert_ball_circle_object(*coin);
        if (CheckCollision(temp_circle, player_rectangle_obj)) {
//            (*coin).alive = false;
            coins.erase(coin);
            printf("Collided with coins\n");
        }
    }


    // Check collision with fire lines and make ticks
    for( fire_line = fire_lines.begin(); fire_line < fire_lines.end(); fire_line ++ ) {

        // tick fire line
        (*fire_line).tick();

        //Check collision with player
        for (int i=0;i<6;i++) {
            if ((*fire_line).check_collision_with_point(player.border_positions[i])) {
                printf(" player collided with fireline\n");
                player.update_position_x(-10);
            }
//            printf("%f %f \n", player.border_positions[i].x, player.border_positions[i].y);
        }

        // Check collision of  fire lines  with water balls
        for (water_ball = water_balls.begin(); water_ball < water_balls.end(); water_ball ++) {
            for (int i = 0; i < 4; i++) {
                if ((*fire_line).check_collision_with_point((*water_ball).border_positions[i])) {
                    printf("water ball collided with fire line\n");
                    water_balls.erase(water_ball);
                    (*fire_line).fire_extinguished = true;
                }

            }
        }
    }

    for( fire_beam = fire_beams.begin(); fire_beam < fire_beams.end(); fire_beam++) {
        (*fire_beam).tick();
        temp_rectangle = (*fire_beam).convert_rectangle_object(1);
        if (CheckCollision(temp_rectangle, player_rectangle_obj)) {
            quit(window);
        }
        temp_rectangle = (*fire_beam).convert_rectangle_object(2);
        if (CheckCollision(temp_rectangle, player_rectangle_obj)) {
            quit(window);
        }
    }



    if (player.position.x > 150 && !created) {
        fire_beams.push_back(FireBeam(glm::vec3(120.0f, 10.0f, 0.0f), glm::vec3(220.0f, 10.0f, 0.0f), ground.max_y, 10, 15));
        created = true;
    }

    if (inv_obj.alive) {
        inv_obj.tick();
        temp_circle = inv_obj.convert_to_circle();
        if (CheckCollision(temp_circle, player_rectangle_obj)) {
            camera_orientation = -1;
            inv_obj.alive = false;
        }
    }
    if (power_diamond.alive) {
        power_diamond.tick();
        temp_circle = power_diamond.convert_to_circle();
        if (CheckCollision(temp_circle, player_rectangle_obj)) {
            power_diamond.alive = false;
        }
    }


//    temp_rectangle = enemy_horizontal.convert_to_rectangle_object();

//    for (vector<WaterBall>::iterator water_ball = water_balls.begin();water_ball < water_balls.end(); water_ball++) {
//        if (enemy_horizontal.check_collision_with_point((*water_ball).water_ball.position)) {
//            water_balls.erase(water_ball);
//        }
//    }

    //
//
//    if (CheckCollision(player_rectangle_obj, temp_rectangle)) {
//        player.update_position_x(-10);
////        player.update_position_y(-10);
//        printf("collided with enemies\n");
//    }
//    temp_rectangle =enemy1_2.convert_to_rectangle_object();
//    if (CheckCollision(player_rectangle_obj, temp_rectangle)) {
//        player.update_position_x(-10);
//        player.update_position_y(-10);
//        printf("collided with enemies\n");
//    }
//    temp_rectangle =enemy_vertical.convert_to_rectangle_object();
//    if (CheckCollision(player_rectangle_obj, temp_rectangle)) {
//        player.update_position_x(-10);
//        player.update_position_y(-10);
//        printf("collided with enemies\n");
//    }

//    temp_rectangle = enemy_2.convert_rectangle_object();

    if (CheckCollision(player_rectangle_obj, temp_rectangle)) {
//        player.update_position_x(-20);
    }

//    if (enemy1_2.check_collision_with_point(player.head.position) ||
//        enemy1_2.check_collision_with_point(player.body.position) ||
//        enemy1_2.check_collision_with_point(player.left_hand.position) ||
//        enemy1_2.check_collision_with_point(player.right_leg.position)
//        ) {
//        player.update_position_x(-10);
//        player.update_position_y(-10);
//    }
//
//    if (enemy1_4.check_collision_with_point(player.head.position) ||
//        enemy1_4.check_collision_with_point(player.body.position) ||
//        enemy1_4.check_collision_with_point(player.left_hand.position) ||
//        enemy1_4.check_collision_with_point(player.right_leg.position)
//            ) {
//        player.update_position_x(-10);
//        player.update_position_y(-10);
//    }
//    if (enemy1.check_collision_with_point(player.head.position) ||
//        enemy1.check_collision_with_point(player.body.position) ||
//        enemy1.check_collision_with_point(player.left_hand.position) ||
//        enemy1.check_collision_with_point(player.right_leg.position)
//            ) {
//        player.update_position_x(-10);
//        player.update_position_y(-10);
//    }
//
//    if (enemy_horizontal.check_collision_with_point(player.head.position) ||
//        enemy_horizontal.check_collision_with_point(player.body.position) ||
//        enemy_horizontal.check_collision_with_point(player.left_hand.position) ||
//        enemy_horizontal.check_collision_with_point(player.right_leg.position)
//            ) {
//        player.update_position_x(-10);
//        player.update_position_y(10);
//    }
//    temp_circle = mag.convert_circle();
//    if (CheckCollision(temp_circle, player_rectangle_obj)) {
//        player.update_position_x(10.0f);
//    }
//
//
//    if (detect_powerups_taken()) {
//        cout << "powerups taken" << endl;
//    }
    for (int i=0;i<coins.size();i++)
        coins[i].rotate();


//    temp_player.tick();
    enemy1.tick();
    enemy1_4.tick();

    enemy_2.tick();
    enemy3.tick();
//    if (temp_player.position.y > Screen.dimensions.min_y + 12) {
//        temp_player.time_of_falling += 1.0 / 60.0;
//        float new_position = float(1.0 / 2.0 * 2.0 * temp_player.time_of_falling * temp_player.time_of_falling);
//        if (temp_player.position.y - new_position < Screen.dimensions.min_y + 12) {
//            temp_player.position.y = Screen.dimensions.min_y + 12;
//            temp_player.time_of_falling = 0.0;
//
//        }
//        else {
//            temp_player.position.y -= new_position;
//        }
//    }

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
        if (player.net_acceleration.y < 0 && player.velocity.y > player.max_vertical_velocity) {
            player.velocity.y = player.max_vertical_velocity;
        }

        player.glow_fire = player.net_acceleration.y >= 0;

        float time_of_tick = 1.0f / 60.0f;
        float final_velocity;
//        printf("accel -> %f\n", player.net_acceleration.y);
        final_velocity = player.net_acceleration.y * time_of_tick;
//        printf("velocity > %f\n", player.velocity.y);
        float displacement;


        displacement = (player.velocity.y * time_of_tick) + (1.0f / 2.0f * player.net_acceleration.y * time_of_tick * time_of_tick);
            if (player.position.y + displacement > ground.min_y + 3) {
                player.velocity.y += final_velocity;
        player.update_position_y(displacement);
    }
    else {
        player.velocity.y = 0;

    }
    player.net_acceleration.y = -GRAVITY;

    displacement = player.velocity.x * time_of_tick + 1.0f / 2.0f *player.net_acceleration.x*time_of_tick*time_of_tick;
    player.update_position_x(displacement);
    for (int i=0;i<water_balls.size();i++) {
        water_balls[i].tick();
    }

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
    ground = Borders(level_1_map_length, 10, glm::vec3(Screen.dimensions.min_x, Screen.dimensions.min_y, 0.0f), COLOR_SADDLE_BROWN);
    slab = Borders(level_1_map_length, 10, glm::vec3(Screen.dimensions.min_x, Screen.dimensions.max_y - 10, 0.0f), COLOR_SADDLE_BROWN);
    mag = Magnet(glm::vec3(10.0f, 10.0f, 0.0f));
    for (float j=11.0;j<Screen.dimensions.max_y;j+=3 ) {
        for (float i = -15; i < 15; i += 3) {
            if (rand() % 2)
                coins.push_back(Ball(i, ground.min_y + j, COLOR_GOLD, glm::vec3(1.0f, 1.0f, 0.0f), i*j, 1.0f, 360.0f, 1));
            else
                coins.push_back(Ball(i, ground.min_y + j, COLOR_ORCHID, glm::vec3(1.0f, 1.0f, 0.0f), i*j, 1.0f, 360.0f, 2));
        }
    }

    fire_lines.push_back(FireLine(glm::vec3(40, ground.max_y+5, 0.0f), glm::vec3(50, ground.max_y+5, 0.0f)));
    fire_lines.push_back(FireLine(glm::vec3(50, ground.max_y+5, 0.0f), glm::vec3(50, ground.max_y+15, 0.0f)));
    fire_lines.push_back(FireLine(glm::vec3(40, ground.max_y+15, 0.0f), glm::vec3(50, ground.max_y+15, 0.0f)));
    fire_lines.push_back(FireLine(glm::vec3(40, ground.max_y+5, 0.0f), glm::vec3(40, ground.max_y+15, 0.0f)));

    coins.push_back(Ball(45, ground.max_y + 10, COLOR_DARK_ORANGE, glm::vec3(0.0f, 1.0f, 0.0f), 0.0, 1.0f, 360.0f, 5));

    fire_lines.push_back(FireLine(glm::vec3(70.0f, -5.0f, 0.0f), glm::vec3(70.0f, 5.0f, 0.0f), true, 0.02f));
    fire_lines.push_back(FireLine(glm::vec3(65.0f, 0.0f, 0.0f), glm::vec3(75.0f, 0.0f, 0.0f), true, 0.02f));

    fire_lines.push_back(FireLine(glm::vec3(85.0f, -10.0f, 0.0f), glm::vec3(85.0f, -20.0f, 0.0f), true, 0.02f));
    fire_lines.push_back(FireLine(glm::vec3(80.0f, -15.0f, 0.0f), glm::vec3(90.0f, -15.0f, 0.0f), true, 0.02f));

    fire_lines.push_back(FireLine(glm::vec3(100.0f, -5.0f, 0.0f), glm::vec3(100.0f, 5.0f, 0.0f), true, 0.02f));
    fire_lines.push_back(FireLine(glm::vec3(95.0f, 0.0f, 0.0f), glm::vec3(105.0f, 0.0f, 0.0f), true, 0.02f));

    fire_lines.push_back(FireLine(glm::vec3(85.0f, 10.0f, 0.0f), glm::vec3(85.0f, 20.0f, 0.0f), true, 0.02f));
    fire_lines.push_back(FireLine(glm::vec3(80.0f, 15.0f, 0.0f), glm::vec3(90.0f, 15.0f, 0.0f), true, 0.02f));

    coins.push_back(Ball(85.0f, 0, COLOR_DARK_ORANGE, glm::vec3(0.0f, 1.0f, 0.0f), 0.0, 1.0f, 360.0f, 5));


//    for (float i=120;i< 300; i += 3.0f) {
//        coins.push_back(Ball(i, -10, COLOR_GOLD, glm::vec3(1.0f, 0.0f, 0.0f), 0.0, 1.0f, 360.0f, 1));
//    }

    for (float i=150;i<350;i+= 20) {
        fire_lines.push_back(FireLine(glm::vec3(i, 23.0f, 0.0f), glm::vec3(i, 28.0f, 0.0f)));
        coins.push_back(Ball(i+10, slab.min_y - 3 , COLOR_ORCHID, glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 1.0f, 360.0f, 2));
    }

    inv_obj = ScreenInversionObject(glm::vec3(100 +rand()%50, 10, 0));
    power_diamond = Diamond(10, glm::vec3(50 + rand()%50, -10, 0), COLOR_DIAMOND);




//    fire_lines.push_back(FireLine());

//    std::cout  << "Screen -> " << Screen.dimensions.min_y << std::endl;

//    printf("ground -> %f %f %f %f",ground.max_x, ground.max_y, ground.min_x, ground.min_y);
//    exit(0);

//    GLfloat vertices[] = {
//            0.0f, 0.0f, 0.0f,
//            0.5f, -3.0f, 0.0f,
//            1.0f, 0.0f, 0.0f,
//            1.0f, 1.0f, 0.0f,
//            0.5f, 1.5f, 0.0f,
//            0.0f, 1.0f, 0.0f,
//
//
//    };

//    GLfloat vertices_player[] = {
//        -1.0f, 1.0f, 0.0f,
//        -1.5f, -1.0f, 0.0f,
//        -1.0f, 1.0f, 0.0f,
//        -1.0f, 2.0f, 0.0f,
//        1.0f, 2.0f, 0.0f,
//        1.0f, 1.0f, 0.0f,
//        1.5f, -1.0f, 0.f,
//        1.0f, 0.0f, 0.0f,
//        1.0f, -2.0f, 0.0f,
//        0.5f, -2.0f, 0.0f,
//        0.5f, -1.0f, 0.0f,
//        -0.5f, -1.0f, 0.0f,
//        -0.5f, -2.0f, 0.0f,
//        -1.0f, -2.0f, 0.0f,
//    };


    loop = EscapeLoop(glm::vec3(-20, 0, 0));

//    temp_pol    = IrregularPolygon(14, vertices_player, glm::vec3(20.0f, 0.0f, 0.0f), COLOR_RED);
//    power_diamond = Diamond(10, glm::vec3(20.0f, 0.0f, 0.0f), COLOR_DIAMOND);
    enemy1 = FireLine(glm::vec3(30.0f, 30.0f, 0.0f), glm::vec3(30.0f, 20.0f, 0.0f), true, 0.02f);
    enemy1_2 = FireLine(glm::vec3(-30.0f, 30.0f, 0.0f), glm::vec3(-20.0f, 20.0f, 0.0f));
//    for (int i=0;i<4;i++) {
//        printf("line equations -> %f, %f, %f\n",enemy1_2.line_equations[i].x, enemy1_2.line_equations[i].y, enemy1_2.line_equations[i].z );
//    }
    enemy1_2.check_collision_with_point(enemy1_2.orb1.position);


    enemy_horizontal = FireLine(glm::vec3(35.0f, -25.f, 0.0f), glm::vec3(45.0f, -25.0f, 0.0f));
    enemy_horizontal.check_collision_with_point(glm::vec3(40.0f, -25.0f, 0.0f));

    enemy1_4 = FireLine(glm::vec3(35.0f, 25.0f, 0.0f), glm::vec3(25.0f, 25.0f, 0.0f), true, 0.02f);
    enemy_vertical = FireLine(glm::vec3(0.0f, 25.0f, .0f), glm::vec3(0.0f, 35.0f, .0f));
//    exit(0);
    enemy_2 = FireBeam(glm::vec3(-45.0f, 10.0f, 0.0f), glm::vec3(45.0f, 10.0f, 0.0f), -30.0f, 30.0f, 0);
    enemy3 = Boomerang(glm::vec3(Screen.dimensions.max_x, -28.0f,0.0f));
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


