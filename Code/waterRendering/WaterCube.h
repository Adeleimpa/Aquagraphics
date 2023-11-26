//
// Created by Adèle Imparato on 25/11/2023.
//

#ifndef WATER_CUBE_H
#define WATER_CUBE_H

#include "SceneObject.h"


class WaterCube : public SceneObject {
public:
    WaterCube(const glm::vec3& center, float side_len) : center(center), side_len(side_len) {
        initCube();
    }

    float calculateHeight(float x, float amplitude, float frequency, float phaseShift) {
        return amplitude * sin(frequency * x + phaseShift);
    }
     
    void animateWater(float amplitude, float frequency, float time) {

        for (unsigned int vertexIndex = 0; vertexIndex <= 960; ++vertexIndex) { // top face vertices

            float animatedHeight = calculateHeight(indexed_vertices[vertexIndex][0], amplitude, frequency, time);
            indexed_vertices[vertexIndex][1] = animatedHeight + side_len/2.0f; // edit y coord
        }
    }

private:
    glm::vec3 center;
    float side_len;


    void initCube() {

        // Top face (30x30)
        for (int i = 0; i <= 30; ++i) { // height
            for (int j = 0; j <= 30; ++j) { // width
                float x = center.x - side_len / 2.0f + (j / 30.0f) * side_len;
                float z = center.z - side_len / 2.0f + (i / 30.0f) * side_len;
                float y = center.y + side_len / 2.0f; // top face height (constant)
                indexed_vertices.emplace_back(x, y, z);
                normals.emplace_back(0.0f, 1.0f, 0.0f); // Normal points to the sky
            }
        }

        // 5 other faces (30x2): front, back, left, right, floor
        // Front face
        for (int i = 1; i >= 0; --i) { // height, /!\ skip top row (already in top face vertices)
            for (int j = 0; j <= 30; ++j) { // width
                float x = center.x - side_len / 2.0f + (j / 30.0f) * side_len;
                float z = center.z + side_len / 2.0f;
                float y = center.y - side_len / 2.0f + (i / 2.0f) * side_len;
                indexed_vertices.emplace_back(x, y, z);
                normals.emplace_back(0.0f, 0.0f, 1.0f); // Normals point towards viewer
            }
        }

        // Back face
        for (int i = 1; i >= 0; --i) { // /!\ skip top row (already in top face vertices)
            for (int j = 0; j <= 30; ++j) {
                float x = center.x + side_len / 2.0f - (j / 30.0f) * side_len;
                float z = center.z - side_len / 2.0f;
                float y = center.y - side_len / 2.0f + (i / 2.0f) * side_len;
                indexed_vertices.emplace_back(x, y, z);
                normals.emplace_back(0.0f, 0.0f, -1.0f); // Normals point away from viewer
            }
        }

        // Left face
        for (int i = 1; i >= 0; --i) { // /!\ skip top row
            for (int j = 1; j <= 29; ++j) { // /!\ skip 1st and last column
                float x = center.x - side_len / 2.0f;
                float z = center.z - side_len / 2.0f + (j / 30.0f) * side_len;
                float y = center.y - side_len / 2.0f + (i / 2.0f) * side_len;
                indexed_vertices.emplace_back(x, y, z);
                normals.emplace_back(-1.0f, 0.0f, 0.0f); // Normals point towards left
            }
        }

        // Right face
        for (int i = 1; i >= 0; --i) { // /!\ skip top row
            for (int j = 1; j <= 29; ++j) { // /!\ skip 1st and last column
                float x = center.x + side_len / 2.0f;
                float z = center.z + side_len / 2.0f - (j / 30.0f) * side_len;
                float y = center.y - side_len / 2.0f + (i / 2.0f) * side_len;
                indexed_vertices.emplace_back(x, y, z);
                //std::cout << " " << x << "," << y << "," << z;
                normals.emplace_back(1.0f, 0.0f, 0.0f); // Normals point towards right
            }
            //std::cout << "\n" << std::endl;
        }

        // Floor face
        for (int i = 1; i <= 29; ++i) { // /!\ skip top and last row
            for (int j = 1; j <= 29; ++j) { // /!\ skip 1st and last column
                float x = center.x - side_len / 2.0f + (j / 30.0f) * side_len;
                float z = center.z - side_len / 2.0f + (i / 30.0f) * side_len;
                float y = center.y - side_len / 2.0f;
                indexed_vertices.emplace_back(x, y, z);
                normals.emplace_back(0.0f, -1.0f, 0.0f); // Normals point downward
            }
        }


        // Create triangles (fill indices and triangles)
        // note: 31 vertices -> 60 triangles

        // Top face
        for (int i = 0; i < 30; ++i) {
            for (int j = 0; j < 30; ++j) {
                int c1 = i * 31 + j;
                int c2 = c1 + 1;
                int c3 = (i + 1) * 31 + j;
                int c4 = c3 + 1;

                indices.push_back(c1);
                indices.push_back(c2);
                indices.push_back(c3);

                indices.push_back(c3);
                indices.push_back(c2);
                indices.push_back(c4);

                triangles.push_back({c1, c2, c3});
                triangles.push_back({c3, c2, c4});
            }
        }

        // Front face
        int baseIndex = 31 * 31 - 1 - 30; // starting index

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 30; ++j) {
                int c1 = baseIndex + i * 31 + j;
                int c2 = c1 + 1;
                int c3 = baseIndex + (i + 1) * 31 + j;
                int c4 = c3 + 1;

                indices.push_back(c1);
                indices.push_back(c2);
                indices.push_back(c3);

                indices.push_back(c3);
                indices.push_back(c2);
                indices.push_back(c4);

                triangles.push_back({c1, c2, c3});
                triangles.push_back({c3, c2, c4});
            }
        }

        // Back face
        baseIndex = 31 * 31 - 1 + 31 + 1; // starting index

        for(int i = 0; i < 2; ++i){
            for (int j = 0; j < 30; ++j) {
                int c1, c2;
                
                if(i==0){ // row 1
                    c1 = 30 - j;
                    c2 = c1 - 1;
                }else{ // row 2
                    c1 = baseIndex + i * 31 + j;
                    c2 = c1 + 1;
                }

                int c3 = baseIndex + (i + 1) * 31 + j;
                int c4 = c3 + 1;

                indices.push_back(c1);
                indices.push_back(c2);
                indices.push_back(c3);

                indices.push_back(c3);
                indices.push_back(c2);
                indices.push_back(c4);

                triangles.push_back({c1, c2, c3});
                triangles.push_back({c3, c2, c4});
            }
        }

    
        // Left face
        baseIndex = 1085 - 31 - 1; // starting index

        for(int i = 0; i < 2; ++i){
            for (int j = 0; j < 30; ++j) {
                int c1, c2, c3, c4;

                c1 = baseIndex + i * 31 + j;
                c2 = c1 + 1;
                c3 = baseIndex + (i + 1) * 31 + j;
                c4 = c3 + 1;
                
                if(i==0){ // row 1
                    c1 = j * 31;
                    c2 = c1 + 31;

                    if(j==0){ // col 1
                        c3 = baseIndex;
                        c4 = baseIndex + (i + 1) * 31 + j + 1;

                    }else if (j==29){ // last col
                        c3 = baseIndex + (i + 1) * 31 + j;
                        c4 = 961;
                    }

                }else{ // row 2
                    c3 -= 2;
                    c4 = c3 + 1;

                    if(j==0){ // col 1
                        c1 = baseIndex;
                        c3 = c1 + 31;

                    }else if (j==29){ // last col
                        c2 = 961;
                        c4 = 992;
                    }
                }

                indices.push_back(c1);
                indices.push_back(c2);
                indices.push_back(c3);

                indices.push_back(c3);
                indices.push_back(c2);
                indices.push_back(c4);

                triangles.push_back({c1, c2, c3});
                triangles.push_back({c3, c2, c4}); 
            }
        }

        // Right face
        baseIndex = 1143 - 31 - 1; // starting index

        for(int i = 0; i < 2; ++i){
            for (int j = 0; j < 30; ++j) {
                int c1, c2, c3, c4;

                c1 = baseIndex + i * 31 + j;
                c2 = c1 + 1;
                c3 = baseIndex + (i + 1) * 31 + j;
                c4 = c3 + 1;
                
                if(i==0){ // row 1
                    c1 = 960 - (j * 31);
                    c2 = c1 - 31;

                    if(j==0){ // col 1
                        c3 = 991;
                        c4 = baseIndex + (i + 1) * 31 + j + 1;

                    }else if (j==29){ // last col
                        c3 = baseIndex + (i + 1) * 31 + j;
                        c4 = 1023;
                    }

                }else{ // row 2
                    c3 -= 2;
                    c4 = c3 + 1;

                    if(j==0){ // col 1
                        c1 = 991;
                        c3 = c1 + 31;

                    }else if (j==29){ // last col
                        c2 = 1023;
                        c4 = 1054;
                    }
                }

                indices.push_back(c1);
                indices.push_back(c2);
                indices.push_back(c3);

                indices.push_back(c3);
                indices.push_back(c2);
                indices.push_back(c4);

                triangles.push_back({c1, c2, c3});
                triangles.push_back({c3, c2, c4}); 
            }
        }

        // Floor face
        baseIndex = 1172;

        for (int i = 0; i < 30; ++i) {
            for (int j = 0; j < 30; ++j) {
                int c1, c2, c3, c4;

                // general case
                c1 = baseIndex + i * 29 + j - 1;
                c2 = c1 + 1;
                c3 = c1 + 29;
                c4 = c3 + 1;

                if(j==0){ // col 1
                    c1 = 1114 + i - 1;
                    c3 = c1 + 1;
                }

                if(j==29){ // last col
                    c2 = 1201 - i;
                    c4 = c2 - 1;
                }

                if(i==29){ // last row
                    c3 = 992 + j;
                    c4 = c3 + 1;
                }

                if(i==0){ // row 1
                    c1 = 1084 - j;
                    c2 = c1 - 1;
                }

                indices.push_back(c1);
                indices.push_back(c2);
                indices.push_back(c3);

                indices.push_back(c3);
                indices.push_back(c2);
                indices.push_back(c4);

                triangles.push_back({c1, c2, c3});
                triangles.push_back({c3, c2, c4});

                /*std::cout << "c1: " << c1 << std::endl;
                std::cout << "c2: " << c2 << std::endl;
                std::cout << "c3: " << c3 << std::endl;
                std::cout << "c4: " << c4 << std::endl;
                std::cout << "" << std::endl;*/
            }
        }

        //std::cout << "Triangles constructed" << std::endl;

        // TODO set texture coordinate (if needed)
        for (int i = 0; i < indexed_vertices.size(); ++i) {
            coord_texture.emplace_back(0.0f, 0.0f);
        }
        //std::cout << "Textures done" << std::endl;


        /*std::cout << "indexed_vertices.size(): " << indexed_vertices.size() << std::endl;
        std::cout << "indices.size(): " << indices.size() << std::endl;
        std::cout << "normals.size(): " << normals.size() << std::endl;
        std::cout << "triangles.size(): " << triangles.size() << std::endl;*/
    }


};


#endif //WATER_CUBE_H