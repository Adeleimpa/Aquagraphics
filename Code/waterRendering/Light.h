//
// Created by Adèle Imparato on 18/11/2023.
//

#ifndef LIGHT_H
#define LIGHT_H


class Light {
public:

    glm::vec3 position;
    glm::vec3 color;

    // vec3 for RGB values
    glm::vec3 I_ambiant;
    glm::vec3 I_diffuse;
    glm::vec3 I_specular;

    Light() {}
    Light(glm::vec3 a, glm::vec3 d, glm::vec3 s, glm::vec3 pos, glm::vec3 c) {
        I_ambiant = a;
        I_diffuse = d;
        I_specular = s;
        position = pos;
        color = c;
    }

    void sendDataToShaders(GLuint programID){

        glUniform3f(glGetUniformLocation(programID, "lightPos"), position[0], position[1], position[2]);
        glUniform3f(glGetUniformLocation(programID, "lightColor"), color[0], color[1], color[2]);

        glUniform3f(glGetUniformLocation(programID, "I_a"), I_ambiant[0], I_ambiant[1], I_ambiant[2]);
        glUniform3f(glGetUniformLocation(programID, "I_d"), I_diffuse[0], I_diffuse[1], I_diffuse[2]);
        glUniform3f(glGetUniformLocation(programID, "I_s"), I_specular[0], I_specular[1], I_specular[2]);

    }

};


#endif //LIGHT_H