#ifndef COLLISIONS
#define COLLISIONS

#include <cstdio>
//#include <cstdlib>

#include "collisions.h"

// colisions reference: https://dev.to/suvink/opengl-collisions-9ai
bool checkCubeCubeCollision(GameElement cube1,GameElement cube2) {
    cube1.bbox_min*=cube1.scale;
    cube1.bbox_max*=cube1.scale;
    cube2.bbox_min*=cube2.scale;
    cube2.bbox_max*=cube2.scale;
    float cube1MinPositionX = cube1.position.x - std::abs(cube1.bbox_min.x);
    float cube1MaxPositionX = cube1.position.x + std::abs(cube1.bbox_max.x);
    float cube1MinPositionZ = cube1.position.z - std::abs(cube1.bbox_min.z);
    float cube1MaxPositionZ = cube1.position.z + std::abs(cube1.bbox_max.z);

    float cube2MinPositionX = cube2.position.x - std::abs(cube2.bbox_min.x);
    float cube2MaxPositionX = cube2.position.x + std::abs(cube2.bbox_max.x);
    float cube2MinPositionZ = cube2.position.z - std::abs(cube2.bbox_min.z);
    float cube2MaxPositionZ = cube2.position.z + std::abs(cube2.bbox_max.z);

    printf("                                               \n");
    printf(" %f < %f    %d \n", cube1MinPositionX,  cube2MaxPositionX,  cube1MinPositionX < cube2MaxPositionX);
    printf(" %f > %f    %d \n", cube1MaxPositionX,  cube2MinPositionX,  cube1MaxPositionX > cube2MinPositionX);
    printf(" %f < %f    %d \n", cube1MaxPositionZ,  cube2MinPositionZ,  cube1MaxPositionZ < cube2MinPositionZ);
    printf(" %f > %f    %d \n", cube1MinPositionZ,  cube2MaxPositionZ,  cube1MinPositionZ > cube2MaxPositionZ);
    printf("                                               \n");

    if (cube1MinPositionX < cube2MaxPositionX &&
        cube1MaxPositionX > cube2MinPositionX &&
        cube1MaxPositionZ > cube2MinPositionZ &&
        cube1MinPositionZ < cube2MaxPositionZ
        //TODO: CHECK IF THE CUBES COLIDE ON y AXIS
        ) return true;
    return false;
}

bool checkCubePlaneCollision(/*cube, plane*/) {
    //if()
    return false;
}
#endif
