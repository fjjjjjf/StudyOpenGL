#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;  
in vec3 Normal; 

struct Light {

    vec3 position;  
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform sampler2D texture_diffuse1;
uniform Light light;
uniform vec3 viewPos;

void main()
{    
    vec3 lightDir =normalize(light.position-FragPos);

    float theta =dot(lightDir,normalize(-light.direction));

    if(theta >light.cutOff)// remember that we're working with angles as cosines instead of degrees so a '>' is used.
    {    
        //ambient
        vec3 ambient =light.ambient *texture(texture_diffuse1, TexCoords).rgb;

        //diffuse
        vec3 norm =normalize(Normal);
        float diff =max(dot(norm,lightDir),0.0);
        vec3 diffuse =light.diffuse*diff*texture(texture_diffuse1, TexCoords).rgb;

        //specular
        vec3 viewDir=normalize(viewPos-FragPos);
        vec3 reflectDir=reflect(-lightDir,norm);
        float spec =pow(max(dot(viewDir,reflectDir),0.0),1.0f);
        vec3 specular = light.specular*spec*texture(texture_diffuse1, TexCoords).rgb;

        float distance =length(light.position-FragPos);
        float attenuation = 1.0/ (light.constant+light.linear*distance+light.quadratic* (distance * distance));

         // ambient  *= attenuation; // remove attenuation from ambient, as otherwise at large distances the light would be darker inside than outside the spotlight due the ambient term in the else branch
        diffuse   *= attenuation;
        specular *= attenuation;  

       vec3 result = ambient + diffuse + specular;

        FragColor = vec4(result, 1.0);
    }
    else{
    
    FragColor =vec4(light.ambient*texture(texture_diffuse1, TexCoords).rgb,1.0)   ;
    }

}