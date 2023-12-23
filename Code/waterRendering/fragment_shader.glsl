#version 330 core

// Ouput data
//(out) vec4 color;
out vec4 FragColor;

in vec2 coord_txt;
uniform sampler2D skybox_txt;
uniform int isSkybox;

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

// reflection
uniform sampler2D reflectionTexture;

in vec3 fragNormal; 

in vec3 FragPos;

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

        vec4 reflectionColor = texture(reflectionTexture, coord_txt); // test texture


        if(isSkybox == 1){
                FragColor = texture(skybox_txt, coord_txt); // TODO fix
                //FragColor = vec4(objectColor, 0.0); // simple color
        }else{
                //FragColor = vec4(objectColor, 0.0); // simple color
                FragColor = vec4(result, transparency); // phong color 
                //FragColor = mix(reflectionColor, vec4(result, transparency), 1.0); // test reflection
                
        }


}
