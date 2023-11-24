//
// Created by Adèle Imparato on 13/02/2023.
//

#ifndef TUTORIALS_PLANE_H
#define TUTORIALS_PLANE_H

#include <vector>
#include <iostream>
#include <cmath>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "SceneObject.h"
#include "Material.h"

class Plane : public SceneObject {

private:

public:

    double width = 1.;
    double height = 1.;

    int w = 1;
    int h = 1;

    int xyz; // plane orientation: 0 for x = 0, 1 for y = 0, 2 for z = 0

    glm::vec3 center = glm::vec3(0.0,0.0,0.0); 

    glm::vec3 bottom_right, bottom_left, top_right, top_left;

    Plane() {}
    Plane(double wi , double he , int nw, int nh, glm::vec3 center, int x_y_z) {
        width = wi;
        height = he;
        h = nw;
        w = nh;

        xyz = x_y_z;

        if(xyz == 0){ // x = 0
            //std::cout << "x=0" << std::endl;
            bottom_left = glm::vec3(center[0], center[1]-height/2, center[2]+width/2);
            bottom_right = glm::vec3(center[0], center[1-height/2], center[2]-width/2);
            top_right = glm::vec3(center[0], center[1]+height/2, center[2]+width/2);
            top_left = glm::vec3(center[0], center[1]+height/2, center[2]-width/2);

        }else if(xyz == 1){ // y = 0
            //std::cout << "y=0" << std::endl;
            bottom_left = glm::vec3(center[0]-width/2, center[1], center[2]+height/2);
            bottom_right = glm::vec3(center[0]+width/2, center[1], center[2]+height/2);
            top_right = glm::vec3(center[0]+width/2, center[1], center[2]-height/2);
            top_left = glm::vec3(center[0]-width/2, center[1], center[2]-height/2);

        }else{ // z = 0
            //std::cout << "z=0" << std::endl;
            bottom_left = glm::vec3(center[0]-width/2, center[1]-height/2, center[2]);
            bottom_right = glm::vec3(center[0]+width/2, center[1]-height/2, center[2]);
            top_right = glm::vec3(center[0]+width/2, center[1]+height/2, center[2]);
            top_left = glm::vec3(center[0]-width/2, center[1]+height/2, center[2]);
        }

    }

    void setDimension(int nw, int nh){
        h = nw;
        w = nh;
    }

    void setPlaneMaterial(glm::vec3 a, glm::vec3 d, glm::vec3 s){
        material.k_ambiant = a;
        material.k_diffuse = d;
        material.k_specular = s;
    }

    // n_orient indicates the orientation of the normal, it can be +1.0 or -1.0
    void generatePlane(double n_orient){

        double step_1 = width/(double)w;
        double step_2 = height/(double)h;


        glm::vec3 current_corner;

        // fill indexed_vertices
        if(xyz == 0){ // x = 0

            glm::vec3 start_corner = bottom_left;

            for(int i = 0; i <= h; i++) {
                for (int j = 0; j <= w; j++) {
                    current_corner = glm::vec3(start_corner[0], start_corner[1] + j*step_2, start_corner[2] + i*step_1);
                    glm::vec3 normal = glm::vec3(n_orient, 0.0, 0.0);
                    coord_texture.push_back(glm::vec2(1.0-current_corner[1]/height, current_corner[2]/width)); // todo check
                    indexed_vertices.push_back(current_corner);
                    normals.push_back(normal);
                }
            }


        }else if(xyz == 1){ // y = 0

            glm::vec3 start_corner = top_left;

            for(int i = 0; i <= h; i++) {
                for (int j = 0; j <= w; j++) {
                    current_corner = glm::vec3(start_corner[0] + i*step_1, start_corner[1], start_corner[2] + j*step_2);
                    glm::vec3 normal = glm::vec3(0.0, n_orient, 0.0);
                    coord_texture.push_back(glm::vec2(current_corner[0]/width, 1.0-current_corner[2]/height));
                    indexed_vertices.push_back(current_corner);
                    normals.push_back(normal);
                }
            }

        }else if(xyz == 2){ // z = 0
            
            glm::vec3 start_corner = bottom_left;

            for(int i = 0; i <= h; i++) {
                for (int j = 0; j <= w; j++) {
                    current_corner = glm::vec3(start_corner[0] + i*step_1, start_corner[1] + j*step_2, start_corner[2]);
                    glm::vec3 normal = glm::vec3(0.0, 0.0, n_orient);
                    coord_texture.push_back(glm::vec2(current_corner[0]/width, 1.0-current_corner[1]/height)); // todo check
                    indexed_vertices.push_back(current_corner);
                    normals.push_back(normal);
                }
            }
        }

        for(int i = 0; i < h; i++){
            for(int j = 0; j < w; j++){
                std::vector<unsigned short> triangle1;
                std::vector<unsigned short> triangle2;
                int c1, c2, c3, c4;

                c1 = i + j*(w+1);
                c2 = (i+1) + j*(w+1);
                c3 = i + (j+1)*(w+1);
                c4 = (i+1) + (j+1)*(w+1);

                indices.push_back(c1);
                indices.push_back(c2);
                indices.push_back(c3);

                indices.push_back(c3);
                indices.push_back(c4);
                indices.push_back(c2);

                triangle1.push_back(c1);
                triangle1.push_back(c2);
                triangle1.push_back(c3);

                triangle2.push_back(c3);
                triangle2.push_back(c4);
                triangle2.push_back(c2);

                triangles.push_back(triangle1);
                triangles.push_back(triangle2);
            }
        }
    }


    // --------------------------------------------------------------
    // Functions to animate a plane representing the surface of water
    // --------------------------------------------------------------
    float calculateHeight(float x, float amplitude, float frequency, float phaseShift) {
        return amplitude * sin(frequency * x + phaseShift);
    }
     
    void animateWater(float amplitude, float frequency, float time, float initial_height) {

        for (size_t i = 0; i < triangles.size(); ++i) {
            
            for (size_t j = 0; j < triangles[i].size(); ++j) {
                unsigned short vertexIndex = triangles[i][j];
                float animatedHeight = calculateHeight(indexed_vertices[vertexIndex][0], amplitude, frequency, time);
                indexed_vertices[vertexIndex][1] = animatedHeight + initial_height; // edit y coord
            }
        }
    }
    // --------------------------------------------------------------


};


#endif //TUTORIALS_PLANE_H
