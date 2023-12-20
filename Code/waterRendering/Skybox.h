//
// Created by Adèle Imparato on 25/11/2023.
//

#ifndef SKYBOX_H
#define SKYBOX_H

#include "Plane.h"


class Skybox : public MeshObject {
public:
    glm::vec3 center;
    float side_len;
    int side_unit = 1;

    Plane *top, *floor, *left, *right, *back, *front;

    Skybox(const glm::vec3& center, float side_len) : center(center), side_len(side_len) {

        
        // TOP PLANE
        glm::vec3 center_top =  glm::vec3(center[0], center[1] + side_len/2. , center[2]);
        top = new Plane(side_len, side_len, side_unit, side_unit, center_top, 1);
        // FLOOR PLANE
        glm::vec3 center_floor =  glm::vec3(center[0], center[1] - side_len/2. , center[2]);
        floor = new Plane(side_len, side_len, side_unit, side_unit, center_floor, 1);
        // LEFT PLANE
        glm::vec3 center_left =  glm::vec3(center[0] - side_len/2., center[1], center[2] - side_len);
        left = new Plane(side_len, side_len, side_unit, side_unit, center_left, 0);
        // RIGHT PLANE
        glm::vec3 center_right =  glm::vec3(center[0] + side_len/2., center[1], center[2] - side_len);
        right = new Plane(side_len, side_len, side_unit, side_unit, center_right, 0);
        // BACK PLANE
        glm::vec3 center_back =  glm::vec3(center[0], center[1], center[2] - side_len/2.);
        back = new Plane(side_len, side_len, side_unit, side_unit, center_back, 2);
        // FRONT PLANE
        glm::vec3 center_front =  glm::vec3(center[0], center[1], center[2] + side_len/2.);
        front = new Plane(side_len, side_len, side_unit, side_unit, center_front, 2);
        
    }


    void generatePlanes(){
        // GENERATE PLANES AND BUFFERS
        top->generatePlane(-1.0);
        top->generateBuffers();
        floor->generatePlane(1.0);
        floor->generateBuffers();
        left->generatePlane(1.0);
        left->generateBuffers();
        right->generatePlane(-1.0);
        right->generateBuffers();
        front->generatePlane(-1.0);
        front->generateBuffers();
        back->generatePlane(1.0);
        back->generateBuffers();
    }

    void setCubeColor(glm::vec3 color){
        top->setColor(color);
        floor->setColor(color);
        left->setColor(color);
        right->setColor(color);
        front->setColor(color);
        back->setColor(color);
    }

    void setCubeMaterial(glm::vec3 a, glm::vec3 d, glm::vec3 s, float alpha){
        top->setMaterial(a, d, s, alpha);
        floor->setMaterial(a, d, s, alpha);
        left->setMaterial(a, d, s, alpha);
        right->setMaterial(a, d, s, alpha);
        front->setMaterial(a, d, s, alpha);
        back->setMaterial(a, d, s, alpha);
    }

    void setIsSkybox(int val){
        top->isSkybox = val;
        floor->isSkybox = val;
        left->isSkybox = val;
        right->isSkybox = val;
        front->isSkybox = val;
        back->isSkybox = val;
    }


};


#endif //SKYBOX_H