#version 330 core

// Ouput data
//(out) vec4 color;
//(out) vec4 FragColor;

in vec2 coord_txt;

uniform vec4 mesh_color;

void main(){

        //color = vec3(0.0, 0.0, 1.0);
        gl_FragColor = mesh_color;

}
