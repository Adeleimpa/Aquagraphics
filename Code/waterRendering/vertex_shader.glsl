#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertices_position_modelspace;

// Input normal data
layout (location = 1) in vec3 vertexNormal;

// uniform transformations matrices Model View Projection
// Values that stay constant for the whole mesh.
uniform mat4 model_matrix;
uniform mat4 view_matrix; // camera
uniform mat4 proj_matrix;

mat4 transformation_matrix;

// texture
out vec2 coord_txt;
layout(location = 2) in vec2 coord;

// send normals to fragment shader
out vec3 fragNormal;

// send fragment position to fragment shader
out vec3 FragPos;  


void main(){
        
        transformation_matrix = proj_matrix * view_matrix * model_matrix; // MVP but inverted! (order matters)
        gl_Position = transformation_matrix * vec4(vertices_position_modelspace, 1);

        FragPos = vec3(model_matrix * vec4(vertices_position_modelspace, 1.0));

        fragNormal = vertexNormal;

        coord_txt = coord; // texture

}

