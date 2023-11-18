//
// Created by Adèle Imparato on 16/03/2023.
//

#ifndef CUBE_H
#define CUBE_H

#include "MeshObject.h"
#include "Square.h"


class Cube : public MeshObject {
public:

    double side_len;
    int side_unit;

    glm::vec3 center = glm::vec3(0.0,0.0,0.0); // default value

};


#endif //CUBE_H
