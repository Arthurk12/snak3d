#ifndef COLLISIONS
#define COLLISIONS

#include <cstdio>
#include <cmath>

#include "collisions.h"

void debug(GameElement a, GameElement b) {
    printf("a bbox_min (%f, %f, %f) bbox_max (%f, %f, %f) \n",
    a.bbox_min.x, a.bbox_min.y, a.bbox_min.z, a.bbox_max.x, a.bbox_max.y, a.bbox_max.z);
    printf("b bbox_min (%f, %f, %f) bbox_max (%f, %f, %f) \n",
    b.bbox_min.x, b.bbox_min.y, b.bbox_min.z, b.bbox_max.x, b.bbox_max.y, b.bbox_max.z);
}

float findTheGreatestSide(GameElement obj) {
    float bboxes[6] = { obj.bbox_max.x, obj.bbox_max.y, obj.bbox_max.z,
                        obj.bbox_min.x, obj.bbox_min.y, obj.bbox_min.z};
    float greatest = std::abs(bboxes[0]);

    for (int i=1; i<5; i++){
        if(std::abs(bboxes[i]) > greatest) greatest = std::abs(bboxes[i]);
    }
    return greatest;
}

// colisions reference: https://dev.to/suvink/opengl-collisions-9ai
bool checkCubeCubeCollision(GameElement cube1,GameElement cube2) {
    //approximate the objects to simmetric cubes
    float cube1Width = findTheGreatestSide(cube1);
    float cube2Width = findTheGreatestSide(cube2);

    float cube1MinPositionX = cube1.position.x - std::abs(cube1Width);
    float cube1MaxPositionX = cube1.position.x + std::abs(cube1Width);
    float cube1MaxPositionY = cube1.position.y + std::abs(cube1Width);
    float cube1MinPositionY = cube1.position.y - std::abs(cube1Width);
    float cube1MinPositionZ = cube1.position.z - std::abs(cube1Width);
    float cube1MaxPositionZ = cube1.position.z + std::abs(cube1Width);

    float cube2MinPositionX = cube2.position.x - std::abs(cube2Width);
    float cube2MaxPositionX = cube2.position.x + std::abs(cube2Width);
    float cube2MaxPositionY = cube2.position.y + std::abs(cube2Width);
    float cube2MinPositionY = cube2.position.y - std::abs(cube2Width);
    float cube2MinPositionZ = cube2.position.z - std::abs(cube2Width);
    float cube2MaxPositionZ = cube2.position.z + std::abs(cube2Width);

    #ifdef DEBUG
    printf("                                               \n");
    printf(" %f < %f    %d \n", cube1MinPositionX,  cube2MaxPositionX,  cube1MinPositionX < cube2MaxPositionX);
    printf(" %f > %f    %d \n", cube1MaxPositionX,  cube2MinPositionX,  cube1MaxPositionX > cube2MinPositionX);
    printf(" %f < %f    %d \n", cube1MinPositionY,  cube2MaxPositionY,  cube1MinPositionY < cube2MaxPositionY);
    printf(" %f > %f    %d \n", cube1MaxPositionY,  cube2MinPositionY,  cube1MaxPositionY > cube2MinPositionY);
    printf(" %f < %f    %d \n", cube1MinPositionZ,  cube2MaxPositionZ,  cube1MinPositionZ < cube2MaxPositionZ);
    printf(" %f > %f    %d \n", cube1MaxPositionZ,  cube2MinPositionZ,  cube1MaxPositionZ > cube2MinPositionZ);
    printf("                                               \n");
    #endif

    if (cube1MinPositionX < cube2MaxPositionX &&
        cube1MaxPositionX > cube2MinPositionX &&
        cube1MinPositionY < cube2MaxPositionY &&
        cube1MaxPositionY > cube2MinPositionY &&
        cube1MinPositionZ < cube2MaxPositionZ &&
        cube1MaxPositionZ > cube2MinPositionZ
        ) return true;
    return false;
}

bool checkCubePlaneCollision(GameElement cube, GameElement plane) {
    // DEBUG debug(cube, plane);

    float cubeWidth = findTheGreatestSide(cube);

    float cubeMinPositionX = cube.position.x - std::abs(cubeWidth);
    float cubeMaxPositionX = cube.position.x + std::abs(cubeWidth);
    float cubeMaxPositionY = cube.position.y + std::abs(cubeWidth);
    float cubeMinPositionY = cube.position.y - std::abs(cubeWidth);
    float cubeMinPositionZ = cube.position.z - std::abs(cubeWidth);
    float cubeMaxPositionZ = cube.position.z + std::abs(cubeWidth);

    float planeWidthX = std::abs(plane.bbox_max.x) + std::abs(plane.bbox_min.x);
    float planeWidthY = std::abs(plane.bbox_max.y) + std::abs(plane.bbox_min.y);
    float planeWidthZ = std::abs(plane.bbox_max.z) + std::abs(plane.bbox_min.z);

    float planeX = plane.position.x;
    //float planeMaxPositionX = plane.position.x + std::abs(plane.bbox_max.x);
    float planeY = plane.position.y;
    //float planeMinPositionY = plane.position.y - std::abs(plane.bbox_min.y);
    float planeZ = plane.position.z;
    //float planeMaxPositionZ = plane.position.z + std::abs(plane.bbox_max.z);
      #ifdef DEBUG
        printf("                                               \n");
        printf("planeWidthX: %f planeWidthY: %f planeWidthZ: %f \n", planeWidthX, planeWidthY, planeWidthZ);
        printf("planeX: %f planeY: %f planeZ: %f \n", planeX, planeY, planeZ);
        printf("                                               \n");
      #endif


    if(planeWidthX < 0.001) {
      #ifdef DEBUG
        printf("                                               \n");
        printf("YZ plane => (- , -, %f)\n",planeZ);
        printf("cubeMinPositionX < planeX && cubeMaxPositionX > planeX => %d\n", cubeMinPositionX < planeX && cubeMaxPositionX > planeX);
        printf("                                               \n");
      #endif
      if (cubeMinPositionX < planeX && cubeMaxPositionX > planeX) return true;
    }
    if(planeWidthY < 0.001) {
      #ifdef DEBUG
        printf("                                               \n");
        printf("XZ plane => (%f, -, -)\n",planeX);
        printf("cubeMinPositionY < planeY && cubeMaxPositionY > planeY => %d\n", cubeMinPositionY < planeY && cubeMaxPositionY > planeY);
        printf("                                               \n");
      #endif
      if (cubeMinPositionY < planeY && cubeMaxPositionY > planeY) return true;
    }
    if(planeWidthZ < 0.001) {
      #ifdef DEBUG
        printf("                                               \n");
        printf("XY plane => (-, %f, -)\n",planeY);
        printf("cubeMinPositionZ < planeZ && cubeMaxPositionZ > planeZ => %d\n", cubeMinPositionZ < planeZ && cubeMaxPositionZ > planeZ);
        printf("                                               \n");
      #endif
      if (cubeMinPositionZ < planeZ && cubeMaxPositionZ > planeZ) return true;
    }
    return false;
}
#endif
