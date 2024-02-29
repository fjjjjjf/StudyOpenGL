#version 330 core

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform vec3 viewPos;//添加摄像机位置


struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

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
     
        vec3 ambient = material.ambient * light.ambient;
       
        //diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);//计算光源和片段位置之间的方向向量
    
        float diff = max(dot(norm, lightDir), 0.0);//对norm和lightDir向量进行点乘，计算光源对当前片段实际的漫反射影响。结果值再乘以光的颜色，得到漫反射分量。
        vec3 diffuse = diff * light.diffuse* material.diffuse;//如果两个向量之间的角度大于90度，点乘的结果就会变成负数，这样会导致漫反射分量变为负数。为此，我们使用max函数返回两个参数之间较大的参数，从而保证漫反射分量不会变成负数。
         
        //高光
      
        vec3 viewDir =normalize(viewPos-FragPos);
        vec3 reflectDir =reflect(-lightDir,norm);//取反lightdir，指的是从片段指向光源的向量，保证获得正确reflect

        float spec =pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
        vec3 specular =material.specular*spec*light.specular;

        vec3 result = (ambient + diffuse+ specular) * objectColor;
        FragColor = vec4(result,1.0); 
   }