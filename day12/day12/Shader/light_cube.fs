#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;


uniform vec3 viewPos;//添加摄像机位置


struct Material{
   // vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};
uniform Material material;
uniform float matrixlight;
uniform float matrixmove;
struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

void main()
{
        // 环境光
     
        vec3 ambient = texture(material.diffuse, TexCoords).rgb * light.ambient;
       
        //diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(light.position - FragPos);//计算光源和片段位置之间的方向向量
    
        float diff = max(dot(norm, lightDir), 0.0);//对norm和lightDir向量进行点乘，计算光源对当前片段实际的漫反射影响。结果值再乘以光的颜色，得到漫反射分量。
        vec3 diffuse = diff * light.diffuse* texture(material.diffuse, TexCoords).rgb;
        //高光
      
        vec3 viewDir =normalize(viewPos-FragPos);
        vec3 reflectDir =reflect(-lightDir,norm);

        float spec =pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
        vec3 specular =texture(material.specular, TexCoords).rgb*spec*light.specular;

        vec3 emission = matrixlight*texture(material.emission,vec2(TexCoords.x,TexCoords.y+matrixmove)).rgb;

        vec3 result = (ambient + diffuse+ specular) +emission;
        FragColor = vec4(result,1.0); 
   }