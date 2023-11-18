//
// Created by Adèle Imparato on 16/03/2023.
//

#ifndef AQUARIUM_H
#define AQUARIUM_H

#include "MeshObject.h"
#include "Plane.h"


class Aquarium : public MeshObject {
public:

    double side_len = 1.0;
    int side_unit = 1;

    glm::vec3 center = glm::vec3(0.0,0.0,0.0);

    Plane *floor, *left, *right, *back;

    double border; // aquarium goes upper than water
    double space = 0.02; // space between water and parois of aquarium

    Aquarium(){}

    Aquarium(double s_len, int s_unit, glm::vec3 c){
        side_len = s_len;
        side_unit = s_unit;
        center = c;

        border = side_len/8.;

        // FLOOR PLANE
        glm::vec3 center_floor =  glm::vec3(center[0], center[1] - side_len/2. , center[2]);
        floor = new Plane(side_len, side_len, side_unit, side_unit, center_floor, 1);
        // LEFT PLANE
        glm::vec3 center_left =  glm::vec3(center[0] - side_len/2. - space, center[1], center[2] - side_len);
        left = new Plane(side_len, side_len+border, side_unit, side_unit, center_left, 0);
        // RIGHT PLANE
        glm::vec3 center_right =  glm::vec3(center[0] + side_len/2. + space, center[1], center[2] - side_len);
        right = new Plane(side_len, side_len+border, side_unit, side_unit, center_right, 0);
        // BACK PLANE
        glm::vec3 center_back =  glm::vec3(center[0], center[1], center[2] - side_len/2. - space);
        back = new Plane(side_len, side_len+border, side_unit, side_unit, center_back, 2);

    }

    void generatePlanes(){
        // GENERATE PLANES AND BUFFERS
        floor->generatePlane();
        floor->generateBuffers();
        left->generatePlane();
        left->generateBuffers();
        right->generatePlane();
        right->generateBuffers();
        back->generatePlane();
        back->generateBuffers();
    }

    void setAquariumColor(glm::vec4 color){
        floor->setColor(color);
        left->setColor(color);
        right->setColor(color);
        back->setColor(color);
    }

};


#endif //AQUARIUM_H
