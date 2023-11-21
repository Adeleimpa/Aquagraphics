#version 330 core

// Ouput data
//(out) vec4 color;
//(out) vec4 FragColor;

in vec2 coord_txt;

uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 lightColor;

in vec3 fragNormal; 

in vec3 FragPos;

void main(){

        // light calculations
        float ambientStrength = 0.8;
        vec3 ambient = ambientStrength * lightColor;

        vec3 norm = normalize(fragNormal);
        vec3 lightDir = normalize(lightPos - FragPos); 

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;

        //vec3 result = ambient * objectColor; // ambient
        vec3 result = (ambient + diffuse) * objectColor; // ambient + diffuse


        //gl_FragColor = vec4(objectColor, 1.0); // simple color
        gl_FragColor = vec4(result, 1.0); // phong color

}
