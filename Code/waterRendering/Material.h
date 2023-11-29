//
// Created by Adèle Imparato on 18/11/2023.
//

#ifndef MATERIAL_H
#define MATERIAL_H


class Material {
public:
    // vec3 for RGB values
    glm::vec3 k_ambiant;
    glm::vec3 k_diffuse;
    glm::vec3 k_specular;

    float transparency; // alpha

};


#endif //MATERIAL_H