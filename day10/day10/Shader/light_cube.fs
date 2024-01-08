#version 330 core

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;


void main()
{
        // 环境光
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * lightColor;
       
        //diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);//计算光源和片段位置之间的方向向量
    
        float diff = max(dot(norm, lightDir), 0.0);//对norm和lightDir向量进行点乘，计算光源对当前片段实际的漫反射影响。结果值再乘以光的颜色，得到漫反射分量。
        vec3 diffuse = diff * lightColor;//如果两个向量之间的角度大于90度，点乘的结果就会变成负数，这样会导致漫反射分量变为负数。为此，我们使用max函数返回两个参数之间较大的参数，从而保证漫反射分量不会变成负数。
         
        
        vec3 result = (ambient + diffuse) * objectColor;
        FragColor = vec4(result,1.0); 
   }