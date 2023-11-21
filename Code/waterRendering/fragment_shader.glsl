#version 330 core

// Ouput data
//(out) vec4 color;
//(out) vec4 FragColor;

in vec2 coord_txt;

uniform vec4 mesh_color;
uniform vec3 lightPos;

in vec3 fragNormal; 

void main(){


        // todo light calcul

        gl_FragColor = mesh_color; // simple color

}
