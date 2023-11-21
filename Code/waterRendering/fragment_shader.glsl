#version 330 core

// Ouput data
//(out) vec4 color;
//(out) vec4 FragColor;

in vec2 coord_txt;

uniform vec3 objectColor;
uniform vec3 k_a;
uniform vec3 k_d;
uniform vec3 k_s;

// light data
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 I_a;
uniform vec3 I_d;
uniform vec3 I_s;

// camera position
uniform vec3 viewPos;

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

        float specularStrength = 0.5;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * lightColor;  

        //vec3 result = ambient * objectColor;
        //vec3 result = (ambient + diffuse) * objectColor;
        vec3 result = (ambient + diffuse + specular) * objectColor;


        //gl_FragColor = vec4(objectColor, 1.0); // simple color
        gl_FragColor = vec4(result, 1.0); // phong color

}
