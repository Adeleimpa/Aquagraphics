#version 330 core

// Ouput data
//(out) vec4 color;
//(out) vec4 FragColor;

// texture
uniform sampler2D texture_grass;
uniform sampler2D texture_rock;
uniform sampler2D texture_snowrocks;
uniform sampler2D texture_snow;
uniform sampler2D texture_sun;
in vec2 coord_txt;

// heightmap
in float height;

float coef_grass;
float coef_rock;
float coef_snowrocks;

uniform int isPlane;

uniform vec4 mesh_color;

void main(){

        //color = vec3(0.0, 0.0, 1.0);
        gl_FragColor = mesh_color;

}
