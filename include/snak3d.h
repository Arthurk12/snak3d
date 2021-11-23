#ifndef SNAK3D_HEADER
#define SNAK3D_HEADER

// Headers da biblioteca GLM: criação de matrizes e vetores.
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

//#define DEBUG

#define TITLE "SNAK3D"

//object IDs
#define PLANE  0
#define FRUIT  1
#define SNAKE_HEAD 2
#define BOTTOM_SIDE 3
#define LEFT_SIDE   4
#define TOP_SIDE    5
#define RIGHT_SIDE  6

// Direções em que a cobra estará se movimentando
#define UP    0
#define DOWN  180
#define LEFT  90
#define RIGHT 270

#define SNAKE_INITIAL_SPEED 0.005
#define SNAKE_INITIAL_POSITION_X  0
//no initial snake y position, because it only moves over the plane which has fixed y
#define SNAKE_INITIAL_POSITION_Z  0.07

struct GameElement
{
    glm::vec3 position = glm::vec3(0,0,0);
    glm::vec3 scale = glm::vec3(1, 1, 1); //default is original scale
    glm::vec3    bbox_min; // Axis-Aligned Bounding Box do objeto
    glm::vec3    bbox_max;
    int score = 0;
    bool paused = false;
};

struct Snake
{
    GameElement ge;
    float speed = SNAKE_INITIAL_SPEED;
    int direction = UP;
};
#endif
