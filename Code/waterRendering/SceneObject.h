//
// Created by Adèle Imparato on 09/03/2023.
//

#ifndef TP1_CODE_SCENEOBJECT_H
#define TP1_CODE_SCENEOBJECT_H

#include <iostream>
#include <glm/glm.hpp>

#include "Material.h"

class SceneObject
{

private:
public:
    std::vector<unsigned short> indices; // Triangles concaténés dans une liste
    std::vector<std::vector<unsigned short>> triangles;
    std::vector<glm::vec3> indexed_vertices;
    std::vector<glm::vec2> coord_texture; // texture
    std::vector<glm::vec3> normals;

    // ids of frame buffer objects
    GLuint vertexbuffer, normalbuffer, elementbuffer, buffer_coord_txt;

    // default value => 0 = false
    int isSkybox;
    int isPlane;
    int isWater;
    int isAquarium;
    int isSphere;

    glm::vec3 color = glm::vec3(0.0, 0.0, 0.0); // default value

    Material material;

    SceneObject() {}

    void setColor(glm::vec3 color)
    {
        this->color = color;
    }

    void setMaterial(glm::vec3 a, glm::vec3 d, glm::vec3 s, float alpha)
    {
        material.k_ambiant = a;
        material.k_diffuse = d;
        material.k_specular = s;
        material.transparency = alpha;
    }

    void draw(GLuint programID, bool wired) const
    {
        if (triangles.size() == 0)
            return;

        glUniform3f(glGetUniformLocation(programID, "objectColor"), color[0], color[1], color[2]);
        glUniform3f(glGetUniformLocation(programID, "k_a"), material.k_ambiant[0], material.k_ambiant[1], material.k_ambiant[2]);
        glUniform3f(glGetUniformLocation(programID, "k_d"), material.k_diffuse[0], material.k_diffuse[1], material.k_diffuse[2]);
        glUniform3f(glGetUniformLocation(programID, "k_s"), material.k_specular[0], material.k_specular[1], material.k_specular[2]);
        glUniform1f(glGetUniformLocation(programID, "transparency"), material.transparency);

        glUniform1i(glGetUniformLocation(programID, "isSkybox"), isSkybox);
        glUniform1i(glGetUniformLocation(programID, "isPlane"), isPlane);
        glUniform1i(glGetUniformLocation(programID, "isWater"), isWater);
        glUniform1i(glGetUniformLocation(programID, "isAquarium"), isAquarium);
        glUniform1i(glGetUniformLocation(programID, "isSphere"), isSphere);

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0); // layout (location = 0)
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,        // attribute
            3,        // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0,        // stride
            (void *)0 // array buffer offset
        );

        // 2nd attribute buffer: normals
        glEnableVertexAttribArray(1); // layout (location = 1)
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
            1,        // attribute
            3,        // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0,        // stride
            (void *)0 // array buffer offset
        );

        // 3rd attribute buffer: texture coordinates
        glEnableVertexAttribArray(2); // layout (location = 2)
        glBindBuffer(GL_ARRAY_BUFFER, buffer_coord_txt);
        glVertexAttribPointer(
            2,        // attribute
            2,        // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            sizeof(GLfloat)*2,        // stride
            (void *)0 // array buffer offset
        );

        // Index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

        if (wired)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // displays meshs
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glTexCoordPointer(2, GL_FLOAT, 2 * sizeof(float), (GLvoid *)(coord_texture.data()));
        glNormalPointer(GL_FLOAT, 3 * sizeof(float), (GLvoid *)(normals.data()));
        glVertexPointer(3, GL_FLOAT, 3 * sizeof(float), (GLvoid *)(indexed_vertices.data()));

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void *)0);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
    }

    void generateBuffers()
    {
        glGenBuffers(1, &vertexbuffer);
        glGenBuffers(1, &normalbuffer);
        glGenBuffers(1, &elementbuffer);
        glGenBuffers(1, &buffer_coord_txt);
    }

    void loadBuffers()
    {
        // Load data (vertices, meshes, etc.) into VBO's
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

        // Generate a buffer for the vertex normals
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

        // Generate a buffer for the indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

        // fill buffer for texture coordinates
        glBindBuffer(GL_ARRAY_BUFFER, buffer_coord_txt);
        glBufferData(GL_ARRAY_BUFFER, coord_texture.size() * sizeof(glm::vec2), &coord_texture[0], GL_STATIC_DRAW);
    }

    void deleteBuffers()
    {
        glDeleteBuffers(1, &vertexbuffer);
        glDeleteBuffers(1, &normalbuffer);
        glDeleteBuffers(1, &elementbuffer);
        glDeleteBuffers(1, &buffer_coord_txt);
    }

    void clearVectors()
    {
        indexed_vertices.clear();
        indices.clear();
        triangles.clear();
        normals.clear();
        coord_texture.clear();
    }
};

#endif // TP1_CODE_SCENEOBJECT_H
