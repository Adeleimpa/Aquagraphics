//
// Created by Adèle Imparato on 18/11/2023.
//

#ifndef LIGHT_H
#define LIGHT_H


class Light {
public:

    glm::vec3 position;

    // vec3 for RGB values
    glm::vec3 I_ambiant;
    glm::vec3 I_diffuse;
    glm::vec3 I_specular;

    Light() {}
    Light(glm::vec3 a, glm::vec3 d, glm::vec3 s, glm::vec3 pos) {
        I_ambiant = a;
        I_diffuse = d;
        I_specular = s;
        position = pos;
    }

};


#endif //LIGHT_H