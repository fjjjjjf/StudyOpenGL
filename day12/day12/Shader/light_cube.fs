#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;


uniform vec3 viewPos;//��������λ��


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
        // ������
     
        vec3 ambient = texture(material.diffuse, TexCoords).rgb * light.ambient;
       
        //diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(light.position - FragPos);//�����Դ��Ƭ��λ��֮��ķ�������
    
        float diff = max(dot(norm, lightDir), 0.0);//��norm��lightDir�������е�ˣ������Դ�Ե�ǰƬ��ʵ�ʵ�������Ӱ�졣���ֵ�ٳ��Թ����ɫ���õ������������
        vec3 diffuse = diff * light.diffuse* texture(material.diffuse, TexCoords).rgb;
        //�߹�
      
        vec3 viewDir =normalize(viewPos-FragPos);
        vec3 reflectDir =reflect(-lightDir,norm);

        float spec =pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
        vec3 specular =texture(material.specular, TexCoords).rgb*spec*light.specular;

        vec3 emission = matrixlight*texture(material.emission,vec2(TexCoords.x,TexCoords.y+matrixmove)).rgb;

        vec3 result = (ambient + diffuse+ specular) +emission;
        FragColor = vec4(result,1.0); 
   }