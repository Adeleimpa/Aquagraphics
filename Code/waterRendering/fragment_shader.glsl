#version 330 core

// Ouput data
out vec4 FragColor;

in vec2 coord_txt;
uniform sampler2D skybox_txt;
uniform int isSkybox;
uniform sampler2D wood_txt;
uniform int isPlane;

uniform vec3 objectColor;
uniform vec3 k_a;
uniform vec3 k_d;
uniform vec3 k_s;
uniform float transparency;

// light data
uniform vec3 lightPos;
uniform vec3 I_a;
uniform vec3 I_d;
uniform vec3 I_s;

// camera position
uniform vec3 viewPos;

in vec3 fragNormal; 

in vec3 FragPos;

// reflection
uniform sampler2D reflectionTexture;
uniform int isWater;

void main(){

        // light calculations
        vec3 ambient = I_a * k_a;

        vec3 norm = normalize(fragNormal);
        vec3 lightDir = normalize(lightPos - FragPos); 

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * I_d * k_d;

        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = I_s * spec * k_s;

        //vec3 result = ambient * objectColor;
        //vec3 result = (ambient + diffuse) * objectColor;
        vec3 result = (ambient + diffuse + specular) * objectColor;


        if(isSkybox == 1){
                FragColor = texture(skybox_txt, coord_txt) * vec4(objectColor, 0.0);

        }else if (isPlane ==  1){
                //FragColor = texture(wood_txt, coord_txt) * vec4(objectColor, 0.0);
                FragColor = texture(reflectionTexture, coord_txt) * vec4(0.9, 0.9, 0.9, 0.0); // test reflection

        }else if (isWater ==  1){
                FragColor = vec4(result, transparency); // phong color 
                //FragColor = texture(reflectionTexture, coord_txt) * vec4(0.9, 0.9, 0.9, 0.0); // test reflection

        }else{
                //FragColor = vec4(objectColor, 0.0); // simple color
                FragColor = vec4(result, transparency); // phong color 
        }


}
